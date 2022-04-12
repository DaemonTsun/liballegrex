
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "psp_elf.hpp"
#include "parse_instructions.hpp"

#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "string.hpp"
#include "number_types.hpp"

#include "psp-elfdump/dump_format.hpp"
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
    bool emit_glabels;       // -g, --glabel
    std::string output_file; // -o, --output
    std::string log_file;    // --log
    std::string section;     // -s, --section
    std::string decrypted_elf_output; // --dump-decrypt
    bool emit_pseudo;        // -p, --pseudo
    u32 vaddr;               // -a, --vaddr
    std::vector<disasm_range> ranges; // -r
    bool verbose;            // -v, --verbose

    std::string input_file;
};

const arguments default_arguments{
    .emit_glabels = false,
    .output_file = "",
    .log_file = "",
    .section = ".text",
    .decrypted_elf_output = "",
    .emit_pseudo = false,
    .vaddr = INFER_VADDR,
    .ranges = {},
    .verbose = false,
    .input_file = ""
};

void print_usage()
{
    puts("Usage: " PSP_ELFDUMP_NAME " [-h] [-g] [-o OUTPUT] [-p] [-a VADDR] [-v] OBJFILE\n"
         "\n"
         PSP_ELFDUMP_NAME " v" PSP_ELFDUMP_VERSION ": little-endian MIPS ELF object file disassembler\n"
         "by " PSP_ELFDUMP_AUTHOR "\n"
         "\n"
         "Optional arguments:\n"
         "  -h, --help                  show this help and exit\n"
         "  -g, --glabel                emit \"glabel name\" for global labels\n"
         "  -o OUTPUT, --output OUTPUT  output filename (default: stdout)\n"
         "  --log LOGFILE               output all information messages to LOGFILE (stdout by default)\n"
         "  -s, --section NAME          disassemble the section with name NAME (\".text\" by default)\n"
         "  --dump-decrypt OUTPUT       optional output file to dump the decrypted ELF to.\n"
         "                              if set, only dumps the ELF to OUTPUT and exits.\n" 
         "  -p, --pseudo                emit pseudoinstructions for related instructions\n"
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
         "Arguments:\n"
         "  OBJFILE      ELF object file to disassemble the given section for\n"
         );
}

void parse_range(disasm_range *r, const char *arg)
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
            throw std::runtime_error(str("start offset 0x", std::hex, r->start, " is larger than end offset 0x", std::hex, endpos));

        r->size = endpos - r->start;
    }
    else if (plus)
        r->size = strtoul(plus + 1, nullptr, 0);
    else
        r->size = INFER_SIZE;
}

void parse_arguments(int argc, const char **argv, arguments *out)
{
    for (int i = 1; i < argc;)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            print_usage();
            exit(EXIT_SUCCESS);
        }

        if (arg == "-g" || arg == "--glabel")
        {
            out->emit_glabels = true;
            ++i;
            continue;
        }

        if (arg == "-o" || arg == "--output")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the output file"));

            out->output_file = argv[i+1];
            i += 2;
            continue;
        }

        if (arg == "--log")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the log file"));

            out->log_file = argv[i+1];
            i += 2;
            continue;
        }

        if (arg == "-s" || arg == "--section")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the section name"));

            out->section = argv[i+1];
            i += 2;
            continue;
        }

        if (arg == "--dump-decrypt")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the output file"));

            out->decrypted_elf_output = argv[i+1];
            i += 2;
            continue;
        }

        if (arg == "-p" || arg == "--pseudo")
        {
            out->emit_pseudo = true;
            ++i;
            continue;
        }

        if (arg == "-a" || arg == "--vaddr")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the VADDR"));

            out->vaddr = std::stoul(argv[i+1], nullptr, 0);
            i += 2;
            continue;
        }

        if (arg == "-r")
        {
            if (i >= argc - 1)
                throw std::runtime_error(str(arg, " expects a positional argument: the range"));

            disasm_range &range = out->ranges.emplace_back();
            parse_range(&range, argv[i+1]);
            i += 2;
            continue;
        }

        if (arg == "-v" || arg == "--verbose")
        {
            out->verbose = true;
            ++i;
            continue;
        }

        if (begins_with(arg, str("-")))
            throw std::runtime_error(str("unknown argument '", arg, "'"));

        if (out->input_file.empty())
        {
            out->input_file = arg;
            ++i;
            continue;
        }
        else
            throw std::runtime_error(str("unexpected argument '", arg, "'"));
    }
}

