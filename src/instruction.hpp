
#pragma once

#include <vector>
#include <variant>

#include "psp_modules.hpp"
#include "mips_registers.hpp"
#include "allegrex_mnemonics.hpp"
#include "allegrex_vfpu.hpp"
#include "number_types.hpp"

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
DEFINE_TYPED_ARG(string_arg, const char *);
// error handling
DEFINE_TYPED_ARG(error, const char *);

using instruction_argument =
    std::variant<mips_register,
                 mips_fpu_register,
                 vfpu_register,
                 vfpu_matrix,
                 vfpu_condition,
                 vfpu_constant,
                 vfpu_prefix_array,
                 vfpu_destination_prefix_array,
                 vfpu_rotation_array,
                 const psp_function*,
                 shift,
                 coprocessor_register,
                 base_register,
                 jump_address,
                 branch_address,
                 memory_offset,
                 immediate<u32>,
                 immediate<s32>,
                 immediate<u16>,
                 immediate<s16>,
                 immediate<u8>,
                 immediate<float>,
                 condition_code,
                 bitfield_pos,
                 bitfield_size,
                 extra,
                 string_arg,
                 error>;

struct instruction
{
    u32 opcode;
    u32 address;
    allegrex_mnemonic mnemonic;

    std::vector<instruction_argument> arguments;
};
