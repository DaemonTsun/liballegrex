
#include "shl/print.hpp"

#include "allegrex/psp_modules.hpp"
#include "default_formatter.hpp"

// default formatter
static void _print_module_function_args(io_handle h, const psp_function_arg_t *args)
{
    auto *arg = args;
    bool first = true;

    while (*arg)
    {
        if (first)
            first = false;
        else
            tprint(h, ", ");

        tprint(h, "%s", get_psp_function_arg_name(*arg));
        ++arg;
    }
}

static void _print_module_function(io_handle h, const psp_function *func)
{
    tprint(h, "  0x%08x %s %s(", func->nid, get_psp_function_arg_name(func->ret), func->name);
    _print_module_function_args(h, func->args);
    tprint(h, ")\n");
    tprint(h, "  %s, % % \n\n", func->header_file, func->module_num, func->function_num);
}

static void _print_module(io_handle h, const psp_module *mod)
{
    tprint(h, "% %s\n", mod->module_num, mod->name);

    for (u32 i = 0; i < mod->function_count; ++i)
        _print_module_function(h, mod->functions + i);
}

void print_modules(io_handle h)
{
    u32 n = get_psp_module_count();
    const psp_module *mods = get_psp_modules();

    for (u32 i = 0; i < n; ++i)
        _print_module(h, mods + i);
}
