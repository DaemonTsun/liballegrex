
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shl/streams.hpp"
#include "shl/number_types.hpp"
#include "shl/string.hpp"
#include "shl/print.hpp"
#include "shl/error.hpp"
#include "shl/defer.hpp"

#include "allegrex/psp_elf.hpp"
#include "allegrex/parse_instructions.hpp"

#include "psp-elfdump/dump_format.hpp"
#include "psp-elfdump/asm_formatter.hpp"
#include "psp-elfdump/config.hpp"

#define INFER_SIZE UINT32_MAX

struct disasm_range
{
    u32 vaddr;
    u32 start;
    u32 size;
};

struct arguments
{
    const_string output_file; // -o, --output
    const_string log_file;    // --log
    const_string section;     // -s, --section
    const_string decrypted_elf_output; // --dump-decrypt
    u32 vaddr;               // -a, --vaddr
    array<disasm_range> ranges; // -r
    bool verbose;            // -v, --verbose
    // --no-comment
    // --no-comma-separator
    // --no-dollar-registers
    // --no-glabels
    // --no-labels
    // --no-pseudoinstructions
    mips_format_options output_format;
    // --asm (default)
    format_type output_type;

    const_string input_file;
};

const arguments default_arguments{
    .output_file = ""_cs,
    .log_file = ""_cs,
    .section = ""_cs,
    .decrypted_elf_output = ""_cs,
    .vaddr = INFER_VADDR,
    .ranges = {},
    .verbose = false,
    .output_format = default_mips_format_options,
    .output_type = format_type::Asm,
    .input_file = ""_cs
};

static void _print_usage()
{
    puts("Usage: " psp_elfdump_NAME " [-h] [-g] [-o OUTPUT] [-p] [-a VADDR] [-v] OBJFILE\n"
         "\n"
         psp_elfdump_NAME " v" psp_elfdump_VERSION ": little-endian MIPS ELF object file disassembler\n"
         "by " psp_elfdump_AUTHOR "\n"
         "\n"
         "Optional arguments:\n"
         "  -h, --help                  show this help and exit\n"
         "  -o OUTPUT, --output OUTPUT  output filename (default: stdout)\n"
         "  --log LOGFILE               output all information messages to LOGFILE (stdout by default)\n"
         "  -s, --section NAME          disassemble only the section with name NAME (e.g. \".text\")\n"
         "                              if empty, disassembles all executable sections (default).\n"
         "  --dump-decrypt OUTPUT       optional output file to dump the decrypted ELF to.\n"
         "                              if set, only dumps the ELF to OUTPUT and exits.\n" 
         "  -a VADDR, --vaddr VADDR     virtual address of the first instruction\n"
         "                              will be read from elf instead if not set\n"
         "  -r [VADDR:]START[-END]      if set, disassemble the given range of the\n"
         "                              input file. ignores all ELF information.\n"
         "                              if END is omitted, END is end of file.\n"
         "                              -r can be used multiple times.\n"
         "                              if at least one -r is present, only disassembles\n"
         "                              the -r ranges.\n"
         "  -r [VADDR:]START+SIZE       same as above, but uses size instead of end\n"
         "                              position.\n"
         "  -v, --verbose               verbose progress output\n"
         "\n"
         "Formatting options:\n"
         "--no-comment                  omit position/address/opcode comment\n"
         "--no-comma-separator          omit commas between arguments\n"
         "--no-dollar-registers         omit dollars before register names\n"
         "--no-glabels                  omit glabel definitions and in jumps\n"
         "--no-labels                   omit label definitions and in branches\n"
         "--no-pseudoinstructions       don't emit pseudoinstructions\n"
         "\n"
         "--asm                         output assembly (default)\n"
         "\n"
         "Arguments:\n"
         "  OBJFILE      ELF object file to disassemble the given section for\n"
         );
}

static bool _get_file_stream_or_stdout(const_string file, file_stream *out, error *err)
{
    if (is_blank(file))
        out->handle = stdout_handle();
    else if (!init(out, file.c_str, MODE_WRITE_TRUNC, PERMISSION_READ | PERMISSION_WRITE, err))
        return false;

    return true;
}

