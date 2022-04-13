
#pragma once

#include "instruction.hpp"
#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "number_types.hpp"

struct parse_config
{
    u32 vaddr;
    file_stream *log;
    bool verbose;
    bool emit_pseudo;
};

enum class jump_type : u32
{
    Jump,  // e.g. j
    Branch // e.g. beq
};

struct jump_destination
{
    u32 address;
    jump_type type;
};

struct parse_data
{
    std::vector<instruction> instructions;
    std::vector<jump_destination> jump_destinations;
};

void parse_instruction(u32 opcode, instruction *out, const parse_config *conf, parse_data *pdata);
void parse_allegrex(memory_stream *in, const parse_config *conf, parse_data *out);

