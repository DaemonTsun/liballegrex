
#include <assert.h>

#include "file_stream.hpp"
#include "instruction.hpp"
#include "dump_format.hpp"

template<typename T>
constexpr inline T hex_digits(T x)
{
    T i = 0;

    while (x > 0)
    {
        x = x >> 4;
        ++i;
    }

    return i;
}

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

void fmt_comment_pos_addr_instr(file_stream *out, u32 pos, const instruction *inst, const char *format_string)
{
    out->format(format_string, pos, inst->address, inst->opcode);
}

void no_fmt_comment_pos_addr_instr(file_stream *out, u32 pos, const instruction *inst, const char *format_string)
{
}

void dump_format(dump_config *conf)
{
    assert(conf != nullptr);
    assert(conf->pdata != nullptr);
    assert(conf->out != nullptr);

    auto *out = conf->out;
    auto *sec = conf->section;
    u32 max_instruction_offset = conf->first_instruction_offset + conf->pdata->instructions.size() * sizeof(u32);

    // format functions
    auto f_comment_pos_addr_instr = no_fmt_comment_pos_addr_instr;

    // prepare
    char comment_format_string[24] = {0};

    if (is_set(conf->format, format_options::comment_pos_addr_instr))
    {
        // prepare format string for comment
        u32 pos_digits = hex_digits(max_instruction_offset);

        sprintf(comment_format_string, "/* %%0%ux %%08x %%08x */  ", pos_digits);
        f_comment_pos_addr_instr = fmt_comment_pos_addr_instr;
    }

    // do the writing
    u32 pos = conf->first_instruction_offset;
    for (const instruction &inst : conf->pdata->instructions)
    {
        f_comment_pos_addr_instr(out, pos, &inst, comment_format_string);
        // format_instruction(conf->out, &inst);
        conf->out->write("\n");

        pos += sizeof(u32);
    }
}
