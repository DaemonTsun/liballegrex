
#pragma once

#include "shl/enum_flag.hpp"
#include "allegrex/psp_elf.hpp"
#include "allegrex/parse_instructions.hpp"

enum class mips_format_options : u8
{
    comment_pos_addr_instr = 1 << 0, // e.g. /* 0025B4 08804000 27BDFFD0 */ ...
    dollar_registers       = 1 << 1, // e.g. li $a1, 1
    comma_separate_args    = 1 << 2, // e.g. li a1, 1 instead of li a1 1
    function_glabels       = 1 << 3, // e.g. glabel func_08804048 for jumps
    labels                 = 1 << 4, // e.g. .L08804090 for branches
    pseudoinstructions     = 1 << 5, // e.g. b, bal, ...
};

enum_flag(mips_format_options);

constexpr mips_format_options default_mips_format_options = 
    mips_format_options::comment_pos_addr_instr |
    mips_format_options::dollar_registers |
    mips_format_options::comma_separate_args |
    mips_format_options::function_glabels |
    mips_format_options::labels |
    mips_format_options::pseudoinstructions;

enum class format_type
{
    Asm
};

struct dump_section
{
    elf_section *section;
    u32 first_instruction_offset; // within elf
    instruction *instructions;
    s32 instruction_count;
    s32 instruction_start_index;
};

// we don't just add a pointer to a elf_psp_module here because we don't
// always want to disassemble an entire elf_psp_module, e.g. if we only
// disassemble ranges.
struct dump_config
{
    file_stream *log;

    hash_table<u32, elf_symbol> *symbols;
    hash_table<u32, function_import> *imports;
    array<module_import> *imported_modules;
    array<module_export> *exported_modules;

    // relocations;
    jump_destination *jumps;
    s32 jump_count;
    array<dump_section> dump_sections;

    prx_sce_module_info *module_info;

    bool verbose;
    mips_format_options format;
};

void init(dump_config *conf);
void free(dump_config *conf);

const char *lookup_address_name(u32 addr, const dump_config *conf);

// some default formatting functions
void fmt_mips_register_name(file_stream *out, mips_register reg);
void fmt_dollar_mips_register_name(file_stream *out, mips_register reg);

void fmt_mips_fpu_register_name(file_stream *out, mips_fpu_register reg);
void fmt_dollar_mips_fpu_register_name(file_stream *out, mips_fpu_register reg);

void fmt_vfpu_register_name(file_stream *out, vfpu_register reg);
void fmt_dollar_vfpu_register_name(file_stream *out, vfpu_register reg);
void fmt_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx);
void fmt_dollar_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx);

void fmt_argument_space(file_stream *out);
void fmt_argument_comma_space(file_stream *out);

void fmt_jump_address_number(file_stream *out, u32 address, const dump_config *conf);
void fmt_jump_address_label(file_stream *out, u32 address, const dump_config *conf);

void fmt_branch_address_number(file_stream *out, u32 address, const dump_config *conf);
void fmt_branch_address_label(file_stream *out, u32 address, const dump_config *conf);

void fmt_jump_glabel(file_stream *out, u32 address, const dump_config *conf);
void fmt_branch_label(file_stream *out, u32 address, const dump_config *conf);

// etc
template<typename T>
constexpr inline T hex_digits(T x)
{
    T i = 0;

    while (x > 0)
    {
        x = x >> 4;
        ++i;
    }

    return i;
}
