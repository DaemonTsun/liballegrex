
#pragma once

#include "shl/file_stream.hpp"
#include "shl/memory_stream.hpp"
#include "shl/number_types.hpp"
#include "shl/hash_table.hpp"
#include "shl/array.hpp"
#include "shl/set.hpp"

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

template<>
constexpr int compare_ascending_p(const jump_destination *l, const jump_destination *r)
{
    if (l->address < r->address)
        return -1;

    if (l->address == r->address)
    {
        if (l->type == r->type)
            return 0;

        if (l->type == jump_type::Jump)
            return -1;
    }

    return 1;
}

template<>
constexpr int compare_ascending_p(const u32 *l, const jump_destination *r)
{
    return compare_ascending_p(l, &r->address);
}

template<>
constexpr int compare_ascending_p(const jump_destination *l, const u32 *r)
{
    return compare_ascending_p(&l->address, r);
}

/* Parses a single instruction.
If the instruction is a jump or a branch, optionally adds the jump to out_jumps if out_jumps
is not nullptr.
*/
void parse_instruction(u32 opcode, instruction *out, set<jump_destination> *out_jumps, const parse_instructions_config *conf);

/* Parses as many instructions as there are in input.
size in bytes, not number of instructions.
Appends all instructions to the end of out_instructions.
*/
void parse_instructions(const char *input, u64 size, array<instruction> *out_instructions, set<jump_destination> *out_jumps, const parse_instructions_config *conf);
