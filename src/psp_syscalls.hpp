
#pragma once

#include "number_types.hpp"

struct syscall
{
    u32 id;
    const char *function_name;
    u16 module_num;
    u16 function_num;
};

const syscall *get_syscall(u16 mod, u16 fun);
const char *get_module_name(u16 mod);
const char *get_function_name(u16 mod, u16 fun);
