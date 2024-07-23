
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "shl/string.hpp"
#include "shl/set.hpp"
#include "shl/hash_table.hpp"
#include "shl/error.hpp"
#include "shl/streams.hpp"
#include "shl/print.hpp"
#include "shl/defer.hpp"
#include "shl/platform.hpp"
#include "allegrex/psp_modules.hpp"

#if Windows
#include <windows.h>
#define PATH_MAX MAX_PATH
#elif Linux
#include <linux/limits.h> // PATH_MAX
#include <unistd.h>
#endif

#include "cpp_formatter.hpp"

// cpp formatter

struct _parsed_function_arg
{
    psp_function_arg_t arg;
    const_string name;
};

template<>
inline int compare_ascending_p(const _parsed_function_arg *l, const _parsed_function_arg *r)
{
    return compare_ascending(l->arg, r->arg);
}

static inline int _parsed_function_arg_indexer(const psp_function_arg_t *l, const _parsed_function_arg *r)
{
    return compare_ascending(*l, r->arg);
}

struct _parsed_liballegrex_data
{
    memory_stream functions_file_content;
    memory_stream headers_file_content;
    set<_parsed_function_arg> function_args;
    hash_table<const_string, const_string> headers;
};

void free(_parsed_liballegrex_data *data)
{
    if (data == nullptr)
        return;

    free(&data->functions_file_content);   
    free(&data->headers_file_content);
    free(&data->function_args);   
    free(&data->headers);
}

static void _load_function_args(_parsed_liballegrex_data *data)
{
    const char *content = data->functions_file_content.data;
    s64 i = 0;

    while (i < data->functions_file_content.size)
    {
        if (strncmp(content, "#define", 7) != 0)
        {
            while (*content != '\n' && *content)
            {
                content++;
                i += 1;
            }

            if (*content == '\0')
                break;

            content++;
            i += 1;
            continue;
        }

        const char *arg = strstr(content, "ARG_");
        const char *spc = strstr(arg, " ");

        if (arg == nullptr || spc == nullptr)
            break;

        const_string argname{arg, spc - arg};

        const char *nm = strstr(spc, "\\x") + 2;

        psp_function_arg_t val = static_cast<psp_function_arg_t>(to_unsigned_int(nm, nullptr, 16));

        insert_element(&data->function_args, _parsed_function_arg{val, argname});

        content++;
        i += 1;
    }
}

static void _load_pspdev_headers(_parsed_liballegrex_data *data)
{
    const char *content = data->headers_file_content.data;
    s64 i = 0;

    while (i < data->headers_file_content.size)
    {
        if (strncmp(content, "const char * const", 18) != 0)
        {
            while (*content != '\n' && *content)
            {
                content++;
                i += 1;
            }

            if (*content == '\0')
                break;

            content++;
            i += 1;
            continue;
        }

        content += 19; // length of "const char * const "
        i += 19;
        const char *eq = strstr(content, " = ");

        if (eq == nullptr)
            break;

        const_string header_var_name{content, eq - content};

        const char *qt1 = strstr(eq, "\"");

        if (qt1 == nullptr)
            break;

        qt1++;

        const char *qt2 = strstr(qt1, "\"");

        if (qt2 == nullptr)
            break;

        const_string header_file{qt1, qt2 - qt1};

        data->headers[header_file] = header_var_name;

        content++;
        i += 1;
    }
}

static bool _load_liballegrex_data(_parsed_liballegrex_data *out, error *err)
{
    char pth[PATH_MAX] = {};

#if Windows
    int result = (int)GetModuleFileNameA(0, pth, PATH_MAX - 1);

    if (result == 0)
    {
        set_GetLastError_error(err);
        return false;
    }

    strcpy(strrchr(pth, '\\'), "\\..\\..\\src\\allegrex\\internal\\");
#else
    if (readlink("/proc/self/exe", pth, PATH_MAX) == -1)
    {
        set_errno_error(err);
        return false;
    }

    // we're assuming we're always in a bin folder which is next to src.
    // yes this is terrible.
    strcpy(strrchr(pth, '/'), "/../../src/allegrex/internal/");
#endif

    u64 len = string_length(pth);
    assert((len + 40) < PATH_MAX);
    strcpy(pth + len, "psp_module_function_argument_defs.hpp");

    if (!read_entire_file(pth, &out->functions_file_content, err))
        return false;

    strcpy(pth + len, "psp_module_function_pspdev_headers.hpp");

    if (!read_entire_file(pth, &out->headers_file_content, err))
        return false;

    _load_function_args(out);
    _load_pspdev_headers(out);

    return true;
}

