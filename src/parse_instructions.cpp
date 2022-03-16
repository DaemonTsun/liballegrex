
#include <stdexcept>
#include <assert.h>

#include "string.hpp"
#include "parse_instruction_arguments.hpp"
#include "parse_instructions.hpp"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

const char *register_names[] = {
    "zero",     // 0
    "at",       // 1
    "v0", "v1", // 2-3
    "a0", "a1", "a2", "a3", // 4-7
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", // 8-15
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", // 16-23
    "t8", "t9", // 24-25
    "k0", "k1", // 26-27
    "gp", // 28
    "sp", // 29
    "fp", // 30
    "ra"  // 31
};

const char *fpu_register_names[] = {
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
    "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
    "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
    "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31",
};

const char *register_name(mips_register reg)
{
    return register_names[static_cast<u32>(reg)];
}

const char *register_name(mips_fpu_register reg)
{
    return fpu_register_names[static_cast<u32>(reg)];
}

struct instruction_info
{
    const char *name;
    u32 opcode;
    instruction_type type;
    argument_parse_function_t argument_parse_function;
};

struct category
{
    u32 min;
    u32 max;
    u32 mask;

    std::vector<instruction_info> instructions;
    std::vector<const category*> sub_categories;
};

// categories
const category Fixed{
    .min  = 0x00000000,
    .max  = 0xffffffff,
    .mask = 0xffffffff,
    .instructions = {
        {"nop", 0x00000000, instruction_type::None, nullptr}
    },
    .sub_categories = {}
};

const category SrlRotr{
    .min =  0x00000002,
    .max =  0x00200002,
    .mask = 0xffe0003f,
    .instructions = {
        {"srl",  0x00000002, instruction_type::None, arg_parse_RdRtShift}, // TODO: type
        {"rotr", 0x00200002, instruction_type::None, arg_parse_RdRtShift}  // TODO: type
    },
    .sub_categories = {}
};

const category SrlvRotrv{
    .min =  0x00000006,
    .max =  0x00000046,
    .mask = 0xfc00007f,
    .instructions = {
        {"srlv",  0x00000006, instruction_type::None, arg_parse_VarShift}, // TODO: type
        {"rotrv", 0x00000046, instruction_type::None, arg_parse_VarShift} // TODO: type
    },
    .sub_categories = {}
};

