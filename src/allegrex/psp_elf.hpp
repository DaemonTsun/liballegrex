
#pragma once

#include <map>
#include <vector>
#include <string>

#include "shl/file_stream.hpp"
#include "shl/memory_stream.hpp"
#include "shl/number_types.hpp"

#include "allegrex/psp_modules.hpp"
#include "allegrex/psp_prx.hpp"

#define INFER_VADDR UINT32_MAX

struct psp_elf_read_config
{
    std::string section; // leave empty to read all executable sections
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
    std::vector<u8> content;
    u32 content_offset;
    u32 vaddr;
    std::string name;
};

struct function_import
{
    u32 address;
    const psp_function *function;
};

struct module_import
{
    std::string module_name;
    std::vector<function_import> functions;
    // TODO: std::vector<variable_import> variables;
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
    std::string module_name;
    std::vector<function_export> functions;
    std::vector<variable_export> variables;
};

typedef std::map<u32, elf_symbol> symbol_map;
typedef std::map<u32, function_import> import_map;
typedef std::vector<module_import> module_import_array;
typedef std::vector<module_export> module_export_array;

struct elf_parse_data
{
    symbol_map symbols; // maps vaddrs to symbols
    import_map imports; // maps vaddrs to imported functions

    module_import_array imported_modules; // the imported modules with redundant function information
    module_export_array exported_modules; // module_start, end, etc.

    std::vector<elf_relocation> relocations;
    std::vector<elf_section> sections;

    prx_sce_module_info module_info;
};

// parse all information about the elf file
// its copied to memory if read from file, sorry
void read_elf(file_stream *in, const psp_elf_read_config *conf, elf_parse_data *out);
void read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out);

// returns decrypted size, or 0 if input is regular ELF
size_t decrypt_elf(file_stream *in, std::vector<u8> *out);
size_t decrypt_elf(memory_stream *in, std::vector<u8> *out);
