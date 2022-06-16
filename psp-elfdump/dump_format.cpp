
#include <assert.h>

#include "string.hpp"
#include "file_stream.hpp"
#include "instruction.hpp"
#include "dump_format.hpp"

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

inline void fmt_comment_pos_addr_instr(file_stream *out, u32 pos, const instruction *inst, const char *format_string)
{
    out->format(format_string, pos, inst->address, inst->opcode);
}

inline void fmt_no_comment_pos_addr_instr(file_stream *out, u32 pos, const instruction *inst, const char *format_string)
{
}

inline void fmt_mips_register_name(file_stream *out, mips_register reg)
{
    out->format("%s", register_name(reg));
}

inline void fmt_dollar_mips_register_name(file_stream *out, mips_register reg)
{
    out->format("$%s", register_name(reg));
}

inline void fmt_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    out->format("%s", register_name(reg));
}

inline void fmt_dollar_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    out->format("$%s", register_name(reg));
}

inline void fmt_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    out->format("%s%s", register_name(reg), size_suffix(reg.size));
}

inline void fmt_dollar_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    out->format("$%s%s", register_name(reg), size_suffix(reg.size));
}

inline void fmt_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    out->format("%s%s", matrix_name(mtx), size_suffix(mtx.size));
}

inline void fmt_dollar_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    out->format("$%s%s", matrix_name(mtx), size_suffix(mtx.size));
}

inline void fmt_argument_space(file_stream *out)
{
    out->write(" ");
}

inline void fmt_argument_comma_space(file_stream *out)
{
    out->write(", ");
}

inline void fmt_jump_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("0x%08x", address);
}

const char *lookup_address_name(u32 addr, const dump_config *conf)
{
    // symbols
    auto it = conf->symbols->find(addr);

    if (it != conf->symbols->end())
        return it->second.name.c_str();

    // imports
    auto it2 = conf->imports->find(addr);

    if (it2 != conf->imports->end())
        return it2->second.function->name;

    // exports (unoptimized, but probably not too common)
    for (int i = 0; i < conf->exported_modules->size(); ++i)
    {
        for (const auto &f : conf->exported_modules->at(i).functions)
            if (f.address == addr)
                return f.function->name;
    }

    return nullptr;
}

inline void fmt_jump_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    const char *name = lookup_address_name(address, conf);

    if (name != nullptr)
        out->format("%s", name);
    else
        out->format("func_%08x", address);
}

inline void fmt_branch_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("0x%08x", address);
}

inline void fmt_branch_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    // we could use symbols for lookup, but these are just branch
    // labels, not jumps usually.
    out->format(".L%08x", address);
}

inline void fmt_jump_glabel(file_stream *out, u32 address, const dump_config *conf)
{
    const char *name = lookup_address_name(address, conf);

    if (name != nullptr)
        out->format("glabel %s\n", name);
    else
        out->format("glabel func_%08x\n", address);
}

inline void fmt_no_jump_glabel(file_stream *out, u32 address, const dump_config *conf)
{
}

inline void fmt_branch_label(file_stream *out, u32 address, const dump_config *conf)
{
    // same thing as before, these are branches, not jumps.
    // address name lookup is probably not necessary.
    out->format(".L%08x:\n", address);
}

inline void fmt_no_branch_label(file_stream *out, u32 address, const dump_config *conf)
{
}

void format_name(file_stream *out, const instruction *inst)
{
    const char *name = get_mnemonic_name(inst->mnemonic);

    if (requires_vfpu_suffix(inst->mnemonic))
    {
        vfpu_size sz = get_vfpu_size(inst->opcode);
        const char *suf = size_suffix(sz);
        auto fullname = str(name, suf); // slow lol

        out->format("%-10s", fullname.c_str());
    }
    else
        out->format("%-10s", name);
}

#define ARG_HOLDS_T_FORMAT(out, arg, T, FMT) \
    (std::holds_alternative<T>(arg)) \
    { \
        out->format(FMT, std::get<T>(arg).data); \
    }

