
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

struct parse_data
{
    std::vector<instruction> instructions;
    std::vector<u32> jump_destinations;
};

void parse_allegrex(memory_stream *in, const parse_config *conf, parse_data *out);

