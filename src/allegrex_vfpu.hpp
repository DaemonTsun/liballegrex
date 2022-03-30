
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

enum class vfpu_constant : u8
{
    VFPU_UNDEFINED,
    VFPU_HUGE,
    VFPU_SQRT2,
    VFPU_SQRT1_2,
    VFPU_2_SQRTPI,
    VFPU_PI,
    VFPU_2_PI,
    VFPU_1_PI,
    VFPU_PI_4,
    VFPU_PI_2,
    VFPU_E,
    VFPU_LOG2E,
    VFPU_LOG10E,
    VFPU_LN2,
    VFPU_LN10,
    VFPU_2PI,
    VFPU_PI_6,
    VFPU_LOG10TWO,
    VFPU_LOG2TEN,
    VFPU_SQRT3_2
};

const char *vfpu_constant_name(vfpu_constant constant);

enum class vfpu_prefix : u8
{
    X,
    Y,
    Z,
    W,
    NEG_X,
    NEG_Y,
    NEG_Z,
    NEG_W,
    ABS_X,
    ABS_Y,
    ABS_Z,
    ABS_W,
    NEG_ABS_X,
    NEG_ABS_Y,
    NEG_ABS_Z,
    NEG_ABS_W,
    ZERO,
    ONE,
    TWO,
    HALF,
    THREE,
    THIRD,
    FOURTH,
    SIXTH,
    _MAX
};

const char *vfpu_prefix_name(vfpu_prefix pfx);

struct vfpu_prefix_array
{
    vfpu_prefix data[4];
};

enum class vfpu_destination_prefix : u8
{
    DEFAULT,
    CLAMP_0_1,
    X,
    CLAMP_NEG_1_1,
    M,
    M_CLAMP_0_1,
    M_X,
    M_CLAMP_NEG_1_1,
    _MAX
};

const char *vfpu_destination_prefix_name(vfpu_destination_prefix pfx);

struct vfpu_destination_prefix_array
{
    vfpu_destination_prefix data[4];
};
