
#include <array>
#include <vector>

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

const char *get_psp_function_arg_name(psp_function_arg_t arg)
{
    return _get_psp_function_arg_name(arg);
}

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
