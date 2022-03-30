
#include <stdexcept>
#include <assert.h>

#include "string.hpp"
#include "parse_instruction_arguments.hpp"
#include "parse_instructions.hpp"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

struct instruction_info
{
    allegrex_mnemonic mnemonic;
    u32 opcode;
    argument_parse_function_t argument_parse_function;
    /* TODO: format / string function */
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
        {allegrex_mnemonic::NOP, 0x00000000, nullptr}
    },
    .sub_categories = {}
};

const category SrlRotr{
    .min =  0x00000002,
    .max =  0x00200002,
    .mask = 0xffe0003f,
    .instructions = {
        {allegrex_mnemonic::SRL,  0x00000002, arg_parse_RdRtShift},
        {allegrex_mnemonic::ROTR, 0x00200002, arg_parse_RdRtShift}
    },
    .sub_categories = {}
};

const category SrlvRotrv{
    .min =  0x00000006,
    .max =  0x00000046,
    .mask = 0xfc00007f,
    .instructions = {
        {allegrex_mnemonic::SRLV,  0x00000006, arg_parse_VarShift},
        {allegrex_mnemonic::ROTRV, 0x00000046, arg_parse_VarShift}
    },
    .sub_categories = {}
};

const category Special{
    .min =  0x00000000,
    .max =  0x0000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {allegrex_mnemonic::SLL,     0x00000000, arg_parse_RdRtShift},
        {allegrex_mnemonic::SRA,     0x00000003, arg_parse_RdRtShift},
        {allegrex_mnemonic::SLLV,    0x00000004, arg_parse_VarShift},
        {allegrex_mnemonic::SRAV,    0x00000007, arg_parse_VarShift},
        {allegrex_mnemonic::JR,      0x00000008, arg_parse_RegJumpRs},
        {allegrex_mnemonic::JALR,    0x00000009, arg_parse_RegJumpRdRs},
        {allegrex_mnemonic::MOVZ,    0x0000000a, arg_parse_RsRtRd},
        {allegrex_mnemonic::MOVN,    0x0000000b, arg_parse_RsRtRd},
        {allegrex_mnemonic::SYSCALL, 0x0000000c, arg_parse_Syscall},
        {allegrex_mnemonic::BREAK,   0x0000000d, nullptr},
        {allegrex_mnemonic::SYNC,    0x0000000f, arg_parse_Sync},
        {allegrex_mnemonic::MFHI,    0x00000010, arg_parse_Rd},
        {allegrex_mnemonic::MTHI,    0x00000011, arg_parse_Rs},
        {allegrex_mnemonic::MFLO,    0x00000012, arg_parse_Rd},
        {allegrex_mnemonic::MTLO,    0x00000013, arg_parse_Rs},
        {allegrex_mnemonic::CLZ,     0x00000016, arg_parse_RsRd},
        {allegrex_mnemonic::CLO,     0x00000017, arg_parse_RsRd},
        {allegrex_mnemonic::MULT,    0x00000018, arg_parse_RsRt},
        {allegrex_mnemonic::MULTU,   0x00000019, arg_parse_RsRt},
        {allegrex_mnemonic::DIV,     0x0000001a, arg_parse_RsRt},
        {allegrex_mnemonic::DIVU,    0x0000001b, arg_parse_RsRt},
        {allegrex_mnemonic::MADD,    0x0000001c, arg_parse_RsRt},
        {allegrex_mnemonic::MADDU,   0x0000001d, arg_parse_RsRt},
        {allegrex_mnemonic::ADD,     0x00000020, arg_parse_RsRtRd},
        {allegrex_mnemonic::ADDU,    0x00000021, arg_parse_AdduOr},
        {allegrex_mnemonic::SUB,     0x00000022, arg_parse_RsRtRd},
        {allegrex_mnemonic::SUBU,    0x00000023, arg_parse_RsRtRd},
        {allegrex_mnemonic::AND,     0x00000024, arg_parse_RsRtRd},
        {allegrex_mnemonic::OR,      0x00000025, arg_parse_AdduOr},
        {allegrex_mnemonic::XOR,     0x00000026, arg_parse_RsRtRd},
        {allegrex_mnemonic::NOR,     0x00000027, arg_parse_RsRtRd},
        {allegrex_mnemonic::SLT,     0x0000002a, arg_parse_RsRtRd},
        {allegrex_mnemonic::SLTU,    0x0000002b, arg_parse_RsRtRd},
        {allegrex_mnemonic::MAX,     0x0000002c, arg_parse_RsRtRd},
        {allegrex_mnemonic::MIN,     0x0000002d, arg_parse_RsRtRd},
        {allegrex_mnemonic::MSUB,    0x0000002e, arg_parse_RsRt},
        {allegrex_mnemonic::MSUBU,   0x0000002f, arg_parse_RsRt},
        {allegrex_mnemonic::TGE,     0x00000030, arg_parse_RsRtCode},
        {allegrex_mnemonic::TGEU,    0x00000031, arg_parse_RsRtCode},
        {allegrex_mnemonic::TLT,     0x00000032, arg_parse_RsRtCode}, 
        {allegrex_mnemonic::TLTU,    0x00000033, arg_parse_RsRtCode},
        {allegrex_mnemonic::TEQ,     0x00000034, arg_parse_RsRtCode},
        {allegrex_mnemonic::TNE,     0x00000036, arg_parse_RsRtCode},
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
        {allegrex_mnemonic::TLBR,  0x42000001, nullptr},
        {allegrex_mnemonic::TLBWI, 0x42000002, nullptr},
        {allegrex_mnemonic::TLBWR, 0x42000006, nullptr},
        {allegrex_mnemonic::TLBP,  0x42000008, nullptr},
        {allegrex_mnemonic::ERET,  0x42000018, nullptr},
        {allegrex_mnemonic::IACK,  0x42000019, nullptr},
        {allegrex_mnemonic::DERET, 0x4200001f, nullptr},
        {allegrex_mnemonic::WAIT,  0x42000020, nullptr}
    },
    .sub_categories = {}
};

