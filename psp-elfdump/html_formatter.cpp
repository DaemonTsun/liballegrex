
#include <assert.h>
#include <string.h>

#include "string.hpp"
#include "instruction.hpp"
#include "internal/psp_module_function_pspdev_headers.hpp"
#include "psp-elfdump/html_formatter.hpp"

const char *pspsdk_github_base_src_url = "https://github.com/pspdev/pspsdk/tree/master/src/";

#define html_fmt_number(out, num, FMT) \
    out->format("<a class=\"num\">" FMT "</a>", num);

void html_fmt_jump_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("<a class=\"addr\">0x%08x</a>", address);
}

void html_fmt_jump_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    // exports (unoptimized, but probably not too common)
    const char *name = nullptr;

    for (int i = 0; i < conf->exported_modules->size(); ++i)
    {
        for (const auto &f : conf->exported_modules->at(i).functions)
            if (f.address == address)
            {
                name = f.function->name;
                break;
            }

        if (name)
            break;
    }

    if (name != nullptr)
    {
        out->format("<a class=\"export\">%s</a>", name);
        return;
    }

    // imports
    auto it2 = conf->imports->find(address);

    if (it2 != conf->imports->end())
    {
        auto *_import = it2->second.function;
        const char *header = _import->header_file;
        name = _import->name;

        if (strlen(header) == 0
         || strcmp(header, unknown_header) == 0)
        {
            out->format("<a class=\"uimport\">%s</a>", name);
        }
        else
        {
            out->format("<a class=\"import\" href=\"%s%s\">%s</a>", pspsdk_github_base_src_url, header, name);
        }

        return;
    }

    // symbols
    auto it = conf->symbols->find(address);

    if (it != conf->symbols->end())
    {
        name = it->second.name.c_str();
        // symbol name
        out->format("<a class=\"symbol\">%s</a>", name);
        
        return;
    }

    out->format("<a class=\"jlabel\">func_%08x</a>", address);
}

void html_fmt_branch_address_number(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("<a class=\"addr\">0x%08x</a>", address);
}

void html_fmt_branch_address_label(file_stream *out, u32 address, const dump_config *conf)
{
    // we could use symbols for lookup, but these are just branch
    // labels, not jumps usually.
    out->format("<a class=\"blabel\">.L%08x</a>", address);
}

void html_fmt_jump_glabel(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("glabel ");

    html_fmt_jump_address_label(out, address, conf);
}

void html_fmt_branch_label(file_stream *out, u32 address, const dump_config *conf)
{
    out->format("<a class=\"blabel\">.L%08x</a>:", address);
}

void html_fmt_mips_register_name(file_stream *out, mips_register reg)
{
    out->format("<a class=\"reg\">%s</a>", register_name(reg));
}

void html_fmt_dollar_mips_register_name(file_stream *out, mips_register reg)
{
    out->format("<a class=\"reg\">$%s</a>", register_name(reg));
}

void html_fmt_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    out->format("<a class=\"reg_fpu\">%s</a>", register_name(reg));
}

void html_fmt_dollar_mips_fpu_register_name(file_stream *out, mips_fpu_register reg)
{
    out->format("<a class=\"reg_fpu\">$%s</a>", register_name(reg));
}

void html_fmt_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    out->format("<a class=\"reg_vfpu\">%s%s</a>", register_name(reg), size_suffix(reg.size));
}

void html_fmt_dollar_vfpu_register_name(file_stream *out, vfpu_register reg)
{
    out->format("<a class=\"reg_vfpu\">$%s%s</a>", register_name(reg), size_suffix(reg.size));
}

void html_fmt_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    out->format("<a class=\"mat_vfpu\">%s%s</a>", matrix_name(mtx), size_suffix(mtx.size));
}

void html_fmt_dollar_vfpu_matrix_name(file_stream *out, vfpu_matrix mtx)
{
    out->format("<a class=\"mat_vfpu\">$%s%s</a>", matrix_name(mtx), size_suffix(mtx.size));
}

