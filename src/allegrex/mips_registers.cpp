
#include "allegrex/mips_registers.hpp"

const char *register_names[] = {
    "zero",     // 0
    "at",       // 1
    "v0", "v1", // 2-3
    "a0", "a1", "a2", "a3", // 4-7
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", // 8-15
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", // 16-23
    "t8", "t9", // 24-25
    "k0", "k1", // 26-27
    "gp", // 28
    "sp", // 29
    "fp", // 30
    "ra"  // 31
};

const char *fpu_register_names[] = {
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
    "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
    "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
    "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31",
};

const char *register_name(mips_register reg)
{
    return register_names[value(reg)];
}

const char *register_name(mips_fpu_register reg)
{
    return fpu_register_names[value(reg)];
}

