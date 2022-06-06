
#include "psp_modules.hpp"
#include "cpp_formatter.hpp"

const char *get_cpp_psp_func_argument_name(psp_function_arg_t arg)
{
    // TODO: implement
    return get_psp_function_arg_name(arg);
}

void print_cpp_module_function_args(FILE *f, const psp_function_arg_t *args)
{
    auto *arg = args;

    if (!*arg)
    {
        fprintf(f, "NO_ARGS");
        return;
    }
    
    fprintf(f, "ARGS(");
    bool first = true;

    while (*arg)
    {
        if (first)
            first = false;
        else
            fprintf(f, ", ");

        fprintf(f, "%s", get_cpp_psp_func_argument_name(*arg));
        ++arg;
    }

    fprintf(f, ")");
}

const char *get_cpp_pspdev_header_file_var(const char *header_file)
{
    // TODO: implement
    return header_file;
}

void print_cpp_module_function(FILE *f, const psp_function *func, bool last)
{
    fprintf(f, "        { 0x%08x, \"%s\",\n", func->nid, func->name);
    fprintf(f, "          RET(%s), ", get_cpp_psp_func_argument_name(func->ret));
    print_cpp_module_function_args(f, func->args);
    fprintf(f, ",\n");
    fprintf(f, "          %s, %u, %u }%s\n", get_cpp_pspdev_header_file_var(func->header_file), func->module_num, func->function_num, last ? "" : ",");
}

// cpp formatter
void print_cpp_module(FILE *f, const psp_module *mod, bool last)
{
    fprintf(f, "\n    psp_module{%u, \"%s\", {\n", mod->module_num, mod->name);

    for (int i = 0; i < mod->functions.size(); ++i)
        print_cpp_module_function(f, &mod->functions.at(i), i+1 == mod->functions.size());

    fprintf(f, "    }}%s\n", last ? "" : ",");
}

void print_cpp_modules(FILE *f)
{
    auto n = get_psp_module_count();
    const psp_module *mods = get_psp_modules();

    fprintf(f, "const std::array _modules\n{");

    for (int i = 0; i < n; ++i)
    {
        const psp_module *mod = &mods[i];

        print_cpp_module(f, mod, i+1 == n);
    }

    fprintf(f, "}\n");
}
