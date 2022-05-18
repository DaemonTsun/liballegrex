
#pragma once

#include "number_types.hpp"

typedef wchar_t psp_function_arg_t;

struct psp_function
{
    u32 nid;
    const char *name;

    psp_function_arg_t ret;
    const psp_function_arg_t *args;

    u16 module_num;
    u16 function_num;

    /* TODO: implement these
     * const char *header_file;
     * const char *lib_name;
     * ??? flags; // user, kernel, etc
     */
};

struct psp_module
{
    const char *name;
    std::vector<psp_function> functions;
};

const psp_function *get_psp_function(u16 mod, u16 fun);
const char *get_psp_module_name(u16 mod);
const char *get_psp_function_name(u16 mod, u16 fun);

const char *get_psp_function_arg_name(psp_function_arg_t arg);
