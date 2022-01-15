
#include <variant>
#include <assert.h>
#include "parse_allegrex.hpp"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

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

const category SrlRotr{
    .min =  0x00000002,
    .max =  0x00200002,
    .mask = 0xffe0003f,
    .instructions = {
        {"srl",  0x00000002},
        {"rotr", 0x00200002}
    },
    .sub_categories = {}
};

const category SrlvRotrv{
    .min =  0x00000006,
    .max =  0x00000046,
    .mask = 0xfc00007f,
    .instructions = {
        {"srlv",  0x00000006},
        {"rotrv", 0x00000046}
    },
    .sub_categories = {}
};

const category Special{
    .min =  0x00000000,
    .max =  0x0000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"sll",     0x00000000},
        {"sra",     0x00000003},
        {"sllv",    0x00000004},
        {"srav",    0x00000007},
        {"jr",      0x00000008},
        {"jalr",    0x00000009},
        {"movz",    0x0000000a},
        {"movn",    0x0000000b},
        {"syscall", 0x0000000c},
        {"break",   0x0000000d},
        {"sync",    0x0000000f},
        {"mfhi",    0x00000010},
        {"mthi",    0x00000011},
        {"mflo",    0x00000012},
        {"mtlo",    0x00000013},
        {"clz",     0x00000016},
        {"clo",     0x00000017},
        {"mult",    0x00000018},
        {"multu",   0x00000019},
        {"div",     0x0000001a},
        {"divu",    0x0000001b},
        {"madd",    0x0000001c},
        {"maddu",   0x0000001d},
        {"add",     0x00000020},
        {"addu",    0x00000021},
        {"sub",     0x00000022},
        {"subu",    0x00000023},
        {"and",     0x00000024},
        {"or",      0x00000025},
        {"xor",     0x00000026},
        {"nor",     0x00000027},
        {"slt",     0x0000002a},
        {"sltu",    0x0000002b},
        {"max",     0x0000002c},
        {"min",     0x0000002d},
        {"msub",    0x0000002e},
        {"msubu",   0x0000002f},
        {"tge",     0x00000030},
        {"tgeu",    0x00000031},
        {"tlt",     0x00000032},
        {"tltu",    0x00000033},
        {"teq",     0x00000034},
        {"tne",     0x00000036},
    },
    .sub_categories = {
        &SrlRotr,
        &SrlvRotrv
    }
};

const category Cop0CO{
    .min =  0x42000000,
    .max =  0x4200003f,
    .mask = 0xfe00003f,
    .instructions = {
        {"tlbr",  0x42000001},
        {"tlbwi", 0x42000002},
        {"tlbwr", 0x42000006},
        {"tlbp",  0x42000008},
        {"eret",  0x42000018},
        {"iack",  0x42000019},
        {"deret", 0x4200001f},
        {"wait",  0x42000020},
    },
    .sub_categories = {}
};


const category Cop0{
    .min =  0x40000000,
    .max =  0x43e00000,
    .mask = 0xffe00000,
    .instructions = {
        {"mfc0",   0x40000000},
        {"mtc0",   0x40800000},
        {"rdpgpr", 0x41600000},
        {"mfmc0",  0x41800000},
        {"wrpgpr", 0x41c00000},
    },
    .sub_categories = {
        &Cop0CO
    }
};

const category Cop1BC{
    .min =  0x45000000,
    .max =  0x451f0000,
    .mask = 0xffff0000,
    .instructions = {
        {"bc1f",  0x45000000},
        {"bc1t",  0x45010000},
        {"bc1fl", 0x45020000},
        {"bc1tl", 0x45030000},
    },
    .sub_categories = {}
};

const category Cop1S{
    .min =  0x46000000,
    .max =  0x4600003f,
    .mask = 0xffe0003f,
    .instructions = {
        {"add.s",     0x46000000},
        {"sub.s",     0x46000001},
        {"mul.s",     0x46000002},
        {"div.s",     0x46000003},
        {"sqrt.s",    0x46000004},
        {"abs.s",     0x46000005},
        {"mov.s",     0x46000006},
        {"neg.s",     0x46000007},
        {"round.w.s", 0x4600000c},
        {"trunc.w.s", 0x4600000d},
        {"ceil.w.s",  0x4600000e},
        {"floor.w.s", 0x4600000f},
        {"cvt.s.w",   0x46000024},
        {"dis.int",   0x46000026},
        {"c.f.s",     0x46000030},
        {"c.un.s",    0x46000031},
        {"c.eq.s",    0x46000032},
        {"c.ueq.s",   0x46000033},
        {"c.olt.s",   0x46000034},
        {"c.ole.s",   0x46000036},
        {"c.ule.s",   0x46000037},
        {"c.sf.s",    0x46000038},
        {"c.ngle.s",  0x46000039},
        {"c.seq.s",   0x4600003a},
        {"c.lt.s",    0x4600003c},
        {"c.nge.s",   0x4600003d},
        {"c.le.s",    0x4600003e},
        {"c.ngt.s",   0x4600003f}

    },
    .sub_categories = {}
};

const category Cop1W{
    .min =  0x46800000,
    .max =  0x4680003f,
    .mask = 0xffe0003f,
    .instructions = {
        {"cvt.s.w", 0x46800020}
    },
    .sub_categories = {}
};

const category Cop1{
    .min =  0x44000000,
    .max =  0x47e00000,
    .mask = 0xffe00000,
    .instructions = {
        {"mfc1", 0x44000000},
        {"cfc1", 0x44400000},
        {"mtc1", 0x44800000},
        {"ctc1", 0x44c00000},
    },
    .sub_categories = {
        &Cop1BC,
        &Cop1S,
        &Cop1W
    }
};

