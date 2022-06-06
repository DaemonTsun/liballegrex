
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "psp_modules.hpp"

void print_module_function(const psp_function *func)
{
    printf("  0x%08x (ret) %s (args) \n", func->nid, func->name);
    printf("  %s, %u %u \n\n", func->header_file, func->module_num, func->function_num);
}

void print_module(const psp_module *mod)
{
    printf("%u %s\n", mod->module_num, mod->name);

    for (int i = 0; i < mod->functions.size(); ++i)
        print_module_function(&mod->functions.at(i));
}

void print_modules()
{
    auto n = get_module_count();
    const psp_module *mods = get_modules();

    for (int i = 0; i < n; ++i)
    {
        const psp_module *mod = &mods[i];

        print_module(mod);
    }
}

// etc
struct arguments
{
    s32 nothing;
};

constexpr arguments default_arguments{
};

void print_usage()
{
    puts("Usage: psp-module-format\n"
         "\n"
         "psp-module-format: formatter tool\n"
         "\n"
         "Optional arguments:\n"
         "  -h, --help                  show this help and exit\n"
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
    }
}

int main(int argc, const char **argv)
try
{
    arguments args = default_arguments;
    parse_arguments(argc, argv, &args);
    print_modules();

    return 0;
}
catch (std::runtime_error &e)
{
    fprintf(stderr, "error: %s\n", e.what());
    return 1;
}
