
#include <array>

#include <stdio.h>
#include <string.h>

#include "internal/map_macro.hpp"
#include "internal/psp_module_function_argument_defs.hpp"
#include "internal/psp_module_function_pspdev_headers.hpp"
#include "psp_modules.hpp"

#define CONCAT_(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_(X, Y)
#define S_(x) #x
#define S(x) S_(x)
#define WS(X) CONCAT(L, S(X))
#define C(x) S_(x)[0]
#define WC(x) WS(x)[0]
#define RET(x) WS(x)[0] // same as WC

#define ARGS(...) MAP(WS, __VA_ARGS__)

static_assert(ARGS(a, b, c) == L"abc");

#define NO_ARGS L""

#include "internal/psp_modules.inl"

constexpr psp_function unknown_function{
    0xffffffff, "unknown function",
    L'\0', L"",
    unknown_header, 0xffff, 0xffff
};

constexpr psp_module unknown_module{0xffff, "unknown_module", &unknown_function, 1};

const psp_module *get_psp_modules()
{
    return _modules.data();
}

u32 get_psp_module_count()
{
    return _modules.size();
}

const psp_module *get_psp_module_by_name(const char *mod)
{
    // could be optimized
    for (const psp_module &md : _modules)
        if (strcmp(md.name, mod) == 0)
            return &md;

    return nullptr;
}

const psp_function *get_psp_function_by_nid(const char *mod, u32 nid)
{
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
    const psp_module *md = get_psp_module_by_name(mod);

    if (md == nullptr)
        return nullptr;

    char nidname[256];

    for (int i = 0; i < md->function_count; ++i)
    {
        const psp_function *f = md->functions + i;

        if (strcmp(f->name, name) == 0)
            return f;

        get_psp_function_nid_name(f, nidname);

        if (strcmp(f->name, nidname) == 0)
            return f;
    }

    return nullptr;
}

const psp_function *get_psp_function(u16 mod, u16 fun)
{
    if (mod >= _modules.size())
        return &unknown_function;

    const psp_module &m = _modules.at(mod);
    
    if (fun >= m.function_count)
        return &unknown_function;

    return m.functions + fun;
}

const char *get_psp_module_name(u16 mod)
{
    if (mod >= _modules.size())
        return unknown_module.name;

    return _modules.at(mod).name;
}

const char *get_psp_function_name(u16 mod, u16 fun)
{
    return get_psp_function(mod, fun)->name;
}

void get_psp_function_nid_name(const psp_function *fun, char *dst, u32 sz)
{
    const psp_module *md = &_modules.at(fun->module_num);
    snprintf(dst, sz, "%s_%08X", md->name, fun->nid);
}

const char *get_psp_function_arg_name(psp_function_arg_t arg)
{
    return _get_psp_function_arg_name(arg);
}
