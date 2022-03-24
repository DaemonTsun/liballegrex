#pragma once

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

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
