
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>

#include "string.hpp"
#include "number_types.hpp"
#include "config.hpp"

#define INFER_VADDR UINT32_MAX

struct arguments
{
    bool emit_glabels;       // -g, --glabel
    std::string output_file; // -o, --output
    std::string log_file;    // --log
    bool emit_pseudo;        // -p, --pseudo
    u32 vaddr;               // -a, --vaddr
    bool verbose;            // -v, --verbose

    std::string input_file;
};

const arguments default_arguments{
    .emit_glabels = false,
    .output_file = "",
    .log_file = "",
    .emit_pseudo = false,
    .vaddr = INFER_VADDR,
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
         " -p, --pseudo                emit pseudoinstructions for related instructions\n"
         " -a VADDR, --vaddr VADDR     virtual address of the first instruction\n"
         "                             will be read from elf instead if not set\n"
         " -v, --verbose               verbose progress output\n"
         "\n"
         "Arguments:\n"
         " OBJFILE      ELF object file to disassemble .text section for\n"
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

int main(int argc, const char **argv)
try
{
    arguments args = default_arguments;

    parse_arguments(argc, argv, &args);

    if (args.input_file.empty())
        throw std::runtime_error("expected input file");

    

    return 0;
}
catch (std::runtime_error &e)
{
    printf("error: %s\n", e.what());
    return 1;
}
