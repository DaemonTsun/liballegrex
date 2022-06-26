
#include <assert.h>
#include "psp-elfdump/dump_format.hpp"

static_assert(hex_digits(0x00000000) == 0);
static_assert(hex_digits(0x00000001) == 1);
static_assert(hex_digits(0x00000008) == 1);
static_assert(hex_digits(0x0000000f) == 1);
static_assert(hex_digits(0x00000010) == 2);
static_assert(hex_digits(0x000000f0) == 2);
static_assert(hex_digits(0x000000ff) == 2);
static_assert(hex_digits(0x00000100) == 3);
static_assert(hex_digits(0x00100000) == 6);
static_assert(hex_digits(0x10000000) == 8);

