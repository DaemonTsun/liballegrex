
#include <stdexcept>
#include <vector>

#include <elf.h>
#include <string.h>

#include "string.hpp"
#include "psp_elf.hpp"


#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};
#define read_section(in, ehdr, index, out) in->read_at(out, ehdr.e_shoff + (index) * ehdr.e_shentsize);

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

    
}
