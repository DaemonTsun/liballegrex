
#pragma once

#include "shl/platform.hpp"

#if Windows
#define EI_NIDENT 16

typedef u32 Elf32_Addr;
typedef u32 Elf32_Off;
typedef u16 Elf32_Section;
typedef u16 Elf32_Versym;
typedef  u8 Elf_Byte;
typedef u16 Elf32_Half;
typedef s32 Elf32_Sword;
typedef u32 Elf32_Word;
typedef s64 Elf32_Sxword;
typedef u64 Elf32_Xword;

typedef struct
{
    u8  e_ident[EI_NIDENT];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    Elf32_Addr e_entry;
    Elf32_Off  e_phoff;
    Elf32_Off  e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} Elf32_Ehdr;

typedef struct
{
    u32 p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    u32 p_filesz;
    u32 p_memsz;
    u32 p_flags;
    u32 p_align;
} Elf32_Phdr;

typedef struct
{
    u32 sh_name;
    u32 sh_type;
    u32 sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    u32 sh_size;
    u32 sh_link;
    u32 sh_info;
    u32 sh_addralign;
    u32 sh_entsize;
} Elf32_Shdr;

typedef struct
{
    u32 st_name;
    Elf32_Addr    st_value;
    u32 st_size;
    u8  st_info;
    u8  st_other;
    u16 st_shndx;
} Elf32_Sym;

typedef struct {
    Elf32_Addr r_offset;
    u32   r_info;
} Elf32_Rel;

#define ELF32_R_SYM(x) ((x) >> 8)
#define ELF32_R_TYPE(x) ((x) & 0xff)

#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_HASH     5
#define SHT_DYNAMIC  6
#define SHT_NOTE     7
#define SHT_NOBITS   8
#define SHT_REL      9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11
#define SHT_NUM      12
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff

#define EI_MAG0    0
#define EI_MAG1    1
#define EI_MAG2    2
#define EI_MAG3    3
#define EI_CLASS   4
#define EI_DATA    5
#define EI_VERSION 6
#define EI_OSABI   7
#define EI_PAD     8

#define ELFCLASSNONE 0
#define ELFCLASS32   1
#define ELFCLASS64   2
#define ELFCLASSNUM  3

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define EV_NONE     0
#define EV_CURRENT  1
#define EV_NUM      2

#define SHF_WRITE          0x1
#define SHF_ALLOC          0x2
#define SHF_EXECINSTR      0x4
#define SHF_RELA_LIVEPATCH 0x00100000
#define SHF_RO_AFTER_INIT  0x00200000
#define SHF_MASKPROC       0xf0000000

#define SHN_UNDEF     0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_LIVEPATCH 0xff20
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_HIRESERVE 0xffff

#define EM_MIPS		8	
#else
#include <elf.h>
#endif

/*
#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6
*/