const category Special{
    .min =  0x00000000,
    .max =  0x0000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"sll",     0x00000000, instruction_type::None, arg_parse_RdRtShift}, // TODO: type
        {"sra",     0x00000003, instruction_type::None, arg_parse_RdRtShift}, // TODO: type
        {"sllv",    0x00000004, instruction_type::None, arg_parse_VarShift}, // TODO: type
        {"srav",    0x00000007, instruction_type::None, arg_parse_VarShift}, // TODO: type
        {"jr",      0x00000008, instruction_type::None, arg_parse_RegJumpRs}, // TODO: type
        {"jalr",    0x00000009, instruction_type::None, arg_parse_RegJumpRdRs}, // TODO: type
        {"movz",    0x0000000a, instruction_type::None, arg_parse_R3}, // TODO: type
        {"movn",    0x0000000b, instruction_type::None, arg_parse_R3}, // TODO: type
        {"syscall", 0x0000000c, instruction_type::None, arg_parse_Syscall}, // TODO: type
        {"break",   0x0000000d, instruction_type::None, nullptr}, // TODO: type
        {"sync",    0x0000000f, instruction_type::None, arg_parse_Sync}, // TODO: type
        {"mfhi",    0x00000010, instruction_type::None, arg_parse_Rd}, // TODO: type
        {"mthi",    0x00000011, instruction_type::None, arg_parse_Rs}, // TODO: type
        {"mflo",    0x00000012, instruction_type::None, arg_parse_Rd}, // TODO: type
        {"mtlo",    0x00000013, instruction_type::None, arg_parse_Rs}, // TODO: type
        {"clz",     0x00000016, instruction_type::None, arg_parse_R2}, // TODO: type
        {"clo",     0x00000017, instruction_type::None, arg_parse_R2}, // TODO: type
        {"mult",    0x00000018, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"multu",   0x00000019, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"div",     0x0000001a, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"divu",    0x0000001b, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"madd",    0x0000001c, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"maddu",   0x0000001d, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"add",     0x00000020, instruction_type::None, arg_parse_R3}, // TODO: type
        {"addu",    0x00000021, instruction_type::None, arg_parse_R3}, // TODO: type
        {"sub",     0x00000022, instruction_type::None, arg_parse_R3}, // TODO: type
        {"subu",    0x00000023, instruction_type::None, arg_parse_R3}, // TODO: type
        {"and",     0x00000024, instruction_type::None, arg_parse_R3}, // TODO: type
        {"or",      0x00000025, instruction_type::None, arg_parse_R3}, // TODO: type
        {"xor",     0x00000026, instruction_type::None, arg_parse_R3}, // TODO: type
        {"nor",     0x00000027, instruction_type::None, arg_parse_R3}, // TODO: type
        {"slt",     0x0000002a, instruction_type::None, arg_parse_R3}, // TODO: type
        {"sltu",    0x0000002b, instruction_type::None, arg_parse_R3}, // TODO: type
        {"max",     0x0000002c, instruction_type::None, arg_parse_R3}, // TODO: type
        {"min",     0x0000002d, instruction_type::None, arg_parse_R3}, // TODO: type
        {"msub",    0x0000002e, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"msubu",   0x0000002f, instruction_type::None, arg_parse_RsRt}, // TODO: type
        {"tge",     0x00000030, instruction_type::None, arg_parse_RsRtCode}, // TODO: type
        {"tgeu",    0x00000031, instruction_type::None, arg_parse_RsRtCode}, // TODO: type
        {"tlt",     0x00000032, instruction_type::None, arg_parse_RsRtCode}, // TODO: type 
        {"tltu",    0x00000033, instruction_type::None, arg_parse_RsRtCode}, // TODO: type
        {"teq",     0x00000034, instruction_type::None, arg_parse_RsRtCode}, // TODO: type
        {"tne",     0x00000036, instruction_type::None, arg_parse_RsRtCode}, // TODO: type
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
        {"tlbr",  0x42000001, instruction_type::None, nullptr}, // TODO: type
        {"tlbwi", 0x42000002, instruction_type::None, nullptr}, // TODO: type
        {"tlbwr", 0x42000006, instruction_type::None, nullptr}, // TODO: type
        {"tlbp",  0x42000008, instruction_type::None, nullptr}, // TODO: type
        {"eret",  0x42000018, instruction_type::None, nullptr}, // TODO: type
        {"iack",  0x42000019, instruction_type::None, nullptr}, // TODO: type
        {"deret", 0x4200001f, instruction_type::None, nullptr}, // TODO: type
        {"wait",  0x42000020, instruction_type::None, nullptr}  // TODO: type
    },
    .sub_categories = {}
};

const category Cop0{
    .min =  0x40000000,
    .max =  0x43e00000,
    .mask = 0xffe00000,
    .instructions = {
        {"mfc0",   0x40000000, instruction_type::None, arg_parse_Cop0RtRdSel}, // TODO: type
        {"mtc0",   0x40800000, instruction_type::None, arg_parse_Cop0RtRdSel}, // TODO: type
        {"rdpgpr", 0x41600000, instruction_type::None, arg_parse_RdRt}, // TODO: type
        {"mfmc0",  0x41800000, instruction_type::None, nullptr}, // TODO: type
        {"wrpgpr", 0x41c00000, instruction_type::None, arg_parse_RdRt}, // TODO: type
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
        {"bc1f",  0x45000000, instruction_type::None, arg_parse_FPURelAddress}, // TODO: type
        {"bc1t",  0x45010000, instruction_type::None, arg_parse_FPURelAddress}, // TODO: type
        {"bc1fl", 0x45020000, instruction_type::None, arg_parse_FPURelAddress}, // TODO: type
        {"bc1tl", 0x45030000, instruction_type::None, arg_parse_FPURelAddress}, // TODO: type
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
        {"halt", 0x70000000, instruction_type::None, nullptr}, // TODO: type
        {"mfic", 0x70000024, instruction_type::None, nullptr}, // TODO: type
        {"mtic", 0x70000026, instruction_type::None, nullptr}, // TODO: type
    },
    .sub_categories = {
    }
};

const category Allegrex0{
    .min =  0x7c000020,
    .max =  0x7c0007e0,
    .mask = 0xfc0007ff,
    .instructions = {
        {"wsbh",   0x7c0000a0, instruction_type::None, arg_parse_RdRt}, // TODO: type
        {"wsbw",   0x7c0000e0, instruction_type::None, arg_parse_RdRt}, // TODO: type
        {"seb",    0x7c000420, instruction_type::None, arg_parse_RdRt}, // TODO: type
        {"bitrev", 0x7c000520, instruction_type::None, arg_parse_RdRt}, // TODO: type
        {"seh",    0x7c000620, instruction_type::None, arg_parse_RdRt}  // TODO: type
    },
    .sub_categories = {}
};

