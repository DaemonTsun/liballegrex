
#pragma once

#include <map>
#include <vector>
#include "psp_modules.hpp"
#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "number_types.hpp"

#define INFER_VADDR UINT32_MAX

struct psp_elf_read_config
{
    std::string section;
    u32 vaddr;
    bool verbose;
    file_stream *log;
};

struct elf_symbol
{
    u32 address;
    std::string name;
};

struct elf_relocation
{
    s32 addend;
    u32 offset;
    std::string symbol_name;
};

struct elf_section
{
    memory_stream content;
    u32 content_offset;
    u32 vaddr;
    std::string name;
};

struct prx_function_import
{
    u32 address;
    const psp_function *function;
};

typedef std::map<u32, elf_symbol> symbol_map;
typedef std::map<u32, prx_function_import> import_map;

struct elf_parse_data
{
    symbol_map symbols;
    import_map imports;

    std::vector<elf_relocation> relocations;
    std::vector<elf_section> sections;
};

// its copied to memory if read from file, sorry
void read_elf(file_stream *in, const psp_elf_read_config *conf, elf_parse_data *out);
void read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out);

// returns decrypted size, or 0 if input is regular ELF
size_t decrypt_elf(file_stream *in, std::vector<u8> *out);
size_t decrypt_elf(memory_stream *in, std::vector<u8> *out);
