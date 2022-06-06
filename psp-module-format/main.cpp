
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "psp_modules.hpp"

void print_module_function_args(FILE *f, const psp_function_arg_t *args)
{
    auto *arg = args;
    bool first = true;

    while (*arg)
    {
        if (first)
            first = false;
        else
            fprintf(f, ", ");

        fprintf(f, "%s", get_psp_function_arg_name(*arg));
        ++arg;
    }
}

void print_module_function(FILE *f, const psp_function *func)
{
    fprintf(f, "  0x%08x %s %s(", func->nid, get_psp_function_arg_name(func->ret), func->name);
    print_module_function_args(f, func->args);
    fprintf(f, ")\n");
    fprintf(f, "  %s, %u %u \n\n", func->header_file, func->module_num, func->function_num);
}

void print_module(FILE *f, const psp_module *mod)
{
    fprintf(f, "%u %s\n", mod->module_num, mod->name);

    for (int i = 0; i < mod->functions.size(); ++i)
        print_module_function(f, &mod->functions.at(i));
}

void print_modules(FILE *f)
{
    auto n = get_psp_module_count();
    const psp_module *mods = get_psp_modules();

    for (int i = 0; i < n; ++i)
    {
        const psp_module *mod = &mods[i];

        print_module(f, mod);
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
    print_modules(stdout);

    return 0;
}
catch (std::runtime_error &e)
{
    fprintf(stderr, "error: %s\n", e.what());
    return 1;
}
