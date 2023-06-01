
#pragma once

#include "shl/number_types.hpp"
#include "shl/enum_flag.hpp"

#include "allegrex/psp_modules.hpp"
#include "allegrex/mips_registers.hpp"
#include "allegrex/allegrex_mnemonics.hpp"
#include "allegrex/allegrex_vfpu.hpp"

#define DEFINE_TYPED_ARG(name, type) struct name {type data;}

DEFINE_TYPED_ARG(shift, u8);
struct coprocessor_register
{
    u8 rd;
    u8 sel;
};

DEFINE_TYPED_ARG(base_register, mips_register);
DEFINE_TYPED_ARG(jump_address, u32);
DEFINE_TYPED_ARG(branch_address, u32);
DEFINE_TYPED_ARG(memory_offset, s16);

// immediates
template<typename T = u32>
DEFINE_TYPED_ARG(immediate, T);
DEFINE_TYPED_ARG(condition_code, u8);

// ext, ins
DEFINE_TYPED_ARG(bitfield_size, u32);
DEFINE_TYPED_ARG(bitfield_pos, u32);

// some instructions can have data (e.g. tge) that's not really
// an argument, but we store it anyway
DEFINE_TYPED_ARG(extra, u32);
DEFINE_TYPED_ARG(string_argument, const char *);
// error handling
DEFINE_TYPED_ARG(invalid_argument, const char *);

// these don't perfectly match actual allegrex argument types
enum class argument_type : u8
{
    Invalid,
    MIPS_Register,
    MIPS_FPU_Register,
    VFPU_Register,
    VFPU_Matrix,
    VFPU_Condition,
    VFPU_Constant,
    VFPU_Prefix_Array,
    VFPU_Destination_Prefix_Array,
    VFPU_Rotation_Array,
    PSP_Function_Pointer,
    Shift,
    Coprocessor_Register,
    Base_Register,
    Jump_Address,
    Branch_Address,
    Memory_Offset,
    Immediate_u32,
    Immediate_s32,
    Immediate_u16,
    Immediate_s16,
    Immediate_u8 ,
    Immediate_float,
    Condition_Code,
    Bitfield_Pos,
    Bitfield_Size,
    Extra,
    String,
    MAX
};

// defines value(arg) and argument_type_ut
DEFINE_ENUM_UNDERLYING_TYPE(argument_type);

union instruction_argument
{
    ::invalid_argument invalid_argument;
    ::mips_register mips_register;
    ::mips_fpu_register mips_fpu_register;
    ::vfpu_register vfpu_register;
    ::vfpu_matrix vfpu_matrix;
    ::vfpu_condition vfpu_condition;
    ::vfpu_constant vfpu_constant;
    ::vfpu_prefix_array vfpu_prefix_array;
    ::vfpu_destination_prefix_array vfpu_destination_prefix_array;
    ::vfpu_rotation_array vfpu_rotation_array;
    const ::psp_function *psp_function_pointer;
    ::shift shift;
    ::coprocessor_register coprocessor_register;
    ::base_register base_register;
    ::jump_address jump_address;
    ::branch_address branch_address;
    ::memory_offset memory_offset;
    ::immediate<u32> immediate_u32;
    ::immediate<s32> immediate_s32;
    ::immediate<u16> immediate_u16;
    ::immediate<s16> immediate_s16;
    ::immediate<u8>  immediate_u8;
    ::immediate<float> immediate_float;
    ::condition_code condition_code;
    ::bitfield_pos bitfield_pos;
    ::bitfield_size bitfield_size;
    ::extra extra;
    ::string_argument string_argument;
};

#define MAX_ARGUMENT_COUNT 4

struct instruction
{
    u32 opcode;
    u32 address;
    allegrex_mnemonic mnemonic;

    u32 argument_count; // at most MAX_ARGUMENT_COUNT;
    argument_type argument_types[MAX_ARGUMENT_COUNT];
    instruction_argument arguments[MAX_ARGUMENT_COUNT];
};
