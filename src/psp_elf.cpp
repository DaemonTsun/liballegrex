
#include <stdexcept>
#include <string.h>

#include "psp_elf.hpp"

#define LOG(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

#define EI_DATA      5
#define EI_NIDENT    16
#define SHT_SYMTAB   2
#define SHT_REL      9
#define STN_UNDEF    0

#define ELF32_R_SYM(info)  ((info) >> 8)
#define ELF32_R_TYPE(info) ((info) & 0xff)

#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6

#define ELFDATA2LSB  1
#define EM_MIPS      8

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;

typedef struct {
   uint8_t    e_ident[EI_NIDENT];
   uint16_t   e_type;
   uint16_t   e_machine;
   uint32_t   e_version;
   Elf32_Addr e_entry;
   Elf32_Off  e_phoff;
   Elf32_Off  e_shoff;
   uint32_t   e_flags;
   uint16_t   e_ehsize;
   uint16_t   e_phentsize;
   uint16_t   e_phnum;
   uint16_t   e_shentsize;
   uint16_t   e_shnum;
   uint16_t   e_shstrndx;
} Elf32_Ehdr;

typedef struct {
   uint32_t   sh_name;
   uint32_t   sh_type;
   uint32_t   sh_flags;
   Elf32_Addr sh_addr;
   Elf32_Off  sh_offset;
   uint32_t   sh_size;
   uint32_t   sh_link;
   uint32_t   sh_info;
   uint32_t   sh_addralign;
   uint32_t   sh_entsize;
} Elf32_Shdr;

typedef struct {
   uint32_t   st_name;
   Elf32_Addr st_value;
   uint32_t   st_size;
   uint8_t    st_info;
   uint8_t    st_other;
   uint16_t   st_shndx;
} Elf32_Sym;

typedef struct {
   Elf32_Addr r_offset;
   uint32_t   r_info;
} Elf32_Rel;

void read_elf(psp_elf_read_config *conf, void *out)
{
    file_buffer *in = conf->in;

    Elf32_Ehdr elf_header;

    int text_section_index = -1;
    uint32_t vaddr_adj = 0;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    in->read(&elf_header);

    // TODO: attempt decrypt
    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
        throw std::runtime_error("input is not an ELF file or may be encrypted");

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
        throw std::runtime_error("input is not little-endian MIPS");

    LOG(conf, "%s\n", "got little-endian mips");
}