// thanks for those c++ function aliases
#define holds_type std::holds_alternative

void dump_format_section(dump_config *conf, dump_section *dsec)
{
    assert(dsec != nullptr);
    assert(dsec->pdata != nullptr);

    auto *out = conf->out;
    auto *sec = dsec->section;
    auto *jumps = conf->jump_destinations;
    u32 max_instruction_offset = dsec->first_instruction_offset + dsec->pdata->instructions.size() * sizeof(u32);

    // format functions
    auto f_comment_pos_addr_instr = fmt_no_comment_pos_addr_instr;
    auto f_mips_register_name = fmt_mips_register_name;
    auto f_mips_fpu_register_name = fmt_mips_fpu_register_name;
    auto f_vfpu_register_name = fmt_vfpu_register_name;
    auto f_vfpu_matrix_name = fmt_vfpu_matrix_name;
    auto f_argument_sep = fmt_argument_space;
    auto f_jump_argument = fmt_jump_address_number;
    auto f_branch_argument = fmt_branch_address_number;
    auto f_jump_glabel = fmt_no_jump_glabel;
    auto f_branch_label = fmt_no_branch_label;

    // prepare
    char comment_format_string[32] = {0};

    if (is_set(conf->format, format_options::comment_pos_addr_instr))
    {
        // prepare format string for comment
        u32 pos_digits = hex_digits(max_instruction_offset);

        sprintf(comment_format_string, "/* %%0%ux %%08x %%08x */  ", pos_digits);
        f_comment_pos_addr_instr = fmt_comment_pos_addr_instr;
    }

    if (is_set(conf->format, format_options::dollar_registers))
    {
        f_mips_register_name = fmt_dollar_mips_register_name;
        f_mips_fpu_register_name = fmt_dollar_mips_fpu_register_name;
        f_vfpu_register_name = fmt_dollar_vfpu_register_name;
        f_vfpu_matrix_name = fmt_dollar_vfpu_matrix_name;
    }

    if (is_set(conf->format, format_options::comma_separate_args))
        f_argument_sep = fmt_argument_comma_space;

    if (is_set(conf->format, format_options::function_glabels))
    {
        f_jump_argument = fmt_jump_address_label;
        f_jump_glabel = fmt_jump_glabel;
    }

    if (is_set(conf->format, format_options::labels))
    {
        f_branch_argument = fmt_branch_address_label;
        f_branch_label = fmt_branch_label;
    }

    u32 pos = dsec->first_instruction_offset;
    u32 jmp_i = 0;

    if (!is_set(conf->format, format_options::function_glabels)
     && !is_set(conf->format, format_options::labels))
        jmp_i = UINT32_MAX;
    else
    {
        // skip symbols that come before this section
        while (jmp_i < jumps->size() && jumps->at(jmp_i).address < dsec->pdata->vaddr)
            ++jmp_i;
    }

    // do the writing
    out->format("\n\n/* Disassembly of section %s */\n", sec->name.c_str());

    for (const instruction &inst : dsec->pdata->instructions)
    {
        bool write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);

        if (write_label)
            out->write("\n");

        while (write_label)
        {
            auto &jmp = jumps->at(jmp_i);

            if (jmp.type == jump_type::Jump)
                f_jump_glabel(out, jmp.address, conf);
            else
                f_branch_label(out, jmp.address, conf);

            jmp_i++;
            write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);
        }

        f_comment_pos_addr_instr(out, pos, &inst, comment_format_string);
        format_name(out, &inst);

        bool first = true;
        for (auto &arg : inst.arguments)
        {
            if (!first && !holds_type<base_register>(arg))
                f_argument_sep(out);

            first = false;

            // i hate variant
            if (holds_type<string_arg>(arg))
                out->format("%s", std::get<string_arg>(arg).data);

            else if (holds_type<mips_register>(arg))
                f_mips_register_name(out, std::get<mips_register>(arg));

            else if (holds_type<mips_fpu_register>(arg))
                f_mips_fpu_register_name(out, std::get<mips_fpu_register>(arg));

            else if (holds_type<vfpu_register>(arg))
                f_vfpu_register_name(out, std::get<vfpu_register>(arg));

            else if (holds_type<vfpu_matrix>(arg))
            {
                auto &mtx = std::get<vfpu_matrix>(arg);
                out->format("%s%s", matrix_name(mtx)
                                  , size_suffix(mtx.size));
            }
            else if (holds_type<vfpu_condition>(arg))
                out->format("%s", vfpu_condition_name(std::get<vfpu_condition>(arg)));

            else if (holds_type<vfpu_constant>(arg))
                out->format("%s", vfpu_constant_name(std::get<vfpu_constant>(arg)));

            else if (holds_type<vfpu_prefix_array>(arg))
            {
                auto &arr = std::get<vfpu_prefix_array>(arg).data;
                out->format("[%s,%s,%s,%s]", vfpu_prefix_name(arr[0])
                                           , vfpu_prefix_name(arr[1])
                                           , vfpu_prefix_name(arr[2])
                                           , vfpu_prefix_name(arr[3])
                );
            }
            else if (holds_type<vfpu_destination_prefix_array>(arg))
            {
                auto &arr = std::get<vfpu_destination_prefix_array>(arg).data;
                out->format("[%s,%s,%s,%s]", vfpu_destination_prefix_name(arr[0])
                                           , vfpu_destination_prefix_name(arr[1])
                                           , vfpu_destination_prefix_name(arr[2])
                                           , vfpu_destination_prefix_name(arr[3])
                );
            }
            else if (holds_type<vfpu_rotation_array>(arg))
            {
                auto &arr = std::get<vfpu_rotation_array>(arg);
                out->format("[%s", vfpu_rotation_name(arr.data[0]));

                for (int i = 1; i < arr.size; ++i)
                    out->format(",%s", vfpu_rotation_name(arr.data[i]));

                out->format("]");
            }
            else if (holds_type<base_register>(arg))
            {
                out->write("(");
                f_mips_register_name(out, std::get<base_register>(arg).data);
                out->write(")");
            }

            else if (holds_type<const psp_function*>(arg))
            {
                const psp_function *sc = std::get<const psp_function*>(arg);
                out->format("%s <0x%08x>", sc->name, sc->nid);
            }
            else if (holds_type<jump_address>(arg))
                f_jump_argument(out, std::get<jump_address>(arg).data, conf);

            else if (holds_type<branch_address>(arg))
                f_branch_argument(out, std::get<branch_address>(arg).data, conf);

            else if (holds_type<immediate<s32>>(arg))
            {
                s32 d = std::get<immediate<s32>>(arg).data;
                if (d < 0)
                    out->format("-%#x", -d);
                else
                    out->format("%#x", d);
            }

            else if (holds_type<immediate<s16>>(arg))
            {
                s16 d = std::get<immediate<s16>>(arg).data;
                if (d < 0)
                    out->format("-%#x", -d);
                else
                    out->format("%#x", d);
            }

            else if ARG_HOLDS_T_FORMAT(out, arg, shift,            "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, memory_offset,    "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, immediate<u32>,   "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, immediate<u16>,   "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, immediate<u8>,    "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, immediate<float>, "%f")
            else if ARG_HOLDS_T_FORMAT(out, arg, condition_code,   "(CC[%#x])")
            else if ARG_HOLDS_T_FORMAT(out, arg, bitfield_pos,     "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, bitfield_size,    "%#x")
            else if (holds_type<coprocessor_register>(arg))
            {
                auto &d = std::get<coprocessor_register>(arg);
                out->format("[%u, %u]", d.rd, d.sel);
            }
        }
        
        // end
        conf->out->write("\n");
        pos += sizeof(u32);
    }
}

void dump_format(dump_config *conf)
{
    assert(conf != nullptr);
    assert(conf->out != nullptr);

    for (dump_section &dsec : conf->dump_sections)
        dump_format_section(conf, &dsec);
}
