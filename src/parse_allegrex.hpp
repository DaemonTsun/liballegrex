
#pragma once

#include <vector>

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

struct instruction_argument
{
    // TODO: argument type (immediate, reg, etc)
    u32 value;
    const char *name;
};

struct instruction
{
    // TODO: instruction type
    u32 opcode;
    u32 address;
    const char *name;

    std::vector<instruction_argument> arguments;
};

void parse_allegrex(memory_stream *in, const parse_config *conf, std::vector<instruction> &out);

