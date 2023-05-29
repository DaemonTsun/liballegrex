
#include <assert.h>
#include "psp-elfdump/dump_format.hpp"

static_assert(hex_digits(0x00000000) == 0);
static_assert(hex_digits(0x00000001) == 1);
static_assert(hex_digits(0x00000008) == 1);
static_assert(hex_digits(0x0000000f) == 1);
static_assert(hex_digits(0x00000010) == 2);
static_assert(hex_digits(0x000000f0) == 2);
static_assert(hex_digits(0x000000ff) == 2);
static_assert(hex_digits(0x00000100) == 3);
static_assert(hex_digits(0x00100000) == 6);
static_assert(hex_digits(0x10000000) == 8);

void init(dump_config *conf)
{
    assert(conf != nullptr);
    ::init(&conf->dump_sections);
}

void free(dump_config *conf)
{
    assert(conf != nullptr);

    ::free(&conf->dump_sections);
}

const char *lookup_address_name(u32 addr, const dump_config *conf)
{
    // symbols
    elf_symbol *sym = ::search(conf->symbols, &addr);

    if (sym != nullptr)
        return sym->name;

    // imports
    function_import *fimp = ::search(conf->imports, &addr);

    if (fimp != nullptr)
        return fimp->function->name;

    // exports (unoptimized, but probably not too common)
    for_array(mod, conf->exported_modules)
    {
        for_array(func, &mod->functions)
            if (func->address == addr)
                return func->function->name;
    }

    return nullptr;
}

void fmt_mips_register_name(file_stream *out, mips_register reg)
{
    format(out, "%s", register_name(reg));
}

void fmt_dollar_mips_register_name(file_stream *out, mips_register reg)
{
    format(out, "$%s", register_name(reg));
}

void fmt_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    format(out, "%s", register_name(reg));
}

void fmt_dollar_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    format(out, "$%s", register_name(reg));
}

void fmt_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    format(out, "%s%s", register_name(reg), size_suffix(reg.size));
}

void fmt_dollar_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    format(out, "$%s%s", register_name(reg), size_suffix(reg.size));
}

void fmt_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    format(out, "%s%s", matrix_name(mtx), size_suffix(mtx.size));
}

void fmt_dollar_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    format(out, "$%s%s", matrix_name(mtx), size_suffix(mtx.size));
}

void fmt_argument_space(file_stream *out)
{
    write(out, " ");
}

void fmt_argument_comma_space(file_stream *out)
{
    write(out, ", ");
}

void fmt_jump_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    format(out, "0x%08x", address);
}

void fmt_jump_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    const char *name = lookup_address_name(address, conf);

    if (name != nullptr)
        format(out, "%s", name);
    else
        format(out, "func_%08x", address);
}

void fmt_branch_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    format(out, "0x%08x", address);
}

void fmt_branch_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    // we could use symbols for lookup, but these are just branch
    // labels, not jumps usually.
    format(out, ".L%08x", address);
}

void fmt_jump_glabel(file_stream *out, u32 address, const dump_config *conf)
{
    const char *name = lookup_address_name(address, conf);

    if (name != nullptr)
        format(out, "glabel %s\n", name);
    else
        format(out, "glabel func_%08x\n", address);
}

void fmt_branch_label(file_stream *out, u32 address, const dump_config *conf)
{
    // same thing as before, these are branches, not jumps.
    // address name lookup is probably not necessary.
    format(out, ".L%08x:\n", address);
}