void html_format_instruction_name(file_stream *out, const instruction *inst)
{
    const char *name = get_mnemonic_name(inst->mnemonic);

    if (requires_vfpu_suffix(inst->mnemonic))
    {
        vfpu_size sz = get_vfpu_size(inst->opcode);
        const char *suf = size_suffix(sz);
        auto fullname = str(name, suf); // slow lol

        out->format(" <pre>%-10s</pre>", fullname.c_str());
    }
    else
        out->format(" <pre>%-10s</pre>", name);
}

void html_format_header(const dump_config *conf, file_stream *out)
{
    const prx_sce_module_info *module_info = conf->module_info;
    const char *module_name = module_info ? module_info->name : "[unknown]";

    out->format(R"=(
<head>
  <title>
    %s
  </title>
)=", module_name);

    out->format(
#include "disasm.css"
    );

    out->format("</head>\n");
}

void html_format_module_info(const dump_config *conf, const prx_sce_module_info *module_info, file_stream *out)
{
    if (module_info == nullptr)
    {
        out->format("  <div class=\"block module_info\">[unknown]</div>");
        return;
    }

    // TODO: anchor, attributes, version, imports, exports
    out->format(R"=(
  <div class="block module_info">
    <span>%s</span><hr/>
  </div><br/>
)=", module_info->name);
}

#define ARG_HOLDS_T_FORMAT(out, arg, T, FMT) \
    (std::holds_alternative<T>(arg)) \
    { \
        out->format(FMT, std::get<T>(arg).data); \
    }

#define ARG_HOLDS_NUMBER_FORMAT(out, arg, T, FMT) \
    (std::holds_alternative<T>(arg)) \
    { \
        html_fmt_number(out, std::get<T>(arg).data, FMT); \
    }

#define holds_type std::holds_alternative