const category Special3{
    .min =  0x7c000000,
    .max =  0x7c00003f,
    .mask = 0xfc00003f,
    .instructions = {
        {"ext",   0x7c000000, instruction_type::None, arg_parse_Ext}, // TODO: type
        {"ins",   0x7c000004, instruction_type::None, arg_parse_Ins}, // TODO: type
        {"rdhwr", 0x7c00003b, instruction_type::None, nullptr} // TODO: type
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
        {"vmov",   0xd0000000},
        {"vabs",   0xd0010000},
        {"vneg",   0xd0020000},
        {"vidt",   0xd0030000},
        {"vsat0",  0xd0040000},
        {"vsat1",  0xd0050000},
        {"vzero",  0xd0060000},
        {"vone",   0xd0070000},
        {"vrcp",   0xd0100000},
        {"vrsq",   0xd0110000},
        {"vsin",   0xd0120000},
        {"vcos",   0xd0130000},
        {"vexp2",  0xd0140000},
        {"vlog2",  0xd0150000},
        {"vsqrt",  0xd0160000},
        {"vasin",  0xd0170000},
        {"vnrcp",  0xd0180000},
        {"vnsin",  0xd01a0000},
        {"vrexp2", 0xd01c0000}
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
        {"vrnds",  0xd0200000},
        {"vrndi",  0xd0210000},
        {"vrndf1", 0xd0220000},
        {"vrndf2", 0xd0230000},
        {"vf2h",   0xd0320000},
        {"vh2f",   0xd0330000},
        {"vsbz",   0xd0360000},
        {"vlgb",   0xd0370000},
        {"vuc2i",  0xd0380000},
        {"vc2i",   0xd0390000},
        {"vus2i",  0xd03a0000},
        {"vs2i",   0xd03b0000},
        {"vi2uc",  0xd03c0000},
        {"vi2c",   0xd03d0000},
        {"vi2us",  0xd03e0000},
        {"vi2s",   0xd03f0000}
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
        {"vsrt1",  0xd0400000},
        {"vsrt2",  0xd0410000},
        {"vbfy1",  0xd0420000},
        {"vbfy2",  0xd0430000},
        {"vocp",   0xd0440000},
        {"vsocp",  0xd0450000},
        {"vfad",   0xd0460000},
        {"vavg",   0xd0470000},
        {"vsrt3",  0xd0480000},
        {"vsrt4",  0xd0490000},
        {"vsgn",   0xd04a0000},
        {"vmfvc",  0xd0500000},
        {"vmtvc",  0xd0510000},
        {"vt4444", 0xd0590000},
        {"vt5551", 0xd05a0000},
        {"vt5650", 0xd05b0000},
    },
    .sub_categories = {
    }
};

const category vwbn{
    .min =  0xd3000000,
    .max =  0xd3000000,
    .mask = 0xff000000,
    .instructions = {
        {"vwbn", 0xd3000000}
    },
    .sub_categories = {}
};

const category VFPU4Jump{
    .min =  0xd0000000,
    .max =  0xd3e00000,
    .mask = 0xffe00000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vcst",  0xd0600000},
        {"vf2in", 0xd2000000},
        {"vf2iz", 0xd2200000},
        {"vf2iu", 0xd2400000},
        {"vf2id", 0xd2600000},
        {"vf2f",  0xd2800000},
        {"vcmov", 0xd2a00000}
    },
    .sub_categories = {
        &VFPU4,
        &VFPU7,
        &VFPU9,
        &vwbn
    }
};

const category VFPU5{
    .min =  0xdc000000,
    .max =  0xdf800000,
    .mask = 0xff800000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vpfxs", 0xdc000000},
        {"vpfxs", 0xdc800000},
        {"vpfxt", 0xdd000000},
        {"vpfxt", 0xdd800000},
        {"vpfxd", 0xde000000},
        {"vpfxd", 0xde800000},
        {"viim",  0xdf000000},
        {"vfim",  0xdf800000}
    },
    .sub_categories = {}
};

