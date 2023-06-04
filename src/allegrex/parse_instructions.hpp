
#pragma once

#include "shl/file_stream.hpp"
#include "shl/memory_stream.hpp"
#include "shl/number_types.hpp"
#include "shl/hash_table.hpp"

#include "allegrex/instruction.hpp"

struct parse_instructions_config
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

struct instruction_parse_data
{
    u32 vaddr; // start address, may not be set when parsing ranges
    u32 section_index; // may not be set when parsing ranges
    array<instruction> instructions;
    array<jump_destination> *jump_destinations;
};

void init(instruction_parse_data *data);
void free(instruction_parse_data *data);

void parse_instruction(u32 opcode, instruction *out, const parse_instructions_config *conf, instruction_parse_data *pdata);
// data in BYTES
void parse_instructions(const char *instruction_data, u64 size, const parse_instructions_config *conf, instruction_parse_data *pdata);
void cleanup_jumps(array<jump_destination> *jumps);