void html_format_section(const dump_config *conf, const dump_section *dsec, file_stream *out)
{
    const elf_section *sec = dsec->section;
    const jump_destination_array *jumps = conf->jump_destinations;

    u32 max_instruction_offset = dsec->first_instruction_offset + dsec->pdata->instructions.size() * sizeof(u32);
    u32 pos_digits = hex_digits(max_instruction_offset);
    char pos_vaddr_code_format_string[256] = {0};

    sprintf(pos_vaddr_code_format_string,
R"=(<a class="opcode_data">%%0%ux %%08x %%08x</a>)=", pos_digits);

    // format functions
    auto f_mips_register_name = html_fmt_mips_register_name;
    auto f_mips_fpu_register_name = html_fmt_mips_fpu_register_name;
    auto f_vfpu_register_name = html_fmt_vfpu_register_name;
    auto f_vfpu_matrix_name = html_fmt_vfpu_matrix_name;
    auto f_argument_sep = fmt_argument_space;
    auto f_jump_argument = html_fmt_jump_address_number;
    auto f_branch_argument = html_fmt_branch_address_number;
    auto f_jump_glabel = html_fmt_jump_glabel;
    auto f_branch_label = html_fmt_branch_label;

    if (is_set(conf->format, format_options::dollar_registers))
    {
        f_mips_register_name = html_fmt_dollar_mips_register_name;
        f_mips_fpu_register_name = html_fmt_dollar_mips_fpu_register_name;
        f_vfpu_register_name = html_fmt_dollar_vfpu_register_name;
        f_vfpu_matrix_name = html_fmt_dollar_vfpu_matrix_name;
    }

    if (is_set(conf->format, format_options::comma_separate_args))
        f_argument_sep = fmt_argument_comma_space;

    if (is_set(conf->format, format_options::function_glabels))
        f_jump_argument = html_fmt_jump_address_label;
    else
        f_jump_glabel = nullptr;

    if (is_set(conf->format, format_options::labels))
        f_branch_argument = html_fmt_branch_address_label;
    else
        f_branch_label = nullptr;

    u32 pos = dsec->first_instruction_offset;
    u32 jmp_i = 0;

    if (!is_set(conf->format, format_options::function_glabels)
     && !is_set(conf->format, format_options::labels))
        jmp_i = UINT32_MAX;
    else
        while (jmp_i < jumps->size() && jumps->at(jmp_i).address < dsec->pdata->vaddr)
            ++jmp_i;
    
    // start writing
    out->format("  <div class=\"block section\">\n");

    // TODO: anchor, offset, size, content
    out->format("    <span>%s</span><hr/>\n", dsec->section->name.c_str());

    bool first_function = true;
    u32 n_blocks = 0; // TODO: remove

    for (const instruction &inst : dsec->pdata->instructions)
    {
        bool write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);

        while (write_label)
        {
            auto &jmp = jumps->at(jmp_i);

            if (jmp.type == jump_type::Jump)
            {
                if (f_jump_glabel != nullptr)
                {
                    if (first_function)
                        first_function = false;
                    else
                        out->format("</div>\n");

                    out->format("<div class=\"block function\">\n");

                    out->format("<a class=\"function\">\n");
                    f_jump_glabel(out, jmp.address, conf);
                    out->format("</a><br/>\n");

                    if (++n_blocks > 20) // TODO: remove
                        goto outer_loop_end;
                }
            }
            else
            {
                if (f_branch_label != nullptr)
                {
                    out->format("<a class=\"branch\">\n");
                    f_branch_label(out, jmp.address, conf);
                    out->format("</a><br/>\n");
                }
            }

            jmp_i++;
            write_label = (jmp_i < jumps->size()) && (jumps->at(jmp_i).address <= inst.address);
        }

        out->format(pos_vaddr_code_format_string, pos, inst.address, inst.opcode);

        html_format_instruction_name(out, &inst);

        bool first_arg = true;
        for (auto &arg : inst.arguments)
        {
            if (!first_arg && !holds_type<base_register>(arg))
                f_argument_sep(out);

            first_arg = false;

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
                f_vfpu_matrix_name(out, std::get<vfpu_matrix>(arg));

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
                {
                    html_fmt_number(out, -d, "-%#x");
                }
                else
                {
                    html_fmt_number(out, d, "%#x");
                }
            }

            else if (holds_type<immediate<s16>>(arg))
            {
                s16 d = std::get<immediate<s16>>(arg).data;
                if (d < 0)
                {
                    html_fmt_number(out, -d, "-%#x");
                }
                else
                {
                    html_fmt_number(out, d, "%#x");
                }
            }

            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, shift,            "%#x")
            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, memory_offset,    "%#x")
            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, immediate<u32>,   "%#x")
            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, immediate<u16>,   "%#x")
            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, immediate<u8>,    "%#x")
            else if ARG_HOLDS_NUMBER_FORMAT(out, arg, immediate<float>, "%f")
            else if ARG_HOLDS_T_FORMAT(out, arg, condition_code,   "(CC[%#x])")
            else if ARG_HOLDS_T_FORMAT(out, arg, bitfield_pos,     "%#x")
            else if ARG_HOLDS_T_FORMAT(out, arg, bitfield_size,    "%#x")
            else if (holds_type<coprocessor_register>(arg))
            {
                auto &d = std::get<coprocessor_register>(arg);
                out->format("[%u, %u]", d.rd, d.sel);
            }
        }

        out->format("<br/>\n");
        pos += sizeof(u32);
    }

outer_loop_end:

    if (!first_function)
        out->format("</div><br/>");

    out->format("  </div><br/>\n"); // section block
}

void html_format_body(const dump_config *conf, file_stream *out)
{
    out->format("<body>");

    html_format_module_info(conf, conf->module_info, out);

    for (const dump_section &dsec : conf->dump_sections)
        html_format_section(conf, &dsec, out);

    out->format("</body>\n");
}

void html_format(const dump_config *conf, file_stream *out)
{
    assert(conf != nullptr);
    assert(out != nullptr);

    out->format("<html>");
    html_format_header(conf, out);

    html_format_body(conf, out);

    out->format("</html>");
}
