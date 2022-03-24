
#pragma once

#include "number_types.hpp"

enum class mips_register : u32
{
    ZERO,   // 0
    AT,     // 1
    V0, V1, // 2-3
    A0, A1, A2, A3, // 4-7
    T0, T1, T2, T3, T4, T5, T6, T7, // 8-15
    S0, S1, S2, S3, S4, S5, S6, S7, // 16-23
    T8, T9, // 24-25
    K0, K1, // 26-27
    GP,     // 28
    SP,     // 29
    FP,     // 30
    RA      // 31
};

enum class mips_fpu_register : u32
{
    F0, F1, F2, F3, F4, F5, F6, F7,
    F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23,
    F24, F25, F26, F27, F28, F29, F30, F31
};

enum class vfpu_size : u32
{
    Single, // M1x1
    Pair,   // M2x2
    Triple, // M3x3
    Quad,   // M4x4
    Unknown
};

struct vfpu_register
{
    u8 num;
    vfpu_size size;
};

struct vfpu_matrix
{
    u8 num;
    vfpu_size size;
};

const char *register_name(mips_register reg);
const char *register_name(mips_fpu_register reg);
const char *register_name(vfpu_register reg);
const char *matrix_name(vfpu_matrix mat);