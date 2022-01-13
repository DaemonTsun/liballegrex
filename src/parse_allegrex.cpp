
#include <variant>
#include <assert.h>
#include "parse_allegrex.hpp"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct instruction_info
{
    const char *name;
    u32 opcode;
    // TODO: type
};

struct category
{
    u32 min;
    u32 max;
    u32 mask;

    std::vector<instruction_info> instructions;
    std::vector<const category*> sub_categories;
};

const instruction_info nop{"nop", 0x00000000};

const category Special{
    .min =  0x00000000,
    .max =  0x0000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"sll", 0x00000000}
    },
    .sub_categories = {}
};

const category Immediate{
    .min =  0x00000000,
    .max =  0xfc000000,
    .mask = 0xfc000000,
    .instructions = {},
    .sub_categories = {
        &Special
    }
};

void populate_instruction(instruction *instr, const instruction_info *info)
{
    instr->name = info->name;
    // TODO: instr->type = info->type;
}

bool try_parse_category_instruction(u32 opcode, const category *cat, const parse_config *conf, instruction *out)
{
    if (cat == nullptr)
        return false;

    for (auto &sub : cat->sub_categories)
        if (try_parse_category_instruction(opcode, sub, conf, out))
            return true;

    u32 mop = opcode & cat->mask;

    if (mop < cat->min || mop > cat->max)
        return false;

    for (auto &instr : cat->instructions)
        if (mop == instr.opcode)
        {
            populate_instruction(out, &instr);
            return true;
        }

    return false;
}

bool try_parse_special_instruction(u32 opcode, const parse_config *conf, instruction *out)
{
    if (opcode == nop.opcode)
    {
        populate_instruction(out, &nop);
        return true;
    }

    // TODO: others (jalr)

    return false;
}

void parse_instruction(u32 opcode, const parse_config *conf, instruction *out)
{
    bool found = try_parse_special_instruction(opcode, conf, out);

    if (!found)
        found = try_parse_category_instruction(opcode, &Immediate, conf, out);

    if (!found)
        out->name = "unknown";
}

void parse_allegrex(memory_stream *in, const parse_config *conf, std::vector<instruction> &out)
{
    size_t sz = in->size();

    assert(sz % sizeof(u32) == 0);
    assert(sz <= UINT32_MAX);

    u32 count = (u32)(sz / sizeof(u32));
    out.resize(count);

    for (u32 i = 0x00000000; i < sz; i += sizeof(u32))
    {
        instruction inst;
        in->read(&inst.opcode); // probably don't need read_at

        inst.address = conf->vaddr + i;

        parse_instruction(inst.opcode, conf, &inst);

        log(conf, "%08x %08x   %s\n", inst.address, inst.opcode, inst.name);
    }
}