const category VFPUMatrix{
    .min =  0xf3800000,
    .max =  0xf38f0000,
    .mask = 0xffef0000,
    .instructions = {
        {"vmmov",  0xf3800000},
        {"vmidt",  0xf3830000},
        {"vmzero", 0xf3860000},
        {"vmone",  0xf3870000},
    },
    .sub_categories = {}
};

const category VFPU6{
    .min =  0xf0000000,
    .max =  0xf3e00000,
    .mask = 0xffe00000,
    .instructions = {
        // TODO: correct VFPU instruction name parsing
        {"vmmul", 0xf0000000},
        {"vmmul", 0xf0200000},
        {"vmmul", 0xf0400000},
        {"vmmul", 0xf0600000},
        {"vtfm2", 0xf0800000},
        {"vtfm2", 0xf0a00000},
        {"vtfm2", 0xf0c00000},
        {"vtfm2", 0xf0e00000},
        {"vtfm3", 0xf1000000},
        {"vtfm3", 0xf1200000},
        {"vtfm3", 0xf1400000},
        {"vtfm3", 0xf1600000},
        {"vtfm4", 0xf1800000},
        {"vtfm4", 0xf1a00000},
        {"vtfm4", 0xf1c00000},
        {"vtfm4", 0xf1e00000},
        {"vmscl", 0xf2000000},
        {"vmscl", 0xf2200000},
        {"vmscl", 0xf2400000},
        {"vmscl", 0xf2600000},
        {"vcrsp", 0xf2800000},
        {"vrot",  0xf3a00000},
    },
    .sub_categories = {
        &VFPUMatrix
    }
};

