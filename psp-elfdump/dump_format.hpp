
#pragma once

#include "enum.hpp"
#include "psp_elf.hpp"
#include "parse_instructions.hpp"

enum class format_options
{
    comment_pos_addr_instr = 1 << 0, // e.g. /* 0025B4 08804000 27BDFFD0 */ ...
    dollar_registers       = 1 << 1, // e.g. li $a1, 1
    comma_separate_args    = 1 << 2, // e.g. li a1, 1 instead of li a1 1
    function_glabels       = 1 << 3, // e.g. glabel func_08804048 for jumps
    labels                 = 1 << 4, // e.g. .L08804090 for branches
    pseudoinstructions     = 1 << 5, // e.g. b, bal, ...
};

ENUM_CLASS_FLAG_OPS(format_options);

constexpr format_options default_format_options = 
    format_options::comment_pos_addr_instr |
    format_options::dollar_registers |
    format_options::comma_separate_args |
    format_options::function_glabels |
    format_options::labels |
    format_options::pseudoinstructions;

struct dump_section
{
    elf_section *section;
    parse_data *pdata;
    u32 first_instruction_offset;
};

struct dump_config
{
    file_stream *out;
    file_stream *log;

    symbol_map *symbols;
    import_map *imports;
    module_import_array *imported_modules;
    module_export_array *exported_modules;

    // relocations;
    jump_destination_array *jump_destinations;
    std::vector<dump_section> dump_sections;

    bool verbose;
    format_options format;
};

void dump_format(dump_config *conf);