const category Cop0{
    .min =  0x40000000,
    .max =  0x43e00000,
    .mask = 0xffe00000,
    .instructions = {
        {allegrex_mnemonic::MFC0,   0x40000000, arg_parse_Cop0RtRdSel},
        {allegrex_mnemonic::MTC0,   0x40800000, arg_parse_Cop0RtRdSel},
        {allegrex_mnemonic::RDPGPR, 0x41600000, arg_parse_RdRt},
        {allegrex_mnemonic::MFMC0,  0x41800000, nullptr},
        {allegrex_mnemonic::WRPGPR, 0x41c00000, arg_parse_RdRt},
    },
    .sub_categories = {
        &Cop0CO
    }
};

const category Cop1BC{
    .min =  0x45000000,
    .max =  0x45030000,
    .mask = 0xffe30000,
    .instructions = {
        {allegrex_mnemonic::BC1F,  0x45000000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BC1T,  0x45010000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BC1FL, 0x45020000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BC1TL, 0x45030000, arg_parse_FPURelAddress},
    },
    .sub_categories = {}
};

const category Cop1S{
    .min =  0x46000000,
    .max =  0x4600003f,
    .mask = 0xffe0003f,
    .instructions = {
        {allegrex_mnemonic::ADD_S,     0x46000000, arg_parse_FPUFtFsFd},
        {allegrex_mnemonic::SUB_S,     0x46000001, arg_parse_FPUFtFsFd},
        {allegrex_mnemonic::MUL_S,     0x46000002, arg_parse_FPUFtFsFd},
        {allegrex_mnemonic::DIV_S,     0x46000003, arg_parse_FPUFtFsFd},
        {allegrex_mnemonic::SQRT_S,    0x46000004, arg_parse_FPUFsFd},
        {allegrex_mnemonic::ABS_S,     0x46000005, arg_parse_FPUFsFd},
        {allegrex_mnemonic::MOV_S,     0x46000006, arg_parse_FPUFsFd},
        {allegrex_mnemonic::NEG_S,     0x46000007, arg_parse_FPUFsFd},
        {allegrex_mnemonic::ROUND_W_S, 0x4600000c, arg_parse_FPUFsFd},
        {allegrex_mnemonic::TRUNC_W_S, 0x4600000d, arg_parse_FPUFsFd},
        {allegrex_mnemonic::CEIL_W_S,  0x4600000e, arg_parse_FPUFsFd},
        {allegrex_mnemonic::FLOOR_W_S, 0x4600000f, arg_parse_FPUFsFd},
        {allegrex_mnemonic::CVT_W_S,   0x46000024, arg_parse_FPUFsFd},
        {allegrex_mnemonic::DIS_INT,   0x46000026, nullptr},
        {allegrex_mnemonic::C_F_S,     0x46000030, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_UN_S,    0x46000031, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_EQ_S,    0x46000032, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_UEQ_S,   0x46000033, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_OLT_S,   0x46000034, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_OLE_S,   0x46000036, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_ULE_S,   0x46000037, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_SF_S,    0x46000038, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_NGLE_S,  0x46000039, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_SEQ_S,   0x4600003a, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_LT_S,    0x4600003c, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_NGE_S,   0x4600003d, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_LE_S,    0x4600003e, arg_parse_FPUCompare},
        {allegrex_mnemonic::C_NGT_S,   0x4600003f, arg_parse_FPUCompare}
    },
    .sub_categories = {}
};

