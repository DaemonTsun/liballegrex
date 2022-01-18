
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

using instruction_argument = std::variant<u32, const char*>;

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

