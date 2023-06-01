
#pragma once

#include "shl/file_stream.hpp"
#include "shl/memory_stream.hpp"
#include "shl/number_types.hpp"
#include "shl/hash_table.hpp"

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

struct parse_data
{
    u32 vaddr; // start address
    array<instruction> instructions;
    array<jump_destination> *jump_destinations;
};

void init(parse_data *data);
void free(parse_data *data);

void parse_instruction(u32 opcode, instruction *out, const parse_config *conf, parse_data *pdata);
void parse_allegrex(memory_stream *in, const parse_config *conf, parse_data *out);
void cleanup_jumps(array<jump_destination> *jumps);
