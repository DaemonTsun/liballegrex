
#pragma once

#include <type_traits>

#define DEFINE_ENUM_VALUE(T) \
    constexpr inline std::underlying_type_t<T> value(T a) { return static_cast<std::underlying_type_t<T>>(a); }
