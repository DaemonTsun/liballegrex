
#include <stdlib.h>

#include "shl/io.hpp"
#include "shl/print.hpp"
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

static void print_usage()
{
    put("Usage: psp-module-format\n"
        "\n"
        "psp-module-format: formatter tool for psp modules\n"
        "\n"
        "Optional arguments:\n"
        "  -h, --help                  Show this help and exit\n"
        "  -cpp                        use the C++ formatter\n"
        );
}

static void parse_arguments(int argc, const char **argv, arguments *out)
{
    for (int i = 1; i < argc;)
    {
        const_string arg = to_const_string(argv[i]);

        if (arg == "-h"_cs || arg == "--help"_cs)
        {
            print_usage();
            exit(EXIT_SUCCESS);
        }

        if (arg == "-cpp"_cs || arg == "-c++"_cs)
        {
            out->fmt = formatter::Cpp;
            ++i;
            continue;
        }

        ++i;
    }
}

int main(int argc, const char **argv)
{
    arguments args = default_arguments;
    parse_arguments(argc, argv, &args);

    io_handle out = stdout_handle();

    error err{};

    switch (args.fmt)
    {
    case formatter::Default:
        print_modules(out);
        break;
    case formatter::Cpp:
        print_cpp_modules(out, &err);
        break;
    }

    if (err.error_code != 0)
    {
        tprint("Error: %\n", err.what);
        return err.error_code;
    }

    return 0;
}