const category Cop1W{
    .min =  0x46800000,
    .max =  0x4680003f,
    .mask = 0xffe0003f,
    .instructions = {
        {allegrex_mnemonic::CVT_S_W, 0x46800020, arg_parse_FPUFsFd},
    },
    .sub_categories = {}
};

const category Cop1{
    .min =  0x44000000,
    .max =  0x47e00000,
    .mask = 0xffe00000,
    .instructions = {
        {allegrex_mnemonic::MFC1, 0x44000000, arg_parse_FPURtFs},
        {allegrex_mnemonic::CFC1, 0x44400000, arg_parse_FPURtFs},
        {allegrex_mnemonic::MTC1, 0x44800000, arg_parse_FPURtFs},
        {allegrex_mnemonic::CTC1, 0x44c00000, arg_parse_FPURtFs},
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
        {allegrex_mnemonic::BVF,  0x49000000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BVT,  0x49010000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BVFL, 0x49020000, arg_parse_FPURelAddress},
        {allegrex_mnemonic::BVTL, 0x49030000, arg_parse_FPURelAddress},
    },
    .sub_categories = {}
};

const category Cop2{
    .min =  0x48000000,
    .max =  0x4be00000,
    .mask = 0xffe00000,
    .instructions = {
        // not really sure with MFC2/CFC2/MTC2/CTC2
        {allegrex_mnemonic::MFC2, 0x48000000, arg_parse_VFPU_Cop2},
        {allegrex_mnemonic::CFC2, 0x48400000, arg_parse_VFPU_Cop2},
        {allegrex_mnemonic::MFV,  0x48600000, arg_parse_VFPU_MFTV},
        {allegrex_mnemonic::MTC2, 0x48800000, arg_parse_VFPU_Cop2},
        {allegrex_mnemonic::CTC2, 0x48c00000, arg_parse_VFPU_Cop2},
        {allegrex_mnemonic::MTV,  0x48e00000, arg_parse_VFPU_MFTV},

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
        {allegrex_mnemonic::VADD, 0x60000000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VSUB, 0x60800000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VSBN, 0x61000000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VDIV, 0x63800000, arg_parse_VFPU_Vd_Vs_Vt},
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
        {allegrex_mnemonic::VMUL, 0x64000000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VDOT, 0x64800000, arg_parse_VFPU_VdSingle_Vs_Vt},
        {allegrex_mnemonic::VSCL, 0x65000000, arg_parse_VFPU_Vd_Vs_VtSingle},
        {allegrex_mnemonic::VHDP, 0x66000000, arg_parse_VFPU_VdSingle_Vs_Vt},
        {allegrex_mnemonic::VCRS, 0x66800000, arg_parse_VFPU_Vcrs},
        {allegrex_mnemonic::VDET, 0x67000000, arg_parse_VFPU_VdSingle_Vs_Vt},
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
        {allegrex_mnemonic::VCMP,  0x6c000000, arg_parse_VFPU_Vcmp},
        {allegrex_mnemonic::VMIN,  0x6d000000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VMAX,  0x6d800000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VSCMP, 0x6e800000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VSGE,  0x6f000000, arg_parse_VFPU_Vd_Vs_Vt},
        {allegrex_mnemonic::VSLT,  0x6f800000, arg_parse_VFPU_Vd_Vs_Vt},
    },
    .sub_categories = {
    }
};

