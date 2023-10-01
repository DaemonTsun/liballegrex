
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

void asm_format_section(const dump_config *conf, const dump_section *dsec, file_stream *out)
{
    assert(dsec != nullptr);
    assert(dsec->instruction_data != nullptr);

    const elf_section *sec = dsec->section;
    const jump_destinations *jumps = conf->jumps;

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

    if (is_flag_set(conf->format, mips_format_options::comment_pos_addr_instr))
    {
        // prepare format string for comment
        u32 max_instruction_offset = dsec->first_instruction_offset + (u32)dsec->instruction_data->instructions.size * sizeof(u32);
        u32 pos_digits = hex_digits(max_instruction_offset);

        sprintf(comment_format_string, "/* %%0%ux %%08x %%08x */  ", pos_digits);
    }
    else
    {
        f_comment_pos_addr_instr = nullptr;
    }

    if (is_flag_set(conf->format, mips_format_options::dollar_registers))
    {
        f_mips_register_name = fmt_dollar_mips_register_name;
        f_mips_fpu_register_name = fmt_dollar_mips_fpu_register_name;
        f_vfpu_register_name = fmt_dollar_vfpu_register_name;
        f_vfpu_matrix_name = fmt_dollar_vfpu_matrix_name;
    }

    if (is_flag_set(conf->format, mips_format_options::comma_separate_args))
        f_argument_sep = fmt_argument_comma_space;

    if (is_flag_set(conf->format, mips_format_options::function_glabels))
        f_jump_argument = fmt_jump_address_label;
    else
        f_jump_glabel = nullptr;

    if (is_flag_set(conf->format, mips_format_options::labels))
        f_branch_argument = fmt_branch_address_label;
    else
        f_branch_label = nullptr;

    u32 pos = dsec->first_instruction_offset;
    u32 jmp_i = 0;

    if (!is_flag_set(conf->format, mips_format_options::function_glabels)
     && !is_flag_set(conf->format, mips_format_options::labels))
        jmp_i = UINT32_MAX;
    else
    {
        // skip symbols that come before this section
        while (jmp_i < array_size(jumps)
            && jumps->data[jmp_i].address < dsec->instruction_data->vaddr)
            ++jmp_i;
    }

    // do the writing
    format(out, "\n\n/* Disassembly of section %s */\n", sec->name);

    for_array(inst, &dsec->instruction_data->instructions)
    {
        bool write_label = (jmp_i < array_size(jumps)) && (jumps->data[jmp_i].address <= inst->address);

        if (write_label)
            write(out, "\n");

        while (write_label)
        {
            jump_destination *jmp = jumps->data.data + jmp_i;

            if (jmp->type == jump_type::Jump)
            {
                if (f_jump_glabel != nullptr)
                    f_jump_glabel(out, jmp->address, conf);
            }
            else
            {
                if (f_branch_label != nullptr)
                    f_branch_label(out, jmp->address, conf);
            }

            jmp_i++;
            write_label = (jmp_i < array_size(jumps)) && (jumps->data[jmp_i].address <= inst->address);
        }

        if (f_comment_pos_addr_instr != nullptr)
            f_comment_pos_addr_instr(out, pos, inst, comment_format_string);

        format_name(out, inst);

        bool first = true;
        for (int i = 0; i < inst->argument_count; ++i)
        {
            instruction_argument *arg = inst->arguments + i;
            argument_type arg_type = inst->argument_types[i];

            if (!first && arg_type != argument_type::Base_Register)
                f_argument_sep(out);

            first = false;

            switch (arg_type)
            {
            case argument_type::Invalid:
                format(out, "[?invalid?]");
                break;

            case argument_type::MIPS_Register:
                f_mips_register_name(out, arg->mips_register);
                break;

            case argument_type::MIPS_FPU_Register:
                f_mips_fpu_register_name(out, arg->mips_fpu_register);
                break;

            case argument_type::VFPU_Register:
                f_vfpu_register_name(out, arg->vfpu_register);
                break;

            case argument_type::VFPU_Matrix:
                format(out, "%s%s", matrix_name(arg->vfpu_matrix)
                                  , size_suffix(arg->vfpu_matrix.size));
                break;

            case argument_type::VFPU_Condition:
                format(out, "%s", vfpu_condition_name(arg->vfpu_condition));
                break;

            case argument_type::VFPU_Constant:
                format(out, "%s", vfpu_constant_name(arg->vfpu_constant));
                break;

            case argument_type::VFPU_Prefix_Array:
            {
                vfpu_prefix_array *arr = &arg->vfpu_prefix_array;
                format(out, "[%s,%s,%s,%s]", vfpu_prefix_name(arr->data[0])
                                           , vfpu_prefix_name(arr->data[1])
                                           , vfpu_prefix_name(arr->data[2])
                                           , vfpu_prefix_name(arr->data[3])
                );
                break;
            }

            case argument_type::VFPU_Destination_Prefix_Array:
            {
                vfpu_destination_prefix_array *arr = &arg->vfpu_destination_prefix_array;
                format(out, "[%s,%s,%s,%s]", vfpu_destination_prefix_name(arr->data[0])
                                           , vfpu_destination_prefix_name(arr->data[1])
                                           , vfpu_destination_prefix_name(arr->data[2])
                                           , vfpu_destination_prefix_name(arr->data[3])
                );
                break;
            }

            case argument_type::VFPU_Rotation_Array:
            {
                vfpu_rotation_array *arr = &arg->vfpu_rotation_array;
                format(out, "[%s", vfpu_rotation_name(arr->data[0]));

                for (int j = 1; j < arr->size; ++j)
                    format(out, ",%s", vfpu_rotation_name(arr->data[j]));

                format(out, "]");
                break;
            }

            case argument_type::PSP_Function_Pointer:
            {
                const psp_function *sc = arg->psp_function_pointer;
                format(out, "%s <0x%08x>", sc->name, sc->nid);
                break;
            }

#define ARG_TYPE_FORMAT(out, arg, ArgumentType, UnionMember, FMT) \
    case argument_type::ArgumentType: \
        format(out, FMT, arg->UnionMember.data);\
        break;

            ARG_TYPE_FORMAT(out, arg, Shift, shift, "%#x");

            case argument_type::Coprocessor_Register:
            {
                coprocessor_register *reg = &arg->coprocessor_register;
                format(out, "[%u, %u]", reg->rd, reg->sel);
                break;
            }

            case argument_type::Base_Register:
                write(out, "(");
                f_mips_register_name(out, arg->base_register.data);
                write(out, ")");
                break;

            case argument_type::Jump_Address:
                f_jump_argument(out, arg->jump_address.data, conf);
                break;

            case argument_type::Branch_Address:
                f_branch_argument(out, arg->branch_address.data, conf);
                break;

            ARG_TYPE_FORMAT(out, arg, Memory_Offset, memory_offset, "%#x");
            ARG_TYPE_FORMAT(out, arg, Immediate_u32, immediate_u32, "%#x");
            case argument_type::Immediate_s32:
            {
                s32 d = arg->immediate_s32.data;

                if (d < 0)
                    format(out, "-%#x", -d);
                else
                    format(out, "%#x", d);

                break;
            }

            ARG_TYPE_FORMAT(out, arg, Immediate_u16, immediate_u16, "%#x");
            case argument_type::Immediate_s16:
            {
                s16 d = arg->immediate_s16.data;

                if (d < 0)
                    format(out, "-%#x", -d);
                else
                    format(out, "%#x", d);

                break;
            }

            ARG_TYPE_FORMAT(out, arg, Immediate_u8,  immediate_u8,  "%#x");
            ARG_TYPE_FORMAT(out, arg, Immediate_float, immediate_float, "%f");
            ARG_TYPE_FORMAT(out, arg, Condition_Code, condition_code, "(CC[%#x])");
            ARG_TYPE_FORMAT(out, arg, Bitfield_Pos, bitfield_pos, "%#x");
            ARG_TYPE_FORMAT(out, arg, Bitfield_Size, bitfield_size, "%#x");

            ARG_TYPE_FORMAT(out, arg, String, string_argument, "%s");

            case argument_type::Extra:
            case argument_type::MAX:
            default:
                break;
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

    for_array(dsec, &conf->dump_sections)
        asm_format_section(conf, dsec, out);
}