const category Immediate{
    .min =  0x00000000,
    .max =  0xfc000000,
    .mask = 0xfc000000,
    .instructions = {
        {"j",     0x08000000, instruction_type::None, arg_parse_JumpAddress}, // TODO: type
        {"jal",   0x0c000000, instruction_type::None, arg_parse_JumpAddress}, // TODO: type
        {"beq",   0x10000000, instruction_type::None, arg_parse_Beq}, // TODO: type
        {"bne",   0x14000000, instruction_type::None, arg_parse_RsRtRelAddress}, // TODO: type
        {"blez",  0x18000000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgtz",  0x1c000000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"addi",  0x20000000, instruction_type::None, arg_parse_Addi}, // TODO: type
        {"addiu", 0x24000000, instruction_type::None, arg_parse_Addiu}, // TODO: type
        {"slti",  0x28000000, instruction_type::None, arg_parse_RsRtImmediateS}, // TODO: type
        {"sltiu", 0x2c000000, instruction_type::None, arg_parse_RsRtImmediateU}, // TODO: type
        {"andi",  0x30000000, instruction_type::None, arg_parse_RsRtImmediateS}, // TODO: type
        {"ori",   0x34000000, instruction_type::None, arg_parse_Ori}, // TODO: type
        {"xori",  0x38000000, instruction_type::None, arg_parse_RsRtImmediateU}, // TODO: type
        {"lui",   0x3c000000, instruction_type::None, arg_parse_RtImmediateU}, // TODO: type
        {"beql",  0x50000000, instruction_type::None, arg_parse_Beql}, // TODO: type
        {"bnel",  0x54000000, instruction_type::None, arg_parse_RsRtRelAddress}, // TODO: type
        {"blezl", 0x58000000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgtzl", 0x5c000000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"lb",    0x80000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lh",    0x84000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lwl",   0x88000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lw",    0x8c000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lbu",   0x90000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lhu",   0x94000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lwr",   0x98000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"sb",    0xa0000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"sh",    0xa4000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"swl",   0xa8000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"sw",    0xac000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"swr",   0xb8000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"cache", 0xbc000000, instruction_type::None, arg_parse_Cache}, // TODO: type
        {"ll",    0xc0000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"lwc1",  0xc4000000, instruction_type::None, arg_parse_RsFtMemOffset}, // TODO: type
        {"lv.s",  0xc8000000},
        {"lv",    0xd4000000},
        {"lv.q",  0xd8000000},
        {"sc",    0xe0000000, instruction_type::None, arg_parse_RsRtMemOffset}, // TODO: type
        {"swc1",  0xe4000000, instruction_type::None, arg_parse_RsFtMemOffset}, // TODO: type
        // TODO: correct VFPU instruction name parsing
        {"sv.s",  0xe8000000},
        {"svl.q", 0xf4000000},
        {"sv.q", 0xf8000000},
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
        &VFPU5,
        &VFPU6
    }
};

const category RegisterImmediate{
    .min =  0x04000000,
    .max =  0x041f0000,
    .mask = 0xfc1f0000,
    .instructions = {
        {"bltz", 0x04000000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgez", 0x04010000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bltzl", 0x04020000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgezl", 0x04030000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"tgei", 0x04080000, instruction_type::None, arg_parse_RsImmediateS}, // TODO: type
        {"tgeiu", 0x04090000, instruction_type::None, arg_parse_RsImmediateU}, // TODO: type
        {"tlti", 0x040a0000, instruction_type::None, arg_parse_RsImmediateS}, // TODO: type
        {"tltiu", 0x040b0000, instruction_type::None, arg_parse_RsImmediateU}, // TODO: type
        {"teqi", 0x040c0000, instruction_type::None, arg_parse_RsImmediateS}, // TODO: type
        {"tnei", 0x040e0000, instruction_type::None, arg_parse_RsImmediateS}, // TODO: type
        {"bltzal", 0x04100000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgezal", 0x04110000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bltzall", 0x04120000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"bgezall", 0x04130000, instruction_type::None, arg_parse_RsRelAddress}, // TODO: type
        {"synci", 0x041f0000, instruction_type::None, nullptr} // TODO: type
    },
    .sub_categories = {}
};

const category VFPUSpecial{
    .min  = 0xffff0000,
    .max  = 0xffff04ff,
    .mask = 0xffff07ff,
    .instructions = {
        {"vnop",   0xffff0000, instruction_type::None, nullptr}, // TODO: type
        {"vsync",  0xffff0320, instruction_type::None, nullptr}, // TODO: type
        {"vflush", 0xffff040d, instruction_type::None, nullptr} // TODO: type
    },
    .sub_categories = {}
};

const category AllInstructions{
    .min  = 0x00000000,
    .max  = 0xffffffff,
    .mask = 0xffffffff,
    .instructions = {},
    .sub_categories = {
        &Fixed,
        &Immediate,
        &RegisterImmediate,
        &VFPUSpecial
    }
};

void populate_instruction(instruction *instr, const instruction_info *info)
{
    instr->name = info->name;
    instr->type = info->type;
    
    if (info->argument_parse_function != nullptr)
        info->argument_parse_function(instr->opcode, instr);
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

void parse_instruction(u32 opcode, const parse_config *conf, instruction *out)
{
    bool found;

    found = try_parse_category_instruction(opcode, &AllInstructions, conf, out);

    if (!found)
        out->name = "unknown";
}

#define IF_ARG_TYPE_LOG(arg, T, FMT) \
    if (std::holds_alternative<T>(arg)) \
    { \
        log(conf, FMT, std::get<T>(arg).data); \
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

        log(conf, "%06x %08x   %-10s", inst.address, inst.opcode, inst.name);

        for (auto arg : inst.arguments)
        {
            if (std::holds_alternative<const char*>(arg))
            {
                log(conf, " %s", std::get<const char*>(arg));
            }
            else if (std::holds_alternative<mips_register>(arg))
            {
                log(conf, " %s", register_name(std::get<mips_register>(arg)));
            }
            else if (std::holds_alternative<mips_fpu_register>(arg))
            {
                log(conf, " %s", register_name(std::get<mips_fpu_register>(arg)));
            }
            else if (std::holds_alternative<base_register>(arg))
            {
                log(conf, "(%s)", register_name(std::get<base_register>(arg).data));
            }
            else IF_ARG_TYPE_LOG(arg, shift, " %u")
            else IF_ARG_TYPE_LOG(arg, address, " %x")
            else IF_ARG_TYPE_LOG(arg, memory_offset, " %x")
            else IF_ARG_TYPE_LOG(arg, immediate<u32>, " %u")
            else IF_ARG_TYPE_LOG(arg, immediate<u16>, " %u")
            else IF_ARG_TYPE_LOG(arg, immediate<s16>, " %u")
            else IF_ARG_TYPE_LOG(arg, bitfield_pos, " %x")
            else IF_ARG_TYPE_LOG(arg, bitfield_size, " %x")
            else if (std::holds_alternative<coprocessor_register>(arg))
            {
                coprocessor_register &d = std::get<coprocessor_register>(arg);
                log(conf, " [%u, %u]", d.rd, d.sel);
            }
        }

        log(conf, "\n", 0);
    }
}