const category Special2{
    .min =  0x70000000,
    .max =  0x7000003f,
    .mask = 0xfc00003f,
    .instructions = {
        {allegrex_mnemonic::HALT, 0x70000000, nullptr},
        {allegrex_mnemonic::MFIC, 0x70000024, nullptr},
        {allegrex_mnemonic::MTIC, 0x70000026, nullptr},
    },
    .sub_categories = {
    }
};

const category Allegrex0{
    .min =  0x7c000020,
    .max =  0x7c0007e0,
    .mask = 0xfc0007ff,
    .instructions = {
        {allegrex_mnemonic::WSBH,   0x7c0000a0, arg_parse_RdRt},
        {allegrex_mnemonic::WSBW,   0x7c0000e0, arg_parse_RdRt},
        {allegrex_mnemonic::SEB,    0x7c000420, arg_parse_RdRt},
        {allegrex_mnemonic::BITREV, 0x7c000520, arg_parse_RdRt},
        {allegrex_mnemonic::SEH,    0x7c000620, arg_parse_RdRt}
    },
    .sub_categories = {}
};

const category Special3{
    .min =  0x7c000000,
    .max =  0x7c00003f,
    .mask = 0xfc00003f,
    .instructions = {
        {allegrex_mnemonic::EXT,   0x7c000000, arg_parse_Ext},
        {allegrex_mnemonic::INS,   0x7c000004, arg_parse_Ins},
        {allegrex_mnemonic::RDHWR, 0x7c00003b, nullptr}
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
        {allegrex_mnemonic::VMOV,   0xd0000000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VABS,   0xd0010000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VNEG,   0xd0020000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VIDT,   0xd0030000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VSAT0,  0xd0040000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSAT1,  0xd0050000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VZERO,  0xd0060000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VONE,   0xd0070000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VRCP,   0xd0100000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VRSQ,   0xd0110000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSIN,   0xd0120000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VCOS,   0xd0130000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VEXP2,  0xd0140000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VLOG2,  0xd0150000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSQRT,  0xd0160000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VASIN,  0xd0170000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VNRCP,  0xd0180000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VNSIN,  0xd01a0000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VREXP2, 0xd01c0000, arg_parse_VFPU_Vd_Vs}
    },
    .sub_categories = {
    }
};

const category VFPU7{
    .min =  0xd0200000,
    .max =  0xd03f0000,
    .mask = 0xffff0000,
    .instructions = {
        {allegrex_mnemonic::VRNDS,  0xd0200000, arg_parse_VFPU_VdSingle},
        {allegrex_mnemonic::VRNDI,  0xd0210000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VRNDF1, 0xd0220000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VRNDF2, 0xd0230000, arg_parse_VFPU_Vd},
        {allegrex_mnemonic::VF2H,   0xd0320000, arg_parse_VFPU_VdHalf_Vs},
        {allegrex_mnemonic::VH2F,   0xd0330000, arg_parse_VFPU_VdDouble_Vs},
        {allegrex_mnemonic::VSBZ,   0xd0360000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VLGB,   0xd0370000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VUC2I,  0xd0380000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VC2I,   0xd0390000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VUS2I,  0xd03a0000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VS2I,   0xd03b0000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VI2UC,  0xd03c0000, arg_parse_VFPU_VdHalf_Vs},
        {allegrex_mnemonic::VI2C,   0xd03d0000, arg_parse_VFPU_VdHalf_Vs},
        {allegrex_mnemonic::VI2US,  0xd03e0000, arg_parse_VFPU_VdHalf_Vs},
        {allegrex_mnemonic::VI2S,   0xd03f0000, arg_parse_VFPU_VdHalf_Vs}
    },
    .sub_categories = {
    }
};

