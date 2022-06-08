
#include "psp_modules.hpp"
#include "default_formatter.hpp"

// default formatter
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

    for (int i = 0; i < mod->function_count; ++i)
        print_module_function(f, mod->functions + i);
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
