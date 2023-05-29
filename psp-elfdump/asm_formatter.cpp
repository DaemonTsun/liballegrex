
#include <assert.h>

#include "shl/format.hpp"
#include "allegrex/instruction.hpp"
#include "psp-elfdump/asm_formatter.hpp"

// asm-specific formatting functions
inline void asm_fmt_comment_pos_addr_instr(file_stream *out, u32 pos, const instruction *inst, const char *format_string)
{
    format(out, format_string, pos, inst->address, inst->opcode);
}

void format_name(file_stream *out, const instruction *inst)
{
    const char *name = get_mnemonic_name(inst->mnemonic);

    if (requires_vfpu_suffix(inst->mnemonic))
    {
        vfpu_size sz = get_vfpu_size(inst->opcode);
        const char *suf = size_suffix(sz);
        auto fullname = tformat("%%\0"_cs, name, suf);

        format(out, "%-10s", fullname.c_str);
    }
    else
        format(out, "%-10s", name);
}

#define ARG_HOLDS_T_FORMAT(out, arg, T, FMT) \
    (std::holds_alternative<T>(arg)) \
    { \
        format(out, FMT, std::get<T>(arg).data); \
    }

// thanks for those c++ function aliases
#define holds_type std::holds_alternative

void asm_format_section(const dump_config *conf, const dump_section *dsec, file_stream *out)
{
    assert(dsec != nullptr);
    assert(dsec->pdata != nullptr);

    const elf_section *sec = dsec->section;
    const jump_destination_array *jumps = conf->jump_destinations;

    // format functions
    auto f_comment_pos_addr_instr = asm_fmt_comment_pos_addr_instr;
    auto f_mips_register_name = fmt_mips_register_name;
    auto f_mips_fpu_register_name = fmt_mips_fpu_register_name;
    auto f_vfpu_register_name = fmt_vfpu_register_name;
    auto f_vfpu_matrix_name = fmt_vfpu_matrix_name;
    auto f_argument_sep = fmt_argument_space;
    auto f_jump_argument = fmt_jump_address_number;
    auto f_branch_argument = fmt_branch_address_number;
    auto f_jump_glabel = fmt_jump_glabel;
    auto f_branch_label = fmt_branch_label;

    // prepare
    char comment_format_string[32] = {0};

    if (is_set(conf->format, mips_format_options::comment_pos_addr_instr))
    {
        // prepare format string for comment
        u32 max_instruction_offset = dsec->first_instruction_offset + dsec->pdata->instructions.size() * sizeof(u32);
        u32 pos_digits = hex_digits(max_instruction_offset);

        sprintf(comment_format_string, "/* %%0%ux %%08x %%08x */  ", pos_digits);
    }
    else
    {
        f_comment_pos_addr_instr = nullptr;
    }

    if (is_set(conf->format, mips_format_options::dollar_registers))
    {
        f_mips_register_name = fmt_dollar_mips_register_name;
        f_mips_fpu_register_name = fmt_dollar_mips_fpu_register_name;
        f_vfpu_register_name = fmt_dollar_vfpu_register_name;
        f_vfpu_matrix_name = fmt_dollar_vfpu_matrix_name;
    }

    if (is_set(conf->format, mips_format_options::comma_separate_args))
        f_argument_sep = fmt_argument_comma_space;

    if (is_set(conf->format, mips_format_options::function_glabels))
        f_jump_argument = fmt_jump_address_label;
    else
        f_jump_glabel = nullptr;

    if (is_set(conf->format, mips_format_options::labels))
        f_branch_argument = fmt_branch_address_label;
    else
        f_branch_label = nullptr;

    u32 pos = dsec->first_instruction_offset;
    u32 jmp_i = 0;

    if (!is_set(conf->format, mips_format_options::function_glabels)
     && !is_set(conf->format, mips_format_options::labels))
        jmp_i = UINT32_MAX;
    else
    {
        // skip symbols that come before this section
        while (jmp_i < jumps->size() && jumps->at(jmp_i).address < dsec->pdata->vaddr)
            ++jmp_i;
    }

    // do the writing
    format(out, "\n\n/* Disassembly of section %s */\n", sec->name);

    for (const instruction &inst : dsec->pdata->instructions)
    {
        bool write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);

        if (write_label)
            write(out, "\n");

        while (write_label)
        {
            auto &jmp = jumps->at(jmp_i);

            if (jmp.type == jump_type::Jump)
            {
                if (f_jump_glabel != nullptr)
                    f_jump_glabel(out, jmp.address, conf);
            }
            else
            {
                if (f_branch_label != nullptr)
                    f_branch_label(out, jmp.address, conf);
            }

            jmp_i++;
            write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);
        }

        if (f_comment_pos_addr_instr != nullptr)
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
                format(out, "%s", std::get<string_arg>(arg).data);

            else if (holds_type<mips_register>(arg))
                f_mips_register_name(out, std::get<mips_register>(arg));

            else if (holds_type<mips_fpu_register>(arg))
                f_mips_fpu_register_name(out, std::get<mips_fpu_register>(arg));

            else if (holds_type<vfpu_register>(arg))
                f_vfpu_register_name(out, std::get<vfpu_register>(arg));

            else if (holds_type<vfpu_matrix>(arg))
            {
                auto &mtx = std::get<vfpu_matrix>(arg);
                format(out, "%s%s", matrix_name(mtx)
                                  , size_suffix(mtx.size));
            }
            else if (holds_type<vfpu_condition>(arg))
                format(out, "%s", vfpu_condition_name(std::get<vfpu_condition>(arg)));

            else if (holds_type<vfpu_constant>(arg))
                format(out, "%s", vfpu_constant_name(std::get<vfpu_constant>(arg)));

            else if (holds_type<vfpu_prefix_array>(arg))
            {
                auto &arr = std::get<vfpu_prefix_array>(arg).data;
                format(out, "[%s,%s,%s,%s]", vfpu_prefix_name(arr[0])
                                           , vfpu_prefix_name(arr[1])
                                           , vfpu_prefix_name(arr[2])
                                           , vfpu_prefix_name(arr[3])
                );
            }
            else if (holds_type<vfpu_destination_prefix_array>(arg))
            {
                auto &arr = std::get<vfpu_destination_prefix_array>(arg).data;
                format(out, "[%s,%s,%s,%s]", vfpu_destination_prefix_name(arr[0])
                                           , vfpu_destination_prefix_name(arr[1])
                                           , vfpu_destination_prefix_name(arr[2])
                                           , vfpu_destination_prefix_name(arr[3])
                );
            }
            else if (holds_type<vfpu_rotation_array>(arg))
            {
                auto &arr = std::get<vfpu_rotation_array>(arg);
                format(out, "[%s", vfpu_rotation_name(arr.data[0]));

                for (int i = 1; i < arr.size; ++i)
                    format(out, ",%s", vfpu_rotation_name(arr.data[i]));

                format(out, "]");
            }
            else if (holds_type<base_register>(arg))
            {
                write(out, "(");
                f_mips_register_name(out, std::get<base_register>(arg).data);
                write(out, ")");
            }

            else if (holds_type<const psp_function*>(arg))
            {
                const psp_function *sc = std::get<const psp_function*>(arg);
                format(out, "%s <0x%08x>", sc->name, sc->nid);
            }
            else if (holds_type<jump_address>(arg))
                f_jump_argument(out, std::get<jump_address>(arg).data, conf);

            else if (holds_type<branch_address>(arg))
                f_branch_argument(out, std::get<branch_address>(arg).data, conf);

            else if (holds_type<immediate<s32>>(arg))
            {
                s32 d = std::get<immediate<s32>>(arg).data;
                if (d < 0)
                    format(out, "-%#x", -d);
                else
                    format(out, "%#x", d);
            }

            else if (holds_type<immediate<s16>>(arg))
            {
                s16 d = std::get<immediate<s16>>(arg).data;
                if (d < 0)
                    format(out, "-%#x", -d);
                else
                    format(out, "%#x", d);
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
                format(out, "[%u, %u]", d.rd, d.sel);
            }
        }
        
        // end
        write(out, "\n");
        pos += sizeof(u32);
    }
}

void asm_format(const dump_config *conf, file_stream *out)
{
    assert(conf != nullptr);
    assert(out != nullptr);

    for (const dump_section &dsec : conf->dump_sections)
        asm_format_section(conf, &dsec, out);
}
