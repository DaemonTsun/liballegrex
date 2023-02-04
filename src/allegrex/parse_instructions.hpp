
#pragma once

#include "shl/file_stream.hpp"
#include "shl/memory_stream.hpp"
#include "shl/number_types.hpp"

#include "allegrex/instruction.hpp"

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

typedef std::vector<jump_destination> jump_destination_array;

struct parse_data
{
    u32 vaddr; // start address
    std::vector<instruction> instructions;
    jump_destination_array *jump_destinations;
};

void parse_instruction(u32 opcode, instruction *out, const parse_config *conf, parse_data *pdata);
void parse_allegrex(memory_stream *in, const parse_config *conf, parse_data *out);
void cleanup_jumps(jump_destination_array *jumps);
