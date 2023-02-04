
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "shl/error.hpp"
#include "default_formatter.hpp"
#include "cpp_formatter.hpp"

// etc
enum class formatter
{
    Default,
    Cpp
};

struct arguments
{
    formatter fmt;
};

constexpr arguments default_arguments{
    .fmt = formatter::Default
};

void print_usage()
{
    puts("Usage: psp-module-format\n"
         "\n"
         "psp-module-format: formatter tool\n"
         "\n"
         "Optional arguments:\n"
         "  -h, --help                  show this help and exit\n"
         "  -cpp                        use the c++ formatter\n"
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

        if (arg == "-cpp" || arg == "-c++")
        {
            out->fmt = formatter::Cpp;
            ++i;
            continue;
        }
    }
}

int main(int argc, const char **argv)
try
{
    arguments args = default_arguments;
    parse_arguments(argc, argv, &args);

    FILE *out = stdout;

    switch (args.fmt)
    {
    case formatter::Default:
        print_modules(out);
        break;
    case formatter::Cpp:
        print_cpp_modules(out);
        break;
    }

    return 0;
}
catch (error &e)
{
    fprintf(stderr, "error: %s\n", e.what);
    return 1;
}
