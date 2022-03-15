
#pragma once

#include "string.hpp"
#include "parse_instructions.hpp"

typedef void(*argument_parse_function_t)(u32 opcode, instruction*);

template<typename T>
constexpr T bitmask(T from, T to)
{
    return (((1 << (1 + to)) - 1) ^ ((1 << (from)) - 1));
}

template<typename T, T From, T To>
constexpr T bitrange_(T val)
{
    return static_cast<T>((val & bitmask(From, To)) >> From);
}

#define bitrange(val, from, to) bitrange_<decltype(val), from, to>(val)
#define RS(opcode) bitrange(opcode, 21u, 25u)
#define RT(opcode) bitrange(opcode, 16u, 20u)
#define RD(opcode) bitrange(opcode, 11u, 15u)
#define SA(opcode) bitrange(opcode, 6u, 10u)

static_assert(bitrange(0x00ff, 0, 0) == 0x1);
static_assert(bitrange(0x00ff, 0, 1) == 0x3);
static_assert(bitrange(0x00ff, 0, 3) == 0xf);
static_assert(bitrange(0x00ff, 0, 7) == 0xff);
static_assert(bitrange(0x01ff, 0, 7) == 0xff);
static_assert(bitrange(0x00ff, 0, 8) == 0xff);
static_assert(bitrange(0x01ff, 1, 8) == 0xff);
static_assert(bitrange(0x0ff0, 4, 11) == 0xff);
static_assert(bitrange(0xff00, 8, 15) == 0xff);

void arg_parse_R3(u32 opcode, instruction *inst);
// clz, clo
void arg_parse_R2(u32 opcode, instruction *inst);
void arg_parse_RsRt(u32 opcode, instruction *inst);

// tge, tgeu etc
void arg_parse_RsRtCode(u32 opcode, instruction *inst);
void arg_parse_RdRtShift(u32 opcode, instruction *inst);
void arg_parse_VarShift(u32 opcode, instruction *inst);
// jr
void arg_parse_RegJumpRs(u32 opcode, instruction *inst);
// jalr
void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst);
void arg_parse_Syscall(u32 opcode, instruction *inst);
void arg_parse_Sync(u32 opcode, instruction *inst);

void arg_parse_Rs(u32 opcode, instruction *inst);
void arg_parse_Rd(u32 opcode, instruction *inst);
void arg_parse_RdRt(u32 opcode, instruction *inst);

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst);

void arg_parse_RsImmediateU(u32 opcode, instruction *inst);
void arg_parse_RsImmediateS(u32 opcode, instruction *inst);
void arg_parse_RtImmediateU(u32 opcode, instruction *inst);
void arg_parse_RsRelAddress(u32 opcode, instruction *inst);
void arg_parse_JumpAddress(u32 opcode, instruction *inst);

void arg_parse_FPURelAddress(u32 opcode, instruction *inst);

void arg_parse_RsRtRelAddress(u32 opcode, instruction *inst);
// B pseudoinstruction
void arg_parse_Beq(u32 opcode, instruction *inst);
// BL pseudoinstruction
void arg_parse_Beql(u32 opcode, instruction *inst);

void arg_parse_RsRtImmediateU(u32 opcode, instruction *inst);
void arg_parse_RsRtImmediateS(u32 opcode, instruction *inst);
// LI pseudoinstruction
void arg_parse_Addi(u32 opcode, instruction *inst);
void arg_parse_Addiu(u32 opcode, instruction *inst);
void arg_parse_Ori(u32 opcode, instruction *inst); // technically same as Addiu

// lb, lh, lw, etc...
void arg_parse_RsRtMemOffset(u32 opcode, instruction *inst);

void arg_parse_Cache(u32 opcode, instruction *inst);

// special3
void arg_parse_Ext(u32 opcode, instruction *inst);
void arg_parse_Ins(u32 opcode, instruction *inst);
