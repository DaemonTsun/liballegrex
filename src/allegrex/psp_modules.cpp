
#include <stdio.h>
#include <string.h>

#include "shl/fixed_array.hpp"
#include "shl/compiler.hpp"

#include "allegrex/internal/psp_module_function_argument_defs.hpp"
#include "allegrex/internal/psp_module_function_pspdev_headers.hpp"
#include "allegrex/psp_modules.hpp"

#if MSVC
#pragma warning(push)
#pragma warning(disable : 5056) // "deprecated" == operator on array types
#endif

static_assert(ARGS(a, b, c) == L"abc");

#if MSVC
#pragma warning(pop)
#endif

#include "internal/psp_modules.inl"

constexpr psp_function unknown_function{
    0xffffffff, "unknown function",
    L'\0', L"",
    unknown_header, 0xffff, 0xffff
};

constexpr psp_module unknown_module{0xffff, "unknown_module", &unknown_function, 1};

const psp_module *get_psp_modules()
{
    return _modules.data;
}

u32 get_psp_module_count()
{
    return (u32)array_size(&_modules);
}

const psp_module *get_psp_module_by_name(const char *mod)
{
    if (mod == nullptr)
        return nullptr;

    // could be optimized
    for_array(md, &_modules)
        if (strcmp(md->name, mod) == 0)
            return md;

    return nullptr;
}

const psp_function *get_psp_function_by_nid(const char *mod, u32 nid)
{
    if (mod == nullptr)
        return nullptr;

    const psp_module *md = get_psp_module_by_name(mod);

    if (md == nullptr)
        return nullptr;

    // could be optimized even more
    for (int i = 0; i < md->function_count; ++i)
    {
        const psp_function *f = md->functions + i;

        if (f->nid == nid)
            return f;
    }

    return nullptr;
}

const psp_function *get_psp_function_by_name(const char *mod, const char *name)
{
    if (mod == nullptr || name == nullptr)
        return nullptr;

    const psp_module *md = get_psp_module_by_name(mod);

    if (md == nullptr)
        return nullptr;

    char nidname[256];

    for (int i = 0; i < md->function_count; ++i)
    {
        const psp_function *f = md->functions + i;

        if (strcmp(f->name, name) == 0)
            return f;

        get_psp_function_nid_name(f, nidname, 256);

        if (strcmp(nidname, name) == 0)
            return f;
    }

    return nullptr;
}

const psp_function *get_psp_function(u16 mod, u16 fun)
{
    if (mod >= array_size(&_modules))
        return &unknown_function;

    const psp_module *m = _modules.data + mod;
    
    if (fun >= m->function_count)
        return &unknown_function;

    return m->functions + fun;
}

const char *get_psp_module_name(u16 mod)
{
    if (mod >= array_size(&_modules))
        return unknown_module.name;

    return _modules[mod].name;
}

const char *get_psp_function_name(u16 mod, u16 fun)
{
    return get_psp_function(mod, fun)->name;
}

void get_psp_function_nid_name(const psp_function *fun, char *dst, u32 sz)
{
    if (fun == nullptr || dst == nullptr)
        return;

    const psp_module *md = _modules.data + fun->module_num;
    snprintf(dst, sz, "%s_%08X", md->name, fun->nid);
}

const char *get_psp_function_arg_name(psp_function_arg_t arg)
{
    return _get_psp_function_arg_name(arg);
}
