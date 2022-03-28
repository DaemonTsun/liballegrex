
#pragma once

#include "number_types.hpp"

enum class vfpu_size : u32
{
    Single, // M1x1
    Pair,   // M2x2
    Triple, // M3x3
    Quad,   // M4x4
    Invalid
};

constexpr vfpu_size half_size(vfpu_size sz)
{
    switch (sz)
    {
    case vfpu_size::Pair: return vfpu_size::Single;
    case vfpu_size::Quad: return vfpu_size::Pair;
    default: return vfpu_size::Invalid;
    }
}

constexpr vfpu_size double_size(vfpu_size sz)
{
    switch (sz)
    {
    case vfpu_size::Single: return vfpu_size::Pair;
    case vfpu_size::Pair: return vfpu_size::Quad;
    default: return vfpu_size::Invalid;
    }
}

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

const char *register_name(vfpu_register reg);
const char *matrix_name(vfpu_matrix mat);

constexpr inline vfpu_size get_vfpu_size(u32 opcode)
{
    u32 a = bitrange(opcode, 7, 7);
    u32 b = bitrange(opcode, 15, 15);
    u32 sz = a + (b << 1);

    return static_cast<vfpu_size>(sz);
}

const char *size_suffix(vfpu_size sz);
const char *size_suffix(vfpu_size opcode);

enum class vfpu_condition : u32
{
    FL,
    EQ,
    LT,
    LE,
    TR,
    NE,
    GE,
    GT,
    EZ,
    EN,
    EI,
    ES,
    NZ,
    NN,
    NI,
    NS
};

const char *vfpu_condition_name(vfpu_condition cond);

const char *vfpu_constant_name(u32 constant);