static const_string _get_cpp_psp_func_argument_name(_parsed_liballegrex_data *data, psp_function_arg_t arg)
{
    _parsed_function_arg *p = search(&data->function_args, arg, _parsed_function_arg_indexer);

    if (p == nullptr)
        return const_string{"", 0};

    return p->name;
}

static void _print_cpp_module_function_args(io_handle h, _parsed_liballegrex_data *data, const psp_function_arg_t *args)
{
    auto *arg = args;

    if (*arg == 0)
    {
        put(h, "NO_ARGS");
        return;
    }
    
    put(h, "ARGS(");

    tprint(h, "%", _get_cpp_psp_func_argument_name(data, *arg));

    arg++;

    while (*arg != 0)
    {
        tprint(h, ", %", _get_cpp_psp_func_argument_name(data, *arg));
        ++arg;
    }

    put(h, ")");
}

static const_string _get_cpp_pspdev_header_file_var(_parsed_liballegrex_data *data, const char *header_file)
{
    const_string *ret = search_by_hash(&data->headers, hash(header_file));

    if (ret == nullptr)
        return const_string{"", 0};

    return *ret;
}

static void _print_cpp_module_function(io_handle h, _parsed_liballegrex_data *data, const psp_function *func, bool last)
{
    tprint(h, "    psp_function{ 0x%08x, \"%s\",\n", func->nid, func->name);
    tprint(h, "                  RET(%s), ", _get_cpp_psp_func_argument_name(data, func->ret));
    _print_cpp_module_function_args(h, data, func->args);
    tprint(h, ",\n");
    tprint(h, "                  %, %, % }%s\n", _get_cpp_pspdev_header_file_var(data, func->header_file),
                                                 func->module_num,
                                                 func->function_num,
                                                 last ? "" : ",");
}

static void _print_cpp_module_functions(io_handle h, _parsed_liballegrex_data *data, const psp_module *mod)
{
    tprint(h, "// module %s, id %, % functions\n", mod->name, mod->module_num, mod->function_count);

    if (mod->function_count == 0)
        return;

    tprint(h, "constexpr fixed_array %s%_functions\n{\n", mod->name, mod->module_num);

    for (u32 i = 0; i < mod->function_count; ++i)
        _print_cpp_module_function(h, data, mod->functions + i, (i + 1) == mod->function_count);

    tprint(h, "};\n\n");
}

static void _print_cpp_module(io_handle h, const psp_module *mod, bool last)
{
    tprint(h, "    %s", mod->function_count > 0 ? "DEFINE_PSP_MODULE" : "DEFINE_EMPTY_PSP_MODULE");
    tprint(h, "(%, %s)%s\n", mod->module_num, mod->name, last ? "" : ",");
}

bool print_cpp_modules(io_handle h, error *err)
{
    _parsed_liballegrex_data data{};
    defer { free(&data); };

    if (!_load_liballegrex_data(&data, err))
        return false;

    const psp_module *mods = get_psp_modules();
    u32 mod_count = get_psp_module_count();

    tprint(h, "/* The list of modules included by src/allegrex/psp_modules.cpp.\n"
              "See src/allegrex/psp_modules.hpp for the structure of modules\n"
              "and functions.\n"
              "\n"
              "https://github.com/hrydgard/ppsspp/blob/master/Core/HLE/HLE.cpp\n"
              "https://github.com/hrydgard/ppsspp/blob/master/Core/HLE/HLETables.cpp\n"
              "\n"
              "Not auto generated anymore using PPSSPPs HLE modules.\n"
              "You can generate most of this by iterating moduleDB & formatting print in HLE.cpp.\n"
              "Now it's self-generated, i.e. this file is parsed by psp-module-format and\n"
              "regenerated using the compiled information from liballegrex.\n"
              "*/\n");


    for (u32 i = 0; i < mod_count; ++i)
        _print_cpp_module_functions(h, &data, mods + i);

    tprint(h, "\n#define DEFINE_PSP_MODULE(NUM, NAME)\\\n");
    tprint(h, "  psp_module{NUM, #NAME, NAME##NUM##_functions.data, (u32)array_size(&NAME##NUM##_functions)}\n\n");

    tprint(h, "#define DEFINE_EMPTY_PSP_MODULE(NUM, NAME)\\\n");
    tprint(h, "  psp_module{NUM, #NAME, nullptr, 0}\n\n");

    tprint(h, "constexpr fixed_array _modules\n{\n");

    for (u32 i = 0; i < mod_count; ++i)
        _print_cpp_module(h, mods + i, (i + 1) == mod_count);

    tprint(h, "};\n");

    return true;
}