const category VFPU9{
    .min =  0xd0400000,
    .max =  0xd05f0000,
    .mask = 0xffff0000,
    .instructions = {
        {allegrex_mnemonic::VSRT1,  0xd0400000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSRT2,  0xd0410000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VBFY1,  0xd0420000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VBFY2,  0xd0430000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VOCP,   0xd0440000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSOCP,  0xd0450000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VFAD,   0xd0460000, arg_parse_VFPU_VdSingle_Vs},
        {allegrex_mnemonic::VAVG,   0xd0470000, arg_parse_VFPU_VdSingle_Vs},
        {allegrex_mnemonic::VSRT3,  0xd0480000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSRT4,  0xd0490000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VSGN,   0xd04a0000, arg_parse_VFPU_Vd_Vs},
        {allegrex_mnemonic::VMFVC,  0xd0500000, arg_parse_VFPU_Vmfvc},
        {allegrex_mnemonic::VMTVC,  0xd0510000, arg_parse_VFPU_Vmtvc},
        {allegrex_mnemonic::VT4444, 0xd0590000, arg_parse_VFPU_ColorConv},
        {allegrex_mnemonic::VT5551, 0xd05a0000, arg_parse_VFPU_ColorConv},
        {allegrex_mnemonic::VT5650, 0xd05b0000, arg_parse_VFPU_ColorConv}
    },
    .sub_categories = {
    }
};

const category vwbn{
    .min =  0xd3000000,
    .max =  0xd3000000,
    .mask = 0xff000000,
    .instructions = {
        {allegrex_mnemonic::VWBN, 0xd3000000, arg_parse_VFPU_Vwbn}
    },
    .sub_categories = {}
};

const category vcmov{
    .min =  0xd2a00000,
    .max =  0xd2b80000,
    .mask = 0xfff80000,
    .instructions = {
        {allegrex_mnemonic::VCMOVT, 0xd2a00000, arg_parse_VFPU_Vcmov},
        {allegrex_mnemonic::VCMOVF, 0xd2a80000, arg_parse_VFPU_Vcmov}
    },
    .sub_categories = {}
};

const category VFPU4Jump{
    .min =  0xd0000000,
    .max =  0xd3e00000,
    .mask = 0xffe00000,
    .instructions = {
        {allegrex_mnemonic::VCST,  0xd0600000, arg_parse_VFPU_Vcst},
        {allegrex_mnemonic::VF2IN, 0xd2000000, arg_parse_VFPU_Vd_Vs_Imm5},
        {allegrex_mnemonic::VF2IZ, 0xd2200000, arg_parse_VFPU_Vd_Vs_Imm5},
        {allegrex_mnemonic::VF2IU, 0xd2400000, arg_parse_VFPU_Vd_Vs_Imm5},
        {allegrex_mnemonic::VF2ID, 0xd2600000, arg_parse_VFPU_Vd_Vs_Imm5},
        {allegrex_mnemonic::VF2F,  0xd2800000, arg_parse_VFPU_Vd_Vs_Imm5}
    },
    .sub_categories = {
        &VFPU4,
        &VFPU7,
        &VFPU9,
        &vwbn,
        &vcmov
    }
};

