
#pragma once

#include "shl/array.hpp"
#include "shl/string.hpp"
#include "shl/hash_table.hpp"
#include "shl/streams.hpp"
#include "shl/number_types.hpp"

#include "allegrex/psp_modules.hpp"
#include "allegrex/psp_prx.hpp"

#define INFER_VADDR max_value(u32)

struct psp_parse_elf_config
{
    const_string section; // leave empty to read all executable sections
    u32 vaddr;
    bool verbose;
    file_stream *log;
};

struct elf_symbol
{
    u32 address;
    const char *name;
};

struct elf_relocation
{
    s32 addend;
    u32 offset;
    const char *symbol_name;
};

struct elf_section
{
    char *content;
    u64 content_size;
    u32 content_offset; // within elf
    u32 vaddr;
    const char *name;
};

struct function_import
{
    u32 address;
    const psp_function *function;
};

struct module_import
{
    const char *module_name;
    array<function_import> functions;
    // TODO: array<variable_import> variables;
};

struct function_export
{
    u32 address;
    const psp_function *function;
};

struct variable_export
{
    u32 address;
    const psp_variable *variable;
};

struct module_export
{
    const char *module_name;
    array<function_export> functions;
    array<variable_export> variables;
};

struct elf_psp_module
{
    char *elf_data; // the whole decrypted elf data, including strings, sections, etc.
    u64 elf_size; // size of elf_data

    prx_sce_module_info module_info;

    hash_table<u32, elf_symbol> symbols; // maps vaddrs to symbols
    hash_table<u32, function_import> imports; // maps vaddrs to imported functions

    array<module_import> imported_modules; // the imported modules with redundant function information
    array<module_export> exported_modules; // module_start, end, etc.

    array<elf_relocation> relocations;
    array<elf_section> sections;
};

void init(elf_psp_module *mod);
void free(elf_psp_module *mod);

bool parse_psp_module_from_elf(const char *path, elf_psp_module *out, error *err = nullptr);
bool parse_psp_module_from_elf(const char *path, elf_psp_module *out, const psp_parse_elf_config *conf, error *err = nullptr);
bool parse_psp_module_from_elf(char *elf_data, u64 elf_size, elf_psp_module *out, error *err = nullptr);
bool parse_psp_module_from_elf(char *elf_data, u64 elf_size, elf_psp_module *out, const psp_parse_elf_config *conf, error *err = nullptr);
bool parse_psp_module_from_elf(memory_stream *elf_stream, elf_psp_module *out, error *err = nullptr);
bool parse_psp_module_from_elf(memory_stream *elf_stream, elf_psp_module *out, const psp_parse_elf_config *conf, error *err = nullptr);

// parse all information about the elf file
// its copied to memory if read from file, sorry
// void read_elf(file_stream *in, const psp_parse_elf_config *conf, elf_psp_module *out);
// void read_elf(memory_stream *in, const psp_parse_elf_config *conf, elf_psp_module *out);

// returns decrypted size, 0 if input is regular ELF, or -1 on error
s64 decrypt_elf(file_stream *in, array<u8> *out, error *err = nullptr);
s64 decrypt_elf(memory_stream *in, array<u8> *out, error *err = nullptr);
