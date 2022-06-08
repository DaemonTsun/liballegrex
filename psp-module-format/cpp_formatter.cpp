
#include <map>
#include <unordered_map>
#include <exception>
#include <string>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>

#include "string.hpp"
#include "psp_modules.hpp"
#include "cpp_formatter.hpp"

// cpp formatter

struct liballegrex_data_t
{
    std::map<psp_function_arg_t, std::string> function_args;
    std::unordered_map<std::string, std::string> headers;
};

static liballegrex_data_t *lib_data = nullptr;

typedef void (*parse_handler)(const char *);

void load_function_args(const char *content)
{
    while (*content)
    {
        if (strncmp(content, "#define", 7) != 0)
        {
            while (*content != '\n' && *content)
                ++content;

            if (*content == '\0')
                break;

            ++content;
            continue;
        }

        const char *arg = strstr(content, "ARG_");
        const char *spc = strstr(arg, " ");

        if (arg == nullptr || spc == nullptr)
            break;

        std::string argname(arg, spc - arg);

        const char *nm = strstr(spc, "\\x") + 2;

        psp_function_arg_t val = static_cast<psp_function_arg_t>(strtol(nm, nullptr, 16));

        lib_data->function_args[val] = argname;

        ++content;
    }
}

void load_pspdev_headers(const char *content)
{
    while (*content)
    {
        if (strncmp(content, "const char * const", 18) != 0)
        {
            while (*content != '\n' && *content)
                ++content;

            if (*content == '\0')
                break;

            ++content;
            continue;
        }

        content += 19; // length of const char * const 
        const char *eq = strstr(content, " = ");

        if (eq == nullptr)
            break;

        std::string header_var_name(content, eq - content);

        const char *qt1 = strstr(eq, "\"");

        if (qt1 == nullptr)
            break;

        qt1++;

        const char *qt2 = strstr(qt1, "\"");

        if (qt2 == nullptr)
            break;

        std::string header_file(qt1, qt2 - qt1);

        lib_data->headers[header_file] = header_var_name;

        ++content;
    }
}

void parse_file(const char *path, const char *filename, parse_handler handler)
{
    char arg_def_file_path[PATH_MAX];
    strcpy(arg_def_file_path, path);
    strcpy(arg_def_file_path + strlen(path), filename);

    FILE *f = fopen(arg_def_file_path, "r");

    if (f == nullptr)
        throw std::runtime_error(str("could not open file ", arg_def_file_path));

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *content = reinterpret_cast<char*>(malloc(fsize + 1));
    fread(content, fsize, 1, f);
    fclose(f);

    try
    {
        handler(content);
    }
    catch (std::exception &e)
    {
        free(content);
        throw e;
        return;
    }

    free(content);
}

void load_liballegrex_data()
{
    if (lib_data)
        return;

    lib_data = new liballegrex_data_t;

    char pth[PATH_MAX];
    readlink("/proc/self/exe", pth, PATH_MAX);

    // we're assuming we're always in a bin folder which is next to src.
    // yes this is terrible.
    strcpy(strrchr(pth, '/'), "/../../src/internal/");

    parse_file(pth, "psp_module_function_argument_defs.hpp", load_function_args);
    parse_file(pth, "psp_module_function_pspdev_headers.hpp", load_pspdev_headers);
}

const char *get_cpp_psp_func_argument_name(psp_function_arg_t arg)
{
    auto it = lib_data->function_args.find(arg);

    assert(it != lib_data->function_args.end());
    return it->second.c_str();
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
    auto it = lib_data->headers.find(std::string(header_file));

    assert(it != lib_data->headers.end());
    return it->second.c_str();
}

void print_cpp_module_function(FILE *f, const psp_function *func, bool last)
{
    fprintf(f, "    psp_function{ 0x%08x, \"%s\",\n", func->nid, func->name);
    fprintf(f, "                  RET(%s), ", get_cpp_psp_func_argument_name(func->ret));
    print_cpp_module_function_args(f, func->args);
    fprintf(f, ",\n");
    fprintf(f, "                  %s, %u, %u }%s\n", get_cpp_pspdev_header_file_var(func->header_file), func->module_num, func->function_num, last ? "" : ",");
}

void print_cpp_module_functions(FILE *f, const psp_module *mod)
{
    fprintf(f, "// module %s, id %u, %u functions\n", mod->name, mod->module_num, mod->function_count);

    if (mod->function_count == 0)
        return;

    fprintf(f, "constexpr std::array %s%u_functions\n{\n", mod->name, mod->module_num);

    for (int i = 0; i < mod->function_count; ++i)
        print_cpp_module_function(f, mod->functions + i, i+1 == mod->function_count);

    fprintf(f, "};\n\n");
}

void print_cpp_module(FILE *f, const psp_module *mod, bool last)
{
    fprintf(f, "    %s", mod->function_count > 0 ? "DEFINE_PSP_MODULE" : "DEFINE_EMPTY_PSP_MODULE");
    fprintf(f, "(%u, %s)%s\n", mod->module_num, mod->name, last ? "" : ",");
}

void print_cpp_modules(FILE *f)
{
    load_liballegrex_data();

    auto n = get_psp_module_count();
    const psp_module *mods = get_psp_modules();

    fprintf(f, "// the list of modules included by src/psp_modules.cpp.\n"
               "// see src/psp_modules.hpp for the structure of modules\n"
               "// and functions.\n"
               "\n"
               "// https://github.com/hrydgard/ppsspp/blob/master/Core/HLE/HLE.cpp\n"
               "// https://github.com/hrydgard/ppsspp/blob/master/Core/HLE/HLETables.cpp\n"
               "\n"
               "// not auto generated anymore using PPSSPPs HLE modules.\n"
               "// you can generate most of this\n"
               "// (just iterating moduleDB & formatting print in HLE.cpp)\n"
               "// now it's self-generated.\n"
               "\n");


    for (int i = 0; i < n; ++i)
    {
        const psp_module *mod = &mods[i];
        print_cpp_module_functions(f, mod);
    }

    fprintf(f, "\n#define DEFINE_PSP_MODULE(NUM, NAME)\\\n");
    fprintf(f, "  psp_module{NUM, #NAME, NAME##NUM##_functions.data(), NAME##NUM##_functions.size()}\n\n");

    fprintf(f, "#define DEFINE_EMPTY_PSP_MODULE(NUM, NAME)\\\n");
    fprintf(f, "  psp_module{NUM, #NAME, nullptr, 0}\n\n");

    fprintf(f, "constexpr std::array _modules\n{\n");

    for (int i = 0; i < n; ++i)
    {
        const psp_module *mod = &mods[i];
        print_cpp_module(f, mod, i+1 == n);
    }

    fprintf(f, "};\n");
}