const category VFPU5{
    .min =  0xdc000000,
    .max =  0xdf800000,
    .mask = 0xff800000,
    .instructions = {
        {allegrex_mnemonic::VPFXS, 0xdc000000, arg_parse_VFPU_PrefixST},
        {allegrex_mnemonic::VPFXS, 0xdc800000, arg_parse_VFPU_PrefixST},
        {allegrex_mnemonic::VPFXT, 0xdd000000, arg_parse_VFPU_PrefixST},
        {allegrex_mnemonic::VPFXT, 0xdd800000, arg_parse_VFPU_PrefixST},
        {allegrex_mnemonic::VPFXD, 0xde000000, arg_parse_VFPU_PrefixDest},
        {allegrex_mnemonic::VPFXD, 0xde800000, arg_parse_VFPU_PrefixDest},
        {allegrex_mnemonic::VIIM,  0xdf000000, arg_parse_VFPU_Viim},
        {allegrex_mnemonic::VFIM,  0xdf800000, arg_parse_VFPU_Vfim}
    },
    .sub_categories = {}
};

const category VFPUMatrix{
    .min =  0xf3800000,
    .max =  0xf38f0000,
    .mask = 0xffef0000,
    .instructions = {
        {allegrex_mnemonic::VMMOV,  0xf3800000},
        {allegrex_mnemonic::VMIDT,  0xf3830000},
        {allegrex_mnemonic::VMZERO, 0xf3860000},
        {allegrex_mnemonic::VMONE,  0xf3870000},
    },
    .sub_categories = {}
};

const category VFPU6{
    .min =  0xf0000000,
    .max =  0xf3e00000,
    .mask = 0xffe00000,
    .instructions = {
        {allegrex_mnemonic::VMMUL, 0xf0000000},
        {allegrex_mnemonic::VMMUL, 0xf0200000},
        {allegrex_mnemonic::VMMUL, 0xf0400000},
        {allegrex_mnemonic::VMMUL, 0xf0600000},
        {allegrex_mnemonic::VTFM2, 0xf0800000},
        {allegrex_mnemonic::VTFM2, 0xf0a00000},
        {allegrex_mnemonic::VTFM2, 0xf0c00000},
        {allegrex_mnemonic::VTFM2, 0xf0e00000},
        {allegrex_mnemonic::VTFM3, 0xf1000000},
        {allegrex_mnemonic::VTFM3, 0xf1200000},
        {allegrex_mnemonic::VTFM3, 0xf1400000},
        {allegrex_mnemonic::VTFM3, 0xf1600000},
        {allegrex_mnemonic::VTFM4, 0xf1800000},
        {allegrex_mnemonic::VTFM4, 0xf1a00000},
        {allegrex_mnemonic::VTFM4, 0xf1c00000},
        {allegrex_mnemonic::VTFM4, 0xf1e00000},
        {allegrex_mnemonic::VMSCL, 0xf2000000},
        {allegrex_mnemonic::VMSCL, 0xf2200000},
        {allegrex_mnemonic::VMSCL, 0xf2400000},
        {allegrex_mnemonic::VMSCL, 0xf2600000},
        {allegrex_mnemonic::VCRSP, 0xf2800000},
        {allegrex_mnemonic::VROT,  0xf3a00000},
    },
    .sub_categories = {
        &VFPUMatrix
    }
};

const category lvsvrl{
    .min =  0xd4000000,
    .max =  0xf4000002,
    .mask = 0xfc000002,
    .instructions = {
        {allegrex_mnemonic::LVL, 0xd4000000, arg_parse_VFPU_LvSv_LRQ},
        {allegrex_mnemonic::LVR, 0xd4000002, arg_parse_VFPU_LvSv_LRQ},
        {allegrex_mnemonic::SVL, 0xf4000000, arg_parse_VFPU_LvSv_LRQ},
        {allegrex_mnemonic::SVR, 0xf4000002, arg_parse_VFPU_LvSv_LRQ},
    },
    .sub_categories = {
    }
};

