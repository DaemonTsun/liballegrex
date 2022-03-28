
#pragma once

#include <vector>
#include <variant>

#include "psp_syscalls.hpp"
#include "mips_registers.hpp"
#include "allegrex_mnemonics.hpp"
#include "allegrex_vfpu.hpp"
#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "number_types.hpp"

struct parse_config
{
    u32 vaddr;
    file_stream *log;
    bool verbose;
    bool emit_pseudo;
};

#define DEFINE_TYPED_ARG(name, type) struct name {type data;}

DEFINE_TYPED_ARG(shift, u8);
struct coprocessor_register
{
    u8 rd;
    u8 sel;
};

DEFINE_TYPED_ARG(base_register, mips_register);
DEFINE_TYPED_ARG(address, u32);
DEFINE_TYPED_ARG(memory_offset, s16);


// immediates
template<typename T = u32>
DEFINE_TYPED_ARG(immediate, T);
DEFINE_TYPED_ARG(condition_code, u8);

// ext, ins
DEFINE_TYPED_ARG(bitfield_size, u32);
DEFINE_TYPED_ARG(bitfield_pos, u32);

DEFINE_TYPED_ARG(vfpu_constant, u32);

// some instructions can have data (e.g. tge) that's not really
// an argument, but we store it anyway
DEFINE_TYPED_ARG(extra, u32);
// error handling
DEFINE_TYPED_ARG(error, const char *);

using instruction_argument =
    std::variant<mips_register,
                 mips_fpu_register,
                 vfpu_register,
                 vfpu_matrix,
                 vfpu_condition,
                 vfpu_constant,
                 const syscall*,
                 const char*,
                 shift,
                 coprocessor_register,
                 base_register,
                 address,
                 memory_offset,
                 immediate<u32>,
                 immediate<u16>,
                 immediate<s16>,
                 immediate<u8>,
                 immediate<float>,
                 condition_code,
                 bitfield_pos,
                 bitfield_size,
                 extra,
                 error>;

struct instruction
{
    u32 opcode;
    u32 address;
    allegrex_mnemonic mnemonic;

    std::vector<instruction_argument> arguments;
};

void parse_allegrex(memory_stream *in, const parse_config *conf, std::vector<instruction> &out);