const category Cop2BC2{
    .min =  0x49000000,
    .max =  0x49030000,
    .mask = 0xffe30000,
    .instructions = {
        {"bvf",  0x49000000},
        {"bvt",  0x49010000},
        {"bvfl", 0x49020000},
        {"bvtl", 0x49030000},
    },
    .sub_categories = {}
};

const category Cop2{
    .min =  0x48000000,
    .max =  0x4be00000,
    .mask = 0xffe00000,
    .instructions = {
        {"mfc2", 0x48000000},
        {"cfc2", 0x48400000},
        {"mfv",  0x48600000},
        {"mtc2", 0x48800000},
        {"ctc2", 0x48c00000},
        {"mtv",  0x48e00000},

    },
    .sub_categories = {
        &Cop2BC2
    }
};

const category VFPU0{
    .min =  0x60000000,
    .max =  0x63800000,
    .mask = 0xff800000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vadd", 0x60000000},
        {"vsub", 0x60800000},
        {"vsbn", 0x61000000},
        {"vdiv", 0x63800000},
    },
    .sub_categories = {
    }
};

const category VFPU1{
    .min =  0x64000000,
    .max =  0x67800000,
    .mask = 0xff800000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vmul", 0x64000000},
        {"vdot", 0x64800000},
        {"vscl", 0x65000000},
        {"vhdp", 0x66000000},
        {"vcrs", 0x66800000},
        {"vdet", 0x67000000},
    },
    .sub_categories = {
    }
};

const category VFPU3{
    .min =  0x6c000000,
    .max =  0x6f800000,
    .mask = 0xff800000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vcmp",  0x6c000000},
        {"vmin",  0x6d000000},
        {"vmax",  0x6d800000},
        {"vscmp", 0x6e800000},
        {"vsge",  0x6f000000},
        {"vslt",  0x6f800000},
    },
    .sub_categories = {
    }
};

const category Special2{
    .min =  0x70000000,
    .max =  0x7000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"halt", 0x70000000},
        {"mfic", 0x70000024},
        {"mtic", 0x70000026},
    },
    .sub_categories = {
    }
};

const category Allegrex0{
    .min =  0x7c000020,
    .max =  0x7c0007e0,
    .mask = 0xfc0007ff,
    .instructions = {
        {"wsbh",   0x7c0000a0},
        {"wsbw",   0x7c0000e0},
        {"seb",    0x7c000420},
        {"bitrev", 0x7c000520},
        {"seh",    0x7c000620}
    },
    .sub_categories = {}
};

const category Special3{
    .min =  0x7c000000,
    .max =  0x7c00003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"ext",   0x7c000000},
        {"ins",   0x7c000004},
        {"rdhwr", 0x7c00003b}
    },
    .sub_categories = {
        &Allegrex0
    }
};

const category VFPU4{
    .min =  0xd0000000,
    .max =  0xd01f0000,
    .mask = 0xffff0000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        // TODO: add instructions
    },
    .sub_categories = {
    }
};

const category VFPU7{
    .min =  0xd0200000,
    .max =  0xd03f0000,
    .mask = 0xffff0000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        // TODO: add instructions
    },
    .sub_categories = {
    }
};

const category VFPU9{
    .min =  0xd0400000,
    .max =  0xd05f0000,
    .mask = 0xffff0000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        // TODO: add instructions
    },
    .sub_categories = {
    }
};

const category VFPU4Jump{
    .min =  0xd0000000,
    .max =  0xd3e00000,
    .mask = 0xffe00000,
    .instructions = {
        // TODO: add instructions
    },
    .sub_categories = {
        &VFPU4,
        &VFPU7,
        &VFPU9,
        // TODO: &vwbn
    }
};

const category Immediate{
    .min =  0x00000000,
    .max =  0xfc000000,
    .mask = 0xfc000000,
    .instructions = {
        {"j",     0x08000000},
        {"jal",   0x0c000000},
        {"beq",   0x10000000},
        {"bne",   0x14000000},
        {"blez",  0x18000000},
        {"bgtz",  0x1c000000},
        {"addi",  0x20000000},
        {"addiu", 0x24000000},
        {"slti",  0x28000000},
        {"sltiu", 0x2c000000},
        {"andi",  0x30000000},
        {"ori",   0x34000000},
        {"xori",  0x38000000},
        {"lui",   0x3c000000},
        {"beql",  0x50000000},
        {"bnel",  0x54000000},
        {"blezl", 0x58000000},
        {"bgtzl", 0x5c000000},
        {"bgtzl", 0x5c000000},
        {"lb",    0x80000000},
        {"lh",    0x84000000},
        {"lwl",   0x88000000},
        {"lw",    0x8c000000},
        {"lbu",   0x90000000},
        {"lhu",   0x94000000},
        {"lwr",   0x98000000},
        {"sb",    0xa0000000},
        {"sh",    0xa4000000},
        {"swl",   0xa8000000},
        {"sw",    0xac000000},
        {"swr",   0xb8000000},
        {"cache", 0xbc000000},
        {"ll",    0xc0000000},
        {"lwc1",  0xc4000000},
        {"lv.s",  0xc8000000},
    },
    .sub_categories = {
        &Special,
        &Cop0,
        &Cop1,
        &Cop2,
        &VFPU0,
        &VFPU1,
        &VFPU3,
        &Special2,
        &Special3,
        &VFPU4Jump,
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