const category Immediate{
    .min =  0x00000000,
    .max =  0xfc000000,
    .mask = 0xfc000000,
    .instructions = {
        {allegrex_mnemonic::J,     0x08000000, arg_parse_JumpAddress},
        {allegrex_mnemonic::JAL,   0x0c000000, arg_parse_JumpAddress},
        {allegrex_mnemonic::BEQ,   0x10000000, arg_parse_Beq},
        {allegrex_mnemonic::BNE,   0x14000000, arg_parse_RsRtRelAddress},
        {allegrex_mnemonic::BLEZ,  0x18000000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGTZ,  0x1c000000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::ADDI,  0x20000000, arg_parse_Addi},
        {allegrex_mnemonic::ADDIU, 0x24000000, arg_parse_Addi},
        {allegrex_mnemonic::SLTI,  0x28000000, arg_parse_RsRtImmediateS},
        {allegrex_mnemonic::SLTIU, 0x2c000000, arg_parse_RsRtImmediateU},
        {allegrex_mnemonic::ANDI,  0x30000000, arg_parse_RsRtImmediateS},
        {allegrex_mnemonic::ORI,   0x34000000, arg_parse_Ori},
        {allegrex_mnemonic::XORI,  0x38000000, arg_parse_RsRtImmediateU},
        {allegrex_mnemonic::LUI,   0x3c000000, arg_parse_RtImmediateU},
        {allegrex_mnemonic::BEQL,  0x50000000, arg_parse_Beql},
        {allegrex_mnemonic::BNEL,  0x54000000, arg_parse_RsRtRelAddress},
        {allegrex_mnemonic::BLEZL, 0x58000000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGTZL, 0x5c000000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::LB,    0x80000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LH,    0x84000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LWL,   0x88000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LW,    0x8c000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LBU,   0x90000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LHU,   0x94000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LWR,   0x98000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SB,    0xa0000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SH,    0xa4000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SWL,   0xa8000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SW,    0xac000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SWR,   0xb8000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::CACHE, 0xbc000000, arg_parse_Cache},
        {allegrex_mnemonic::LL,    0xc0000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::LWC1,  0xc4000000, arg_parse_RsFtMemOffset},
        {allegrex_mnemonic::LV_S,  0xc8000000, arg_parse_VFPU_LvSv_S},
        {allegrex_mnemonic::LV_Q,  0xd8000000, arg_parse_VFPU_LvSv_Q},
        {allegrex_mnemonic::SC,    0xe0000000, arg_parse_RsRtMemOffset},
        {allegrex_mnemonic::SWC1,  0xe4000000, arg_parse_RsFtMemOffset},
        {allegrex_mnemonic::SV_S,  0xe8000000, arg_parse_VFPU_LvSv_S},
        {allegrex_mnemonic::SV_Q,  0xf8000000, arg_parse_VFPU_LvSv_Q},
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
        &VFPU6,
        &lvsvrl
    }
};

const category RegisterImmediate{
    .min =  0x04000000,
    .max =  0x041f0000,
    .mask = 0xfc1f0000,
    .instructions = {
        {allegrex_mnemonic::BLTZ,    0x04000000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGEZ,    0x04010000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BLTZL,   0x04020000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGEZL,   0x04030000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::TGEI,    0x04080000, arg_parse_RsImmediateS},
        {allegrex_mnemonic::TGEIU,   0x04090000, arg_parse_RsImmediateU},
        {allegrex_mnemonic::TLTI,    0x040a0000, arg_parse_RsImmediateS},
        {allegrex_mnemonic::TLTIU,   0x040b0000, arg_parse_RsImmediateU},
        {allegrex_mnemonic::TEQI,    0x040c0000, arg_parse_RsImmediateS},
        {allegrex_mnemonic::TNEI,    0x040e0000, arg_parse_RsImmediateS},
        {allegrex_mnemonic::BLTZAL,  0x04100000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGEZAL,  0x04110000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BLTZALL, 0x04120000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::BGEZALL, 0x04130000, arg_parse_RsRelAddress},
        {allegrex_mnemonic::SYNCI,   0x041f0000, nullptr}
    },
    .sub_categories = {}
};

