
#pragma once

#include <vector>
#include <variant>

#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "number_types.hpp"

struct parse_config
{
    u32 vaddr;
    file_stream *log;
    bool verbose;
    // TODO: bool emit_pseudo;
};

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

const char *register_name(mips_register reg);

#define DEFINE_TYPED_ARG(name, type) struct name {type data;}

DEFINE_TYPED_ARG(shift, u8);
struct coprocessor_register
{
    u8 rd;
    u8 sel;
};

// TODO: syscall

// some instructions can have data (e.g. tge) that's not really
// an argument, but we store it anyway
DEFINE_TYPED_ARG(extra, u32);

using instruction_argument = std::variant<mips_register, const char*, shift, coprocessor_register, extra>;

enum class instruction_type : u32
{
    None = 0
};

struct instruction
{
    u32 opcode;
    u32 address;
    instruction_type type;
    const char *name;

    std::vector<instruction_argument> arguments;
};

void parse_allegrex(memory_stream *in, const parse_config *conf, std::vector<instruction> &out);

