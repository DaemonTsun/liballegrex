
#pragma once

#include <type_traits>

#define DEFINE_ENUM_VALUE(T) \
    constexpr inline std::underlying_type_t<T> value(T a) { return static_cast<std::underlying_type_t<T>>(a); }

#define ENUM_CLASS_FLAG_OPS(T) \
    DEFINE_ENUM_VALUE(T) \
    constexpr inline std::underlying_type_t<T> operator~ (T a) { return (~static_cast<std::underlying_type_t<T>>(a)); }\
    constexpr inline T operator| (T a, T b)  { return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) | static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline std::underlying_type_t<T> operator| (T a, std::underlying_type_t<T> b)  { return static_cast<std::underlying_type_t<T>>(a) | b; }\
    constexpr inline std::underlying_type_t<T> operator| (std::underlying_type_t<T> a, T b)  { return a | static_cast<std::underlying_type_t<T>>(b); }\
    constexpr inline T operator& (T a, T b)  { return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) & static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline std::underlying_type_t<T> operator& (T a, std::underlying_type_t<T> b)  { return static_cast<std::underlying_type_t<T>>(a) & b; }\
    constexpr inline std::underlying_type_t<T> operator& (std::underlying_type_t<T> a, T b)  { return a & static_cast<std::underlying_type_t<T>>(b); }\
    constexpr inline T operator^ (T a, T b)  { return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) ^ static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline std::underlying_type_t<T> operator^ (T a, std::underlying_type_t<T> b)  { return static_cast<std::underlying_type_t<T>>(a) ^ b; }\
    constexpr inline std::underlying_type_t<T> operator^ (std::underlying_type_t<T> a, T b)  { return a ^ static_cast<std::underlying_type_t<T>>(b); }\
    constexpr inline T& operator|=(T& a, T b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) | static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline T& operator|=(T& a, std::underlying_type_t<T> b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) | b); }\
    constexpr inline T& operator&=(T& a, T b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) & static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline T& operator&=(T& a, std::underlying_type_t<T> b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) & b); }\
    constexpr inline T& operator^=(T& a, T b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) ^ static_cast<std::underlying_type_t<T>>(b)); }\
    constexpr inline T& operator^=(T& a, std::underlying_type_t<T> b) { return a = static_cast<T>(static_cast<std::underlying_type_t<T>>(a) ^ b); }\
    constexpr inline bool is_set(T a, T b) { return (a & b) == b; }\
    constexpr inline bool is_set(T a, std::underlying_type_t<T> b) { return (a & b) == b; }\
    constexpr inline bool is_set(std::underlying_type_t<T> a, T b) { return static_cast<T>(a & b) == b; }\
    constexpr inline T& set(T& a, T b) {return a |= b;} \
    constexpr inline T& set(T& a, std::underlying_type_t<T> b) {return a |= b;} \
    constexpr inline T& unset(T& a, T b) {return a &= ~b;} \
    constexpr inline T& unset(T& a, std::underlying_type_t<T> b) {return a &= ~b; }

