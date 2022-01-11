
#include <stdexcept>
#include <vector>

#include <elf.h>
#include <assert.h>
#include <string.h>

#include "string.hpp"
#include "psp_elf.hpp"

#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};
#define read_section(in, ehdr, index, out) in->read_at(out, ehdr.e_shoff + (index) * ehdr.e_shentsize);

void add_symbols(const psp_elf_read_config *conf, Elf32_Ehdr &elf_header, int section_index, char *string_table_data, std::vector<elf_symbol> &symbols)
{
    // there's a good chance symbols don't exist
    auto *in = conf->in;

    for (int i = 0; i < elf_header.e_shnum; i++)
    {
        Elf32_Shdr sec_header;
        read_section(in, elf_header, i, &sec_header);
        const char *section_name = string_table_data + sec_header.sh_name;

        if (sec_header.sh_type != SHT_SYMTAB)
            continue;

        assert(sec_header.sh_entsize == sizeof(Elf32_Sym));

        if (sec_header.sh_size == 0)
            // log empty tables maybe?
            continue;

        log(conf, "found symtab %s\n", section_name);

        Elf32_Shdr strtab_header;
        read_section(in, elf_header, sec_header.sh_link, &strtab_header);

        std::vector<char> sec_string_table;
        sec_string_table.resize(strtab_header.sh_size);
        in->read_at(sec_string_table.data(), strtab_header.sh_offset, strtab_header.sh_size);

        for (u32 i = 0; i < sec_header.sh_size; i += sizeof(Elf32_Sym))
        {
            Elf32_Sym sym;
            in->read_at(&sym, sec_header.sh_offset + i);

            const char *name = sec_string_table.data() + sym.st_name;

            if (sym.st_shndx != section_index || name[0] == '.')
                continue;

            log(conf, "  got symbol '%s' at %08x\n", name, sym.st_value);
            symbols.emplace_back(elf_symbol{sym.st_value, std::string(name)});
        }
    }
}

// TODO: actually add relocation information
// currently only logs relocations
// do games have relocations...?
void add_relocations(const psp_elf_read_config *conf, Elf32_Ehdr &elf_header, char *string_table_data)
{
    auto *in = conf->in;

    for (int i = 0; i < elf_header.e_shnum; ++i)
    {
        Elf32_Shdr sec_header;
        read_section(in, elf_header, i, &sec_header);

        if (sec_header.sh_type != SHT_REL
        // || sec_header.sh_info != (u32)section_index
         )
            continue;

        const char *section_name = string_table_data + sec_header.sh_name;

        assert(sec_header.sh_entsize == sizeof(Elf32_Rel));

        if (sec_header.sh_size == 0)
            // log empty tables maybe?
            continue;

        log(conf, "got relocation table %s\n", section_name);

        for (u32 j = 0; j < sec_header.sh_size; j += sizeof(Elf32_Rel))
        {
            Elf32_Rel rel;
            in->read_at(&rel, sec_header.sh_offset + j);
            u32 index = ELF32_R_SYM(rel.r_info);
            u32 type = ELF32_R_TYPE(rel.r_info);

            log(conf, "  relocation %08x, %d %d\n", rel.r_offset, index, type);
        }
    }
}

void read_elf(const psp_elf_read_config *conf, void *out)
{
    file_buffer *in = conf->in;

    Elf32_Ehdr elf_header;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    in->read(&elf_header);

    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
        // TODO: attempt decrypt
        throw std::runtime_error("input is not an ELF file or may be encrypted");

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
        throw std::runtime_error("input is not little-endian MIPS");

    log(conf, "%s\n", "got little-endian mips");

    if (elf_header.e_shstrndx == SHN_UNDEF)
    {
        // while we could look at program headers, PSP games
        // can have strange sections (e.g. MHFU has ~600 sections)
        // so we just rely on the name given by command line args.
        throw std::runtime_error("no section header table index found");
    }

    Elf32_Shdr string_table_header;
    read_section(in, elf_header, elf_header.e_shstrndx, &string_table_header);

    std::vector<char> string_table;
    string_table.resize(string_table_header.sh_size);
    in->read_at(string_table.data(), string_table_header.sh_offset, string_table_header.sh_size);
    
    Elf32_Shdr section_header;

    log(conf, "              %-20s: offset   - size\n", "name");

    int section_index = -1;

    for (int i = 0; i < elf_header.e_shnum; ++i)
    {
        read_section(in, elf_header, i, &section_header);
        const char *section_name = string_table.data() + section_header.sh_name;

        if (conf->section != section_name)
            continue;

        log(conf, "found section %-20s: %08x - %08x\n", section_name, section_header.sh_offset, section_header.sh_size);
        section_index = i;
        break;
    }

    if (section_index < 0)
        throw std::runtime_error(str("section '", conf->section, "' not found in input file"));

    u32 vaddr = conf->vaddr;

    if (conf->vaddr == INFER_VADDR)
        vaddr = section_header.sh_addr;

    std::vector<elf_symbol> symbols;
    add_symbols(conf, elf_header, section_index, string_table.data(), symbols);

    add_relocations(conf, elf_header, string_table.data());
}