void disassemble_elf(file_stream *in, file_stream *log, const arguments &args)
{
    psp_elf_read_config rconf;
    rconf.log = log;
    rconf.section = args.section;
    rconf.vaddr = args.vaddr;
    rconf.verbose = args.verbose;

    elf_section sec;
    read_elf(in, &rconf, &sec);

    parse_config pconf;
    pconf.log = log;
    pconf.vaddr = sec.vaddr;
    pconf.verbose = args.verbose;
    pconf.emit_pseudo = args.emit_pseudo;

    parse_data pdata;
    parse_allegrex(&sec.content, &pconf, &pdata);

    FILE *outfd = stdout;

    if (!args.output_file.empty())
        outfd = fopen(args.output_file.c_str(), "w");

    file_stream out(outfd);

    if (!out)
        throw std::runtime_error("could not open output file");

    dump_config dconf;
    dconf.out = &out;
    dconf.log = log;
    dconf.section = &sec;
    dconf.pdata = &pdata;
    dconf.first_instruction_offset = sec.content_offset;

    dump_format(&dconf);
}

void dump_decrypted_elf(file_stream *in, file_stream *log, const arguments &args)
{
    std::vector<u8> delf;
    auto sz = decrypt_elf(in, &delf);

    if (sz == 0)
    {
        printf("input file is not encrypted. exiting\n");
        return;
    }
    
    FILE *outfd = fopen(args.decrypted_elf_output.c_str(), "w");

    file_stream out(outfd);

    if (!out)
        throw std::runtime_error("could not open dump output file");

    out.write(delf.data(), sz);

    printf("dumped decrypted ELF from %s to %s\n", args.input_file.c_str(), args.decrypted_elf_output.c_str());
}

void disassemble_range(file_stream *in, file_stream *log, const disasm_range *range, const arguments &args)
{
    u32 from = range->start;
    u32 sz = range->size;

    if (sz == INFER_SIZE)
        sz = in->size() - from;

    if (from + sz > in->size())
        throw std::runtime_error(str("end offset 0x", std::hex, from + sz, " (start 0x", std::hex, from, " + size 0x", std::hex, sz, ") is larger than input file size 0x", std::hex, in->size()));

    parse_config pconf;
    pconf.log = log;
    pconf.vaddr = range->vaddr;
    pconf.verbose = args.verbose;
    pconf.emit_pseudo = args.emit_pseudo;

    if (pconf.vaddr == INFER_VADDR)
        pconf.vaddr = 0;

    if (args.verbose)
        log->format("disassembling range %08x - %08x (size: %08x) with vaddr %08x\n", from, from + sz, sz, pconf.vaddr);

    auto memstr = memory_stream(sz);
    in->read_at(memstr.data(), from, sz);

    parse_data pdata;
    parse_allegrex(&memstr, &pconf, &pdata);

    FILE *outfd = stdout;

    if (!args.output_file.empty())
        outfd = fopen(args.output_file.c_str(), "w");

    file_stream out(outfd);

    if (!out)
        throw std::runtime_error("could not open output file");

    dump_config dconf;
    dconf.out = &out;
    dconf.log = log;
    dconf.section = nullptr;
    dconf.pdata = &pdata;
    dconf.first_instruction_offset = from;

    dump_format(&dconf);

    if (args.verbose)
        log->write("\n");
}

void disassemble_ranges(file_stream *in, file_stream *log, const arguments &args)
{
    for (auto &range : args.ranges)
        disassemble_range(in, log, &range, args);
}

int main(int argc, const char **argv)
try
{
    arguments args = default_arguments;

    parse_arguments(argc, argv, &args);

    if (args.input_file.empty())
        throw std::runtime_error("expected input file");

    // get logfile
    FILE *logfd = stdout;

    if (!args.log_file.empty())
        logfd = fopen(args.log_file.c_str(), "a");

    file_stream log(logfd);

    if (!log)
        throw std::runtime_error("could not open file to log");

    file_stream in(args.input_file, "rb");

    if (!in)
        throw std::runtime_error("could not open input file");

    in.calculate_size();
    
    if (!args.decrypted_elf_output.empty())
    {
        if (args.input_file == args.decrypted_elf_output)
            throw std::runtime_error("decrypted elf target output file is same as input file, aborting");

        dump_decrypted_elf(&in, &log, args);
    }
    else if (!args.ranges.empty())
        disassemble_ranges(&in, &log, args);
    else
        disassemble_elf(&in, &log, args);

    return 0;
}
catch (std::runtime_error &e)
{
    fprintf(stderr, "error: %s\n", e.what());
    return 1;
}
