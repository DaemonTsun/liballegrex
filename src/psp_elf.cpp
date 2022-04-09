
#include <stdexcept>
#include <vector>

#include <elf.h>
#include <assert.h>
#include <string.h>

#include "string.hpp"
#include "prx_decrypt.hpp"
#include "psp_elf.hpp"

/*
#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6
*/

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};
#define read_section(in, ehdr, index, out) in->read_at(out, ehdr.e_shoff + (index) * ehdr.e_shentsize);

template<typename StreamT>
void add_symbols(StreamT *in, const psp_elf_read_config *conf, Elf32_Ehdr &elf_header, int section_index, char *string_table_data, std::map<u32, elf_symbol> &symbols)
{
    // there's a good chance symbols don't exist
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
            symbols[sym.st_value] = elf_symbol{sym.st_value, std::string(name)};
        }
    }
}

// TODO: actually add relocation information
// currently only logs relocations
// do games have relocations...?
template<typename StreamT>
void add_relocations(StreamT *in, const psp_elf_read_config *conf, Elf32_Ehdr &elf_header, char *string_table_data, std::vector<elf_relocation> &out)
{
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

void _read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_section *out)
{
    Elf32_Ehdr elf_header;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    in->read(&elf_header);

    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
        throw std::runtime_error("input is not an ELF file");

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
        throw std::runtime_error("input is not little-endian MIPS");

    log(conf, "%s\n", "got little-endian mips");

    if (elf_header.e_shstrndx == SHN_UNDEF)
    {
        // while we could look at program headers, PSP games
        // can have strange sections (e.g. MHFU has ~600 sections, a lot of them empty)
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

    out->name = conf->section;
    u32 vaddr = conf->vaddr;

    if (conf->vaddr == INFER_VADDR)
        vaddr = section_header.sh_addr;

    out->vaddr = vaddr;

    add_symbols(in, conf, elf_header, section_index, string_table.data(), out->symbols);
    add_relocations(in, conf, elf_header, string_table.data(), out->relocations);

    out->content = memory_stream(section_header.sh_size);
    out->content_offset = section_header.sh_offset;
    in->read_at(out->content.data(), section_header.sh_offset, section_header.sh_size);
}

void read_elf(file_stream *in, const psp_elf_read_config *conf, elf_section *out)
{
    memory_stream memstr = memory_stream(in->size());
    in->read_at(memstr.data(), 0, in->size());

    read_elf(&memstr, conf, out);
}

void read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_section *out)
{
    std::vector<u8> decrypted_elf;

    if (decrypt_elf(in, &decrypted_elf))
    {
        log(conf, "ELF is encrypted and has been decrypted.\n");
        memory_stream delf = memory_stream(reinterpret_cast<char*>(decrypted_elf.data()),
                                           decrypted_elf.size());
        _read_elf(&delf, conf, out);
        return;
    }

    in->seek(0);

    // simply parse from memory if not encrypted
    _read_elf(in, conf, out);
}

size_t decrypt_elf(file_stream *in, std::vector<u8> *out)
{
    memory_stream memstr = memory_stream(in->size());
    in->read_at(memstr.data(), 0, in->size());

    return decrypt_elf(&memstr, out);
}

size_t decrypt_elf(memory_stream *in, std::vector<u8> *out)
{
    Elf32_Ehdr elf_header;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    char magic[4];
    in->read(magic, 4);

    if (strncmp(magic, "\x7f" "ELF", 4))
    {
        // not an ELF
        
        if (strncmp(magic, "~PSP", 4))
            // not encrypted either
            throw std::runtime_error("input is not an ELF file and is not encrypted");

        // ok its encrypted, attempt decrypt
        PSP_Header phead;
        in->read_at(&phead, 0);

        size_t nsize = std::max(phead.elf_size, phead.psp_size);
        out->resize(nsize);

        int decrypted_size = pspDecryptPRX(reinterpret_cast<const u8*>(in->data()),
                                           out->data(),
                                           phead.psp_size);

        if (decrypted_size < 0)
            throw std::runtime_error("could not decrypt input file");

        /* TODO: implement gzip
        const auto isGzip = phead.comp_attribute & 1;
        if (isGzip)
            ...
        */

        return decrypted_size;
    }

    // nothing to decrypt
    return 0;
}
