
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>

#include "psp_elf.hpp"
#include "parse_instructions.hpp"
#include "format_instructions.hpp"

#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "string.hpp"
#include "number_types.hpp"
#include "config.hpp"

struct arguments
{
    bool emit_glabels;       // -g, --glabel
    std::string output_file; // -o, --output
    std::string log_file;    // --log
    std::string section;     // -s, --section
    std::string decrypted_elf_output; // --dump-decrypt
    bool emit_pseudo;        // -p, --pseudo
    u32 vaddr;               // -a, --vaddr
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
    /* TODO: implement these
    .start_pos = INFER_ADDR, // when specified, only disassemble the given range
    .end_pos = INFER_ADDR,
    */
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
         " -h, --help                  show this help and exit\n"
         " -g, --glabel                emit \"glabel name\" for global labels\n"
         " -o OUTPUT, --output OUTPUT  output filename (default: stdout)\n"
         " --log LOGFILE               output all information messages to LOGFILE (stdout by default)\n"
         " -s, --section NAME          disassemble the section with name NAME (\".text\" by default)\n"
         " --dump-decrypt OUTPUT       optional output file to dump the decrypted ELF to.\n"
         "                             if set, only dumps the ELF to OUTPUT and exits.\n" 
         " -p, --pseudo                emit pseudoinstructions for related instructions\n"
         " -a VADDR, --vaddr VADDR     virtual address of the first instruction\n"
         "                             will be read from elf instead if not set\n"
         " -v, --verbose               verbose progress output\n"
         "\n"
         "Arguments:\n"
         " OBJFILE      ELF object file to disassemble the given section for\n"
         );
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

            out->vaddr = std::stoul(argv[i+1]);
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

void print_instructions(file_stream *stream, const std::vector<instruction> &instr)
{
    for (const instruction &inst : instr)
    {
        format_instruction(stream, &inst);
        stream->write("\n");
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
    // TODO: process symbols
    // are relocations even relevant

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

    print_instructions(&out, pdata.instructions);
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
        return 0;
    }

    disassemble_elf(&in, &log, args);

    return 0;
}
catch (std::runtime_error &e)
{
    fprintf(stderr, "error: %s\n", e.what());
    return 1;
}