const category VFPUSpecial{
    .min  = 0xffff0000,
    .max  = 0xffff04ff,
    .mask = 0xffff07ff,
    .instructions = {
        {allegrex_mnemonic::VNOP,   0xffff0000, nullptr},
        {allegrex_mnemonic::VSYNC,  0xffff0320, nullptr},
        {allegrex_mnemonic::VFLUSH, 0xffff040d, nullptr}
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

void populate_instruction(instruction *instr, const instruction_info *info, const parse_config *conf)
{
    instr->mnemonic = info->mnemonic;
    
    if (info->argument_parse_function != nullptr)
        info->argument_parse_function(instr->opcode, instr, conf);
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
            populate_instruction(out, &instr, conf);
            return true;
        }

    return false;
}

void parse_instruction(u32 opcode, const parse_config *conf, instruction *out)
{
    bool found;

    found = try_parse_category_instruction(opcode, &AllInstructions, conf, out);

    if (!found)
        out->mnemonic = allegrex_mnemonic::_UNKNOWN;
}

#define IF_ARG_TYPE_LOG(arg, T, FMT) \
    if (std::holds_alternative<T>(arg)) \
    { \
        log(conf, FMT, std::get<T>(arg).data); \
    }

void log_instruction(const instruction *inst, const parse_config *conf)
{
    const char *name = get_mnemonic_name(inst->mnemonic);
    log(conf, "%06x %08x   %-10s", inst->address, inst->opcode, name);

    for (auto arg : inst->arguments)
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
        else if (std::holds_alternative<vfpu_register>(arg))
        {
            log(conf, " %s", register_name(std::get<vfpu_register>(arg)));
        }
        else if (std::holds_alternative<vfpu_condition>(arg))
        {
            log(conf, " %s", vfpu_condition_name(std::get<vfpu_condition>(arg)));
        }
        else if (std::holds_alternative<vfpu_constant>(arg))
        {
            log(conf, " %s", vfpu_constant_name(std::get<vfpu_constant>(arg)));
        }
        else if (std::holds_alternative<vfpu_prefix_array>(arg))
        {
            auto &arr = std::get<vfpu_prefix_array>(arg).data;
            log(conf, " [%s,%s,%s,%s]", vfpu_prefix_name(arr[0])
                                      , vfpu_prefix_name(arr[1])
                                      , vfpu_prefix_name(arr[2])
                                      , vfpu_prefix_name(arr[3])
               );
        }
        else if (std::holds_alternative<vfpu_destination_prefix_array>(arg))
        {
            auto &arr = std::get<vfpu_destination_prefix_array>(arg).data;
            log(conf, " [%s,%s,%s,%s]", vfpu_destination_prefix_name(arr[0])
                                      , vfpu_destination_prefix_name(arr[1])
                                      , vfpu_destination_prefix_name(arr[2])
                                      , vfpu_destination_prefix_name(arr[3])
               );
        }
        else if (std::holds_alternative<base_register>(arg))
        {
            log(conf, "(%s)", register_name(std::get<base_register>(arg).data));
        }
        else if (std::holds_alternative<const syscall*>(arg))
        {
            const syscall *sc = std::get<const syscall*>(arg);
            log(conf, " %s <0x%08x>", sc->function_name, sc->id);
        }
        else IF_ARG_TYPE_LOG(arg, shift, " %u")
        else IF_ARG_TYPE_LOG(arg, address, " %x")
        else IF_ARG_TYPE_LOG(arg, memory_offset, " %x")
        else IF_ARG_TYPE_LOG(arg, immediate<u32>, " %u")
        else IF_ARG_TYPE_LOG(arg, immediate<u16>, " %u")
        else IF_ARG_TYPE_LOG(arg, immediate<s16>, " %d")
        else IF_ARG_TYPE_LOG(arg, immediate<u8>, " %u")
        else IF_ARG_TYPE_LOG(arg, immediate<float>, " %f")
        else IF_ARG_TYPE_LOG(arg, condition_code, " (CC[%x])")
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

        log_instruction(&inst, conf);
    }
}
