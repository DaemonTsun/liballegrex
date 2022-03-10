
#pragma once

#include "string.hpp"
#include "parse_instructions.hpp"

typedef void(*argument_parse_function_t)(u32 opcode, instruction*);

template<typename T>
constexpr T bitmask(T from, T to)
{
    return (((1 << (1 + to)) - 1) ^ ((1 << (from)) - 1));
}

template<typename T, size_t Bytes, bool = std::is_signed_v<T>>
struct min_number_type{ using type = s64; };

template<typename T, size_t Bytes>
struct min_number_type<T, Bytes, false> { using type = u64; };

template<typename T>
struct min_number_type<T, 4, true> { using type = s32; };

template<typename T>
struct min_number_type<T, 3, true> { using type = s32; };

template<typename T>
struct min_number_type<T, 2, true> { using type = s16; };

template<typename T>
struct min_number_type<T, 1, true> { using type = s8; };

template<typename T>
struct min_number_type<T, 0, true> { using type = s8; };

template<typename T>
struct min_number_type<T, 4, false> { using type = u32; };

template<typename T>
struct min_number_type<T, 3, false> { using type = u32; };

template<typename T>
struct min_number_type<T, 2, false> { using type = u16; };

template<typename T>
struct min_number_type<T, 1, false> { using type = u8; };

template<typename T>
struct min_number_type<T, 0, false> { using type = u8; };

template<typename T, size_t Bytes>
using min_number_type_t = typename min_number_type<T, Bytes>::type;

template<typename T, T From, T To, typename R = min_number_type_t<T, (To-From) / 8>>
constexpr R bitrange_(T val)
{
    return static_cast<R>((val & bitmask(From, To)) >> From);
}

#define bitrange(val, from, to) bitrange_<decltype(val), from, to>(val)
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

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst);
void arg_parse_Cop0RdRt(u32 opcode, instruction *inst);

void arg_parse_RsImmediate(u32 opcode, instruction *inst);
void arg_parse_RsRelAddress(u32 opcode, instruction *inst);

void arg_parse_FPURelAddress(u32 opcode, instruction *inst);