static bool _parse_range(disasm_range *r, const char *arg, error *err)
{
    const char *n = arg;
    const char *colon = strchr(n, ':');

    if (colon)
    {
        r->vaddr = strtoul(n, nullptr, 0);
        n = colon + 1;
    }
    else
        r->vaddr = INFER_VADDR;

    const char *minus = strchr(n, '-');
    const char *plus = strchr(n, '+');
    r->start = strtoul(n, nullptr, 0);

    if (minus)
    {
        u32 endpos = strtoul(minus + 1, nullptr, 0);
        
        if (endpos < r->start)
        {
            format_error(err, 1, "start offset %x is larger than end offset %x", r->start, endpos);
            return false;
        }

        r->size = endpos - r->start;
    }
    else if (plus)
        r->size = strtoul(plus + 1, nullptr, 0);
    else
        r->size = INFER_SIZE;

    return true;
}

static void _add_symbols_to_jumps(jump_destinations *jumps, hash_table<u32, elf_symbol> *syms)
{
    // this adds symbols as jumps so they appear in the disassembly
    for_hash_table(k, _, syms)
        ::insert_element(jumps, jump_destination{*k, jump_type::Jump});
}

static void _add_imports_to_jumps(jump_destinations *jumps, array<module_import> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::insert_element(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

static void _add_exports_to_jumps(jump_destinations *jumps, array<module_export> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::insert_element(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

static void _format_dump(format_type type, const dump_config *dconf, file_stream *out)
{
    switch (type)
    {
    case format_type::Asm:
        asm_format(dconf, out);
        break;
    }
}

static bool _disassemble_elf(file_stream *in, file_stream *log, const arguments *args, error *err)
{
    memory_stream elf_data{};

    if (!read_entire_file(in, &elf_data, err))
        return false;

    defer { free(&elf_data); };

    psp_parse_elf_config rconf;
    rconf.section = args->section;
    rconf.vaddr = args->vaddr;
    rconf.verbose = args->verbose;
    rconf.log = log;

    elf_psp_module pspmodule;
    init(&pspmodule);
    defer { free(&pspmodule); };

    if (!parse_psp_module_from_elf(&elf_data, &pspmodule, &rconf, err))
        return false;

    jump_destinations jumps{};
    defer { ::free(&jumps); };

    array<instruction_parse_data> instruction_datas;
    ::init(&instruction_datas, pspmodule.sections.size);
    defer { ::free<true>(&instruction_datas); };

    dump_config dconf;
    init(&dconf);
    defer { ::free(&dconf); };

    dconf.log = log;
    dconf.symbols = &pspmodule.symbols;
    dconf.imports = &pspmodule.imports;
    dconf.imported_modules = &pspmodule.imported_modules;
    dconf.exported_modules = &pspmodule.exported_modules;
    dconf.module_info = &pspmodule.module_info;
    dconf.format = args->output_format;
    ::resize(&dconf.dump_sections, pspmodule.sections.size);

    for_array(i, sec, &pspmodule.sections)
    {
        parse_instructions_config pconf;
        pconf.log = log;
        pconf.vaddr = sec->vaddr;
        pconf.verbose = args->verbose;
        pconf.emit_pseudo = is_flag_set(args->output_format, mips_format_options::pseudoinstructions);

        instruction_parse_data *instruction_data = instruction_datas.data + i;
        init(instruction_data);
        instruction_data->jumps = &jumps;
        instruction_data->section_index = (u32)i;

        if (sec->content_size > 0)
            parse_instructions(sec->content, sec->content_size, &pconf, instruction_data);

        dump_section *dumpsec = dconf.dump_sections.data + i;
        dumpsec->section = sec;
        dumpsec->instruction_data = instruction_data;
        dumpsec->first_instruction_offset = sec->content_offset;
    }

    _add_symbols_to_jumps(&jumps, &pspmodule.symbols);
    _add_imports_to_jumps(&jumps, &pspmodule.imported_modules);
    _add_exports_to_jumps(&jumps, &pspmodule.exported_modules);

    file_stream out{};

    if (!_get_file_stream_or_stdout(args->output_file, &out, err))
        return false;

    defer { if (out.handle != stdout_handle()) free(&out); };

    dconf.jumps = &jumps;

    _format_dump(args->output_type, &dconf, &out);

    return true;
}

static bool _dump_decrypted_elf(file_stream *in, file_stream *log, const arguments *args, error *err)
{
    array<u8> decrypted_elf_bytes{};
    defer { free(&decrypted_elf_bytes); };

    u64 sz = decrypt_elf(in, &decrypted_elf_bytes);

    if (sz == 0)
    {
        put("input file is not encrypted. exiting\n");
        return true;
    }
    
    file_stream out{};

    if (!init(&out, args->decrypted_elf_output.c_str, MODE_WRITE_TRUNC, PERMISSION_READ | PERMISSION_WRITE, err))
        return false;

    defer { free(&out); };

    if (write(&out, decrypted_elf_bytes.data, sz, err) < 0)
        return false;

    tprint("dumped decrypted ELF from % to %\n", args->input_file, args->decrypted_elf_output);

    return true;
}

static bool _disassemble_range(file_stream *in, file_stream *out, file_stream *log, const disasm_range *range, const arguments *args, error *err)
{
    u32 from = range->start;
    u32 sz = range->size;

    u32 in_size = (u32)get_file_size(in);

    if (sz == INFER_SIZE)
        sz = in_size - from;

    if (from + sz > in_size)
    {
        format_error(err, 1, "end offset %x (start %x + size %x) is larger than input file size %x", from + sz, from, sz, in_size);
        return false;
    }

    parse_instructions_config pconf;
    pconf.log = log;
    pconf.vaddr = range->vaddr;
    pconf.verbose = args->verbose;
    pconf.emit_pseudo = is_flag_set(args->output_format, mips_format_options::pseudoinstructions);

    if (pconf.vaddr == INFER_VADDR)
        pconf.vaddr = 0;

    if (args->verbose)
        tprint(log->handle, "disassembling range %08x - %08x (size: %08x) with vaddr %08x\n", from, from + sz, sz, pconf.vaddr);

    memory_stream memstr{};
    init(&memstr, sz);
    defer { free(&memstr); };
    
    read_at(in, memstr.data, from, sz);

    instruction_parse_data instruction_data;
    init(&instruction_data);
    defer { free(&instruction_data); };

    jump_destinations jumps{};
    defer { ::free(&jumps); };

    instruction_data.jumps = &jumps;

    parse_instructions(memstr.data, memstr.size, &pconf, &instruction_data);

    dump_config dconf;
    dconf.jumps = &jumps;
    dconf.log = log;
    dconf.format = args->output_format;
    dconf.module_info = nullptr;
    dconf.imported_modules = nullptr;
    dconf.exported_modules = nullptr;

    dump_section *dsec = ::add_at_end(&dconf.dump_sections);
    dsec->section = nullptr;
    dsec->instruction_data = &instruction_data;
    dsec->first_instruction_offset = from;

    _format_dump(args->output_type, &dconf, out);

    if (args->verbose)
        put(log->handle, "\n");

    return true;
}

static bool _disassemble_ranges(file_stream *in, file_stream *log, const arguments *args, error *err)
{
    file_stream out{};

    if (!_get_file_stream_or_stdout(args->output_file, &out, err))
        return false;

    defer { if (out.handle != stdout_handle()) free(&out); };

    for_array(range, &args->ranges)
        if (!_disassemble_range(in, &out, log, range, args, err))
            return false;

    return true;
}

static bool _psp_elfdump(arguments *args, error *err)
{
    if (is_blank(args->input_file))
    {
        set_error(err, 1, "Error: expected input file");
        return false;
    }

    // get logfile
    file_stream log{};

    if (is_blank(args->log_file))
        log.handle = stdout_handle();
    else
    {
        if (!init(&log, args->log_file.c_str, MODE_WRITE, PERMISSION_READ | PERMISSION_WRITE, err))
            return false;

        seek_from_end(&log, 0);
    }

    defer { if (log.handle != stdout_handle()) free(&log); };

    file_stream in{};

    if (!init(&in, args->input_file.c_str, MODE_READ, PERMISSION_READ, err))
        return false;

    defer { free(&in); };

    if (!is_blank(args->decrypted_elf_output))
    {
        if (args->input_file == args->decrypted_elf_output)
        {
            set_error(err, 1, "Error: decrypted elf target output file is same as input file, aborting\n");
            return false;
        }

        return _dump_decrypted_elf(&in, &log, args, err);
    }
    else if (args->ranges.size > 0)
        return _disassemble_ranges(&in, &log, args, err);
    else
        return _disassemble_elf(&in, &log, args, err);

    return true;
}

static bool _parse_arguments(int argc, const char **argv, arguments *out, error *err)
{
    ::init(&out->ranges);

    for (int i = 1; i < argc;)
    {
        const_string arg = to_const_string(argv[i]);

        if (arg == "-h"_cs || arg == "--help"_cs)
        {
            _print_usage();
            return true;
        }

        if (arg == "-o"_cs || arg == "--output"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the output file", arg.c_str);
                return false;
            }

            out->output_file = to_const_string(argv[i + 1]);
            i += 2;
            continue;
        }

        if (arg == "--log"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the log file", arg.c_str);
                return false;
            }

            out->log_file = to_const_string(argv[i + 1]);
            i += 2;
            continue;
        }

        if (arg == "-s"_cs || arg == "--section"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the section name", arg.c_str);
                return false;
            }

            out->section = to_const_string(argv[i + 1]);
            i += 2;
            continue;
        }

        if (arg == "--dump-decrypt"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the output file", arg.c_str);
                return false;
            }

            out->decrypted_elf_output = to_const_string(argv[i + 1]);
            i += 2;
            continue;
        }

        if (arg == "-a"_cs || arg == "--vaddr"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the VADDR", arg.c_str);
                return false;
            }

            out->vaddr = to_unsigned_int(argv[i + 1], nullptr, 0);
            i += 2;
            continue;
        }

        if (arg == "-r"_cs)
        {
            if (i >= argc - 1)
            {
                format_error(err, 1, "%s expects a positional argument: the range", arg.c_str);
                return false;
            }

            disasm_range *range = ::add_at_end(&out->ranges);

            if (!_parse_range(range, argv[i + 1], err))
                return false;

            i += 2;
            continue;
        }

        if (arg == "-v"_cs || arg == "--verbose"_cs)
        {
            out->verbose = true;
            i += 1;
            continue;
        }

        // format
        if (arg == "--no-comment"_cs)
        {
            unset_flag(out->output_format, mips_format_options::comment_pos_addr_instr);
            i += 1;
            continue;
        }

        if (arg == "--no-comma-separator"_cs)
        {
            unset_flag(out->output_format, mips_format_options::comma_separate_args);
            i += 1;
            continue;
        }

        if (arg == "--no-dollar-registers"_cs)
        {
            unset_flag(out->output_format, mips_format_options::dollar_registers);
            i += 1;
            continue;
        }

        if (arg == "--no-glabels"_cs)
        {
            unset_flag(out->output_format, mips_format_options::function_glabels);
            i += 1;
            continue;
        }

        if (arg == "--no-labels"_cs)
        {
            unset_flag(out->output_format, mips_format_options::labels);
            i += 1;
            continue;
        }

        if (arg == "--no-pseudoinstructions"_cs)
        {
            unset_flag(out->output_format, mips_format_options::pseudoinstructions);
            i += 1;
            continue;
        }

        // type
        if (arg == "--asm"_cs)
        {
            out->output_type = format_type::Asm;
            i += 1;
            continue;
        }

        // etc
        if (begins_with(arg, "-"_cs))
        {
            format_error(err, 1, "unknown argument '%s'", arg.c_str);
            return false;
        }

        if (is_blank(out->input_file))
        {
            out->input_file = arg;
            i += 1;
            continue;
        }
        else
        {
            format_error(err, 1, "unexpected argument '%s'", arg.c_str);
            return false;
        }
    }

    return true;
}

int main(int argc, const char **argv)
{
    arguments args = default_arguments;
    error err{};

    if (!_parse_arguments(argc, argv, &args, &err))
    {
        tprint("Error: %\n", err.what);
        return err.error_code;
    }

    defer { ::free(&args.ranges); };

    if (!_psp_elfdump(&args, &err))
    {
        tprint("Error: %\n", err.what);
        return err.error_code;
    }

    return 0;
}
