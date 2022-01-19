
#pragma once

#include "string.hpp"
#include "parse_instructions.hpp"

typedef void(*argument_parse_function_t)(u32 opcode, instruction*);

template<typename T>
constexpr T bitmask(T from, T to)
{
    return (((1 << (1 + to)) - 1) ^ ((1 << (from)) - 1));
}

#define bitrange(val, from, to) ((val & bitmask(from, to)) >> from)
#define RS(opcode) bitrange(opcode, 21u, 25u)
#define RT(opcode) bitrange(opcode, 16u, 20u)
#define RD(opcode) bitrange(opcode, 11u, 15u)
#define SA(opcode) bitrange(opcode, 6u, 10u)


void arg_parse_R3(u32 opcode, instruction *inst);
// clz, clo
void arg_parse_R2(u32 opcode, instruction *inst);
void arg_parse_RsRt(u32 opcode, instruction *inst);

// tge, tgeu etc
void arg_parse_RsRtCode(u32 opcode, instruction *inst);
void arg_parse_RtRdShift(u32 opcode, instruction *inst);
void arg_parse_VarShift(u32 opcode, instruction *inst);
