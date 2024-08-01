
#include "shl/array.hpp"
#include "shl/assert.hpp"
#include "shl/memory.hpp"
#include "shl/fixed_array.hpp"

#include "allegrex/parse_instruction_arguments.hpp"
#include "allegrex/parse_instructions.hpp"

struct instruction_info
{
    allegrex_mnemonic mnemonic;
    u32 opcode;
    argument_parse_function_t argument_parse_function;
};

struct category
{
    u32 min;
    u32 max;
    u32 mask;

    const instruction_info *instructions;
    u64 instruction_count;
    const category * const *sub_categories;
    u64 sub_category_count;
};

// instructions
#define I(Mnemonic, Opcode, ...) \
    instruction_info{allegrex_mnemonic::Mnemonic, Opcode __VA_OPT__(,) __VA_ARGS__}

constexpr fixed_array instructions_Fixed = {
    I(NOP, 0x00000000, nullptr)
};

constexpr fixed_array instructions_SrlRotr = {
    I(SRL,  0x00000002, arg_parse_RdRtShift),
    I(ROTR, 0x00200002, arg_parse_RdRtShift)
};

constexpr fixed_array instructions_SrlvRotrv = {
    I(SRLV,  0x00000006, arg_parse_VarShift),
    I(ROTRV, 0x00000046, arg_parse_VarShift)
};

constexpr fixed_array instructions_Special = {
    I(SLL,     0x00000000, arg_parse_RdRtShift),
    I(SRA,     0x00000003, arg_parse_RdRtShift),
    I(SLLV,    0x00000004, arg_parse_VarShift),
    I(SRAV,    0x00000007, arg_parse_VarShift),
    I(JR,      0x00000008, arg_parse_RegJumpRs),
    I(JALR,    0x00000009, arg_parse_RegJumpRdRs),
    I(MOVZ,    0x0000000a, arg_parse_RdRsRt),
    I(MOVN,    0x0000000b, arg_parse_RdRsRt),
    I(SYSCALL, 0x0000000c, arg_parse_Syscall),
    I(BREAK,   0x0000000d, nullptr),
    I(SYNC,    0x0000000f, arg_parse_Sync),
    I(MFHI,    0x00000010, arg_parse_Rd),
    I(MTHI,    0x00000011, arg_parse_Rs),
    I(MFLO,    0x00000012, arg_parse_Rd),
    I(MTLO,    0x00000013, arg_parse_Rs),
    I(CLZ,     0x00000016, arg_parse_RdRs),
    I(CLO,     0x00000017, arg_parse_RdRs),
    I(MULT,    0x00000018, arg_parse_RsRt),
    I(MULTU,   0x00000019, arg_parse_RsRt),
    I(DIV,     0x0000001a, arg_parse_RsRt),
    I(DIVU,    0x0000001b, arg_parse_RsRt),
    I(MADD,    0x0000001c, arg_parse_RsRt),
    I(MADDU,   0x0000001d, arg_parse_RsRt),
    I(ADD,     0x00000020, arg_parse_RdRsRt),
    I(ADDU,    0x00000021, arg_parse_AdduOr),
    I(SUB,     0x00000022, arg_parse_RdRsRt),
    I(SUBU,    0x00000023, arg_parse_RdRsRt),
    I(AND,     0x00000024, arg_parse_RdRsRt),
    I(OR,      0x00000025, arg_parse_AdduOr),
    I(XOR,     0x00000026, arg_parse_RdRsRt),
    I(NOR,     0x00000027, arg_parse_RdRsRt),
    I(SLT,     0x0000002a, arg_parse_RdRsRt),
    I(SLTU,    0x0000002b, arg_parse_RdRsRt),
    I(MAX,     0x0000002c, arg_parse_RdRsRt),
    I(MIN,     0x0000002d, arg_parse_RdRsRt),
    I(MSUB,    0x0000002e, arg_parse_RsRt),
    I(MSUBU,   0x0000002f, arg_parse_RsRt),
    I(TGE,     0x00000030, arg_parse_RsRtCode),
    I(TGEU,    0x00000031, arg_parse_RsRtCode),
    I(TLT,     0x00000032, arg_parse_RsRtCode), 
    I(TLTU,    0x00000033, arg_parse_RsRtCode),
    I(TEQ,     0x00000034, arg_parse_RsRtCode),
    I(TNE,     0x00000036, arg_parse_RsRtCode)
};

constexpr fixed_array instructions_Cop0CO = {
    I(TLBR,  0x42000001, nullptr),
    I(TLBWI, 0x42000002, nullptr),
    I(TLBWR, 0x42000006, nullptr),
    I(TLBP,  0x42000008, nullptr),
    I(ERET,  0x42000018, nullptr),
    I(IACK,  0x42000019, nullptr),
    I(DERET, 0x4200001f, nullptr),
    I(WAIT,  0x42000020, nullptr)
};

constexpr fixed_array instructions_Cop0 = {
    I(MFC0,   0x40000000, arg_parse_Cop0RtRdSel),
    I(MTC0,   0x40800000, arg_parse_Cop0RtRdSel),
    I(RDPGPR, 0x41600000, arg_parse_RdRt),
    I(MFMC0,  0x41800000, nullptr),
    I(WRPGPR, 0x41c00000, arg_parse_RdRt)
};

constexpr fixed_array instructions_Cop1BC = {
    I(BC1F,  0x45000000, arg_parse_FPUBranchAddress),
    I(BC1T,  0x45010000, arg_parse_FPUBranchAddress),
    I(BC1FL, 0x45020000, arg_parse_FPUBranchAddress),
    I(BC1TL, 0x45030000, arg_parse_FPUBranchAddress)
};

constexpr fixed_array instructions_Cop1S = {
    I(ADD_S,     0x46000000, arg_parse_FPUFdFsFt),
    I(SUB_S,     0x46000001, arg_parse_FPUFdFsFt),
    I(MUL_S,     0x46000002, arg_parse_FPUFdFsFt),
    I(DIV_S,     0x46000003, arg_parse_FPUFdFsFt),
    I(SQRT_S,    0x46000004, arg_parse_FPUFdFs),
    I(ABS_S,     0x46000005, arg_parse_FPUFdFs),
    I(MOV_S,     0x46000006, arg_parse_FPUFdFs),
    I(NEG_S,     0x46000007, arg_parse_FPUFdFs),
    I(ROUND_W_S, 0x4600000c, arg_parse_FPUFdFs),
    I(TRUNC_W_S, 0x4600000d, arg_parse_FPUFdFs),
    I(CEIL_W_S,  0x4600000e, arg_parse_FPUFdFs),
    I(FLOOR_W_S, 0x4600000f, arg_parse_FPUFdFs),
    I(CVT_W_S,   0x46000024, arg_parse_FPUFdFs),
    I(DIS_INT,   0x46000026, nullptr),
    I(C_F_S,     0x46000030, arg_parse_FPUCompare),
    I(C_UN_S,    0x46000031, arg_parse_FPUCompare),
    I(C_EQ_S,    0x46000032, arg_parse_FPUCompare),
    I(C_UEQ_S,   0x46000033, arg_parse_FPUCompare),
    I(C_OLT_S,   0x46000034, arg_parse_FPUCompare),
    I(C_ULT_S,   0x46000035, arg_parse_FPUCompare),
    I(C_OLE_S,   0x46000036, arg_parse_FPUCompare),
    I(C_ULE_S,   0x46000037, arg_parse_FPUCompare),
    I(C_SF_S,    0x46000038, arg_parse_FPUCompare),
    I(C_NGLE_S,  0x46000039, arg_parse_FPUCompare),
    I(C_SEQ_S,   0x4600003a, arg_parse_FPUCompare),
    I(C_NGL_S,   0x4600003b, arg_parse_FPUCompare),
    I(C_LT_S,    0x4600003c, arg_parse_FPUCompare),
    I(C_NGE_S,   0x4600003d, arg_parse_FPUCompare),
    I(C_LE_S,    0x4600003e, arg_parse_FPUCompare),
    I(C_NGT_S,   0x4600003f, arg_parse_FPUCompare)
};

constexpr fixed_array instructions_Cop1W = {
    I(CVT_S_W, 0x46800020, arg_parse_FPUFdFs)
};

constexpr fixed_array instructions_Cop1 = {
    I(MFC1, 0x44000000, arg_parse_FPURtFs),
    I(CFC1, 0x44400000, arg_parse_FPURtFs),
    I(MTC1, 0x44800000, arg_parse_FPURtFs),
    I(CTC1, 0x44c00000, arg_parse_FPURtFs)
};

constexpr fixed_array instructions_Cop2BC2 = {
    I(BVF,  0x49000000, arg_parse_FPUBranchAddress),
    I(BVT,  0x49010000, arg_parse_FPUBranchAddress),
    I(BVFL, 0x49020000, arg_parse_FPUBranchAddress),
    I(BVTL, 0x49030000, arg_parse_FPUBranchAddress)
};

constexpr fixed_array instructions_Cop2 = {
    // not really sure about MFC2/CFC2/MTC2/CTC2
    I(MFC2, 0x48000000, arg_parse_VFPU_Cop2),
    I(CFC2, 0x48400000, arg_parse_VFPU_Cop2),
    I(MFV,  0x48600000, arg_parse_VFPU_MFTV),
    I(MTC2, 0x48800000, arg_parse_VFPU_Cop2),
    I(CTC2, 0x48c00000, arg_parse_VFPU_Cop2),
    I(MTV,  0x48e00000, arg_parse_VFPU_MFTV),
};

constexpr fixed_array instructions_VFPU0 = {
    I(VADD, 0x60000000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VSUB, 0x60800000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VSBN, 0x61000000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VDIV, 0x63800000, arg_parse_VFPU_Vd_Vs_Vt),
};

constexpr fixed_array instructions_VFPU1 = {
    I(VMUL, 0x64000000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VDOT, 0x64800000, arg_parse_VFPU_VdSingle_Vs_Vt),
    I(VSCL, 0x65000000, arg_parse_VFPU_Vd_Vs_VtSingle),
    I(VHDP, 0x66000000, arg_parse_VFPU_VdSingle_Vs_Vt),
    I(VCRS, 0x66800000, arg_parse_VFPU_Vcrs),
    I(VDET, 0x67000000, arg_parse_VFPU_VdSingle_Vs_Vt),
};

constexpr fixed_array instructions_VFPU3 = {
    I(VCMP,  0x6c000000, arg_parse_VFPU_Vcmp),
    I(VMIN,  0x6d000000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VMAX,  0x6d800000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VSCMP, 0x6e800000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VSGE,  0x6f000000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VSLT,  0x6f800000, arg_parse_VFPU_Vd_Vs_Vt),
};

constexpr fixed_array instructions_Special2 = {
    I(HALT, 0x70000000, nullptr),
    I(MFIC, 0x70000024, nullptr),
    I(MTIC, 0x70000026, nullptr)
};

constexpr fixed_array instructions_Allegrex0 = {
    I(WSBH,   0x7c0000a0, arg_parse_RdRt),
    I(WSBW,   0x7c0000e0, arg_parse_RdRt),
    I(SEB,    0x7c000420, arg_parse_RdRt),
    I(BITREV, 0x7c000520, arg_parse_RdRt),
    I(SEH,    0x7c000620, arg_parse_RdRt)
};

constexpr fixed_array instructions_Special3 = {
    I(EXT,   0x7c000000, arg_parse_Ext),
    I(INS,   0x7c000004, arg_parse_Ins),
    I(RDHWR, 0x7c00003b, nullptr)
};

constexpr fixed_array instructions_VFPU4 = {
    I(VMOV,   0xd0000000, arg_parse_VFPU_Vd_Vs),
    I(VABS,   0xd0010000, arg_parse_VFPU_Vd_Vs),
    I(VNEG,   0xd0020000, arg_parse_VFPU_Vd_Vs),
    I(VIDT,   0xd0030000, arg_parse_VFPU_Vd),
    I(VSAT0,  0xd0040000, arg_parse_VFPU_Vd_Vs),
    I(VSAT1,  0xd0050000, arg_parse_VFPU_Vd_Vs),
    I(VZERO,  0xd0060000, arg_parse_VFPU_Vd),
    I(VONE,   0xd0070000, arg_parse_VFPU_Vd),
    I(VRCP,   0xd0100000, arg_parse_VFPU_Vd_Vs),
    I(VRSQ,   0xd0110000, arg_parse_VFPU_Vd_Vs),
    I(VSIN,   0xd0120000, arg_parse_VFPU_Vd_Vs),
    I(VCOS,   0xd0130000, arg_parse_VFPU_Vd_Vs),
    I(VEXP2,  0xd0140000, arg_parse_VFPU_Vd_Vs),
    I(VLOG2,  0xd0150000, arg_parse_VFPU_Vd_Vs),
    I(VSQRT,  0xd0160000, arg_parse_VFPU_Vd_Vs),
    I(VASIN,  0xd0170000, arg_parse_VFPU_Vd_Vs),
    I(VNRCP,  0xd0180000, arg_parse_VFPU_Vd_Vs),
    I(VNSIN,  0xd01a0000, arg_parse_VFPU_Vd_Vs),
    I(VREXP2, 0xd01c0000, arg_parse_VFPU_Vd_Vs)
};

constexpr fixed_array instructions_VFPU7 = {
    I(VRNDS,  0xd0200000, arg_parse_VFPU_VdSingle),
    I(VRNDI,  0xd0210000, arg_parse_VFPU_Vd),
    I(VRNDF1, 0xd0220000, arg_parse_VFPU_Vd),
    I(VRNDF2, 0xd0230000, arg_parse_VFPU_Vd),
    I(VF2H,   0xd0320000, arg_parse_VFPU_VdHalf_Vs),
    I(VH2F,   0xd0330000, arg_parse_VFPU_VdDouble_Vs),
    I(VSBZ,   0xd0360000, arg_parse_VFPU_Vd_Vs),
    I(VLGB,   0xd0370000, arg_parse_VFPU_Vd_Vs),
    I(VUC2I,  0xd0380000, arg_parse_VFPU_Vd_Vs),
    I(VC2I,   0xd0390000, arg_parse_VFPU_Vd_Vs),
    I(VUS2I,  0xd03a0000, arg_parse_VFPU_Vd_Vs),
    I(VS2I,   0xd03b0000, arg_parse_VFPU_Vd_Vs),
    I(VI2UC,  0xd03c0000, arg_parse_VFPU_VdSingle_Vs),
    I(VI2C,   0xd03d0000, arg_parse_VFPU_VdHalf_Vs),
    I(VI2US,  0xd03e0000, arg_parse_VFPU_VdHalf_Vs),
    I(VI2S,   0xd03f0000, arg_parse_VFPU_VdHalf_Vs)
};

constexpr fixed_array instructions_VFPU9 = {
    I(VSRT1,  0xd0400000, arg_parse_VFPU_Vd_Vs),
    I(VSRT2,  0xd0410000, arg_parse_VFPU_Vd_Vs),
    I(VBFY1,  0xd0420000, arg_parse_VFPU_Vd_Vs),
    I(VBFY2,  0xd0430000, arg_parse_VFPU_Vd_Vs),
    I(VOCP,   0xd0440000, arg_parse_VFPU_Vd_Vs),
    I(VSOCP,  0xd0450000, arg_parse_VFPU_Vd_Vs),
    I(VFAD,   0xd0460000, arg_parse_VFPU_VdSingle_Vs),
    I(VAVG,   0xd0470000, arg_parse_VFPU_VdSingle_Vs),
    I(VSRT3,  0xd0480000, arg_parse_VFPU_Vd_Vs),
    I(VSRT4,  0xd0490000, arg_parse_VFPU_Vd_Vs),
    I(VSGN,   0xd04a0000, arg_parse_VFPU_Vd_Vs),
    I(VMFVC,  0xd0500000, arg_parse_VFPU_Vmfvc),
    I(VMTVC,  0xd0510000, arg_parse_VFPU_Vmtvc),
    I(VT4444, 0xd0590000, arg_parse_VFPU_ColorConv),
    I(VT5551, 0xd05a0000, arg_parse_VFPU_ColorConv),
    I(VT5650, 0xd05b0000, arg_parse_VFPU_ColorConv)
};

constexpr fixed_array instructions_vwbn = {
    I(VWBN, 0xd3000000, arg_parse_VFPU_Vwbn)
};

constexpr fixed_array instructions_vcmov = {
    I(VCMOVT, 0xd2a00000, arg_parse_VFPU_Vcmov),
    I(VCMOVF, 0xd2a80000, arg_parse_VFPU_Vcmov)
};

constexpr fixed_array instructions_VFPU4Jump = {
    I(VCST,  0xd0600000, arg_parse_VFPU_Vcst),
    I(VF2IN, 0xd2000000, arg_parse_VFPU_Vd_Vs_Imm5),
    I(VF2IZ, 0xd2200000, arg_parse_VFPU_Vd_Vs_Imm5),
    I(VF2IU, 0xd2400000, arg_parse_VFPU_Vd_Vs_Imm5),
    I(VF2ID, 0xd2600000, arg_parse_VFPU_Vd_Vs_Imm5),
    I(VI2F,  0xd2800000, arg_parse_VFPU_Vd_Vs_Imm5)
};

constexpr fixed_array instructions_VFPU5 = {
    I(VPFXS, 0xdc000000, arg_parse_VFPU_PrefixST),
    I(VPFXS, 0xdc800000, arg_parse_VFPU_PrefixST),
    I(VPFXT, 0xdd000000, arg_parse_VFPU_PrefixST),
    I(VPFXT, 0xdd800000, arg_parse_VFPU_PrefixST),
    I(VPFXD, 0xde000000, arg_parse_VFPU_PrefixDest),
    I(VPFXD, 0xde800000, arg_parse_VFPU_PrefixDest),
    I(VIIM,  0xdf000000, arg_parse_VFPU_Viim),
    I(VFIM,  0xdf800000, arg_parse_VFPU_Vfim)
};

constexpr fixed_array instructions_VFPUMatrix = {
    I(VMMOV,  0xf3800000, arg_parse_VFPU_MVd_MVs),
    I(VMIDT,  0xf3830000, arg_parse_VFPU_MVd),
    I(VMZERO, 0xf3860000, arg_parse_VFPU_MVd),
    I(VMONE,  0xf3870000, arg_parse_VFPU_MVd),
};

constexpr fixed_array instructions_vhtfm = {
    I(VHTFM2, 0xf0800000, arg_parse_VFPU_Vhtfm2),
    I(VTFM2,  0xf0800080, arg_parse_VFPU_Vhtfm2),
    I(VHTFM3, 0xf1000080, arg_parse_VFPU_Vhtfm3),
    I(VTFM3,  0xf1008000, arg_parse_VFPU_Vhtfm3),
    I(VHTFM4, 0xf1808000, arg_parse_VFPU_Vhtfm4),
    I(VTFM4,  0xf1808080, arg_parse_VFPU_Vhtfm4),
};

constexpr fixed_array instructions_crossquat = {
    I(VCRSP,  0xf2808000, arg_parse_VFPU_Vd_Vs_Vt),
    I(VQMUL,  0xf2808080, arg_parse_VFPU_Vd_Vs_Vt),
};

constexpr fixed_array instructions_VFPU6 = {
    I(VMMUL,  0xf0000000, arg_parse_VFPU_MVd_XVs_MVt),
    I(VMMUL,  0xf0200000, arg_parse_VFPU_MVd_XVs_MVt),
    I(VMMUL,  0xf0400000, arg_parse_VFPU_MVd_XVs_MVt),
    I(VMMUL,  0xf0600000, arg_parse_VFPU_MVd_XVs_MVt),
    I(VMSCL,  0xf2000000, arg_parse_VFPU_MVd_MVs_VtSingle),
    I(VMSCL,  0xf2200000, arg_parse_VFPU_MVd_MVs_VtSingle),
    I(VMSCL,  0xf2400000, arg_parse_VFPU_MVd_MVs_VtSingle),
    I(VMSCL,  0xf2600000, arg_parse_VFPU_MVd_MVs_VtSingle),
    I(VROT,   0xf3a00000, arg_parse_VFPU_Vrot),
};

constexpr fixed_array instructions_lvsvrl = {
    I(LVL, 0xd4000000, arg_parse_VFPU_LvSv_LRQ),
    I(LVR, 0xd4000002, arg_parse_VFPU_LvSv_LRQ),
    I(SVL, 0xf4000000, arg_parse_VFPU_LvSv_LRQ),
    I(SVR, 0xf4000002, arg_parse_VFPU_LvSv_LRQ),
};

constexpr fixed_array instructions_Immediate = {
    I(J,     0x08000000, arg_parse_JumpAddress),
    I(JAL,   0x0c000000, arg_parse_JumpAddress),
    I(BEQ,   0x10000000, arg_parse_Beq),
    I(BNE,   0x14000000, arg_parse_RsRtBranchAddress),
    I(BLEZ,  0x18000000, arg_parse_RsBranchAddress),
    I(BGTZ,  0x1c000000, arg_parse_RsBranchAddress),
    I(ADDI,  0x20000000, arg_parse_Addi),
    I(ADDIU, 0x24000000, arg_parse_Addi),
    I(SLTI,  0x28000000, arg_parse_RtRsImmediateS),
    I(SLTIU, 0x2c000000, arg_parse_RtRsSignExtendedImmediateU),
    I(ANDI,  0x30000000, arg_parse_RtRsImmediateU),
    I(ORI,   0x34000000, arg_parse_Ori),
    I(XORI,  0x38000000, arg_parse_RtRsImmediateU),
    I(LUI,   0x3c000000, arg_parse_RtImmediateU),
    I(BEQL,  0x50000000, arg_parse_Beql),
    I(BNEL,  0x54000000, arg_parse_RsRtBranchAddress),
    I(BLEZL, 0x58000000, arg_parse_RsBranchAddress),
    I(BGTZL, 0x5c000000, arg_parse_RsBranchAddress),
    I(LB,    0x80000000, arg_parse_RsRtMemOffset),
    I(LH,    0x84000000, arg_parse_RsRtMemOffset),
    I(LWL,   0x88000000, arg_parse_RsRtMemOffset),
    I(LW,    0x8c000000, arg_parse_RsRtMemOffset),
    I(LBU,   0x90000000, arg_parse_RsRtMemOffset),
    I(LHU,   0x94000000, arg_parse_RsRtMemOffset),
    I(LWR,   0x98000000, arg_parse_RsRtMemOffset),
    I(SB,    0xa0000000, arg_parse_RsRtMemOffset),
    I(SH,    0xa4000000, arg_parse_RsRtMemOffset),
    I(SWL,   0xa8000000, arg_parse_RsRtMemOffset),
    I(SW,    0xac000000, arg_parse_RsRtMemOffset),
    I(SWR,   0xb8000000, arg_parse_RsRtMemOffset),
    I(CACHE, 0xbc000000, arg_parse_Cache),
    I(LL,    0xc0000000, arg_parse_RsRtMemOffset),
    I(LWC1,  0xc4000000, arg_parse_RsFtMemOffset),
    I(LV_S,  0xc8000000, arg_parse_VFPU_LvSv_S),
    I(LV_Q,  0xd8000000, arg_parse_VFPU_LvSv_Q),
    I(SC,    0xe0000000, arg_parse_RsRtMemOffset),
    I(SWC1,  0xe4000000, arg_parse_RsFtMemOffset),
    I(SV_S,  0xe8000000, arg_parse_VFPU_LvSv_S),
    I(SV_Q,  0xf8000000, arg_parse_VFPU_LvSv_Q),
};

constexpr fixed_array instructions_RegisterImmediate = {
    I(BLTZ,    0x04000000, arg_parse_RsBranchAddress),
    I(BGEZ,    0x04010000, arg_parse_RsBranchAddress),
    I(BLTZL,   0x04020000, arg_parse_RsBranchAddress),
    I(BGEZL,   0x04030000, arg_parse_RsBranchAddress),
    I(TGEI,    0x04080000, arg_parse_RsImmediateS),
    I(TGEIU,   0x04090000, arg_parse_RsImmediateU),
    I(TLTI,    0x040a0000, arg_parse_RsImmediateS),
    I(TLTIU,   0x040b0000, arg_parse_RsImmediateU),
    I(TEQI,    0x040c0000, arg_parse_RsImmediateS),
    I(TNEI,    0x040e0000, arg_parse_RsImmediateS),
    I(BLTZAL,  0x04100000, arg_parse_RsBranchAddress),
    I(BGEZAL,  0x04110000, arg_parse_Bgezal),
    I(BLTZALL, 0x04120000, arg_parse_RsBranchAddress),
    I(BGEZALL, 0x04130000, arg_parse_RsBranchAddress),
    I(SYNCI,   0x041f0000, nullptr)
};

constexpr fixed_array instructions_VFPUSpecial = {
    I(VNOP,   0xffff0000, nullptr),
    I(VSYNC,  0xffff0320, nullptr),
    I(VFLUSH, 0xffff040d, nullptr)
};

#define CATEGORY_INSTRUCTIONS(cat) \
    .instructions = instructions_##cat.data,\
    .instruction_count = array_size(&instructions_##cat)

#define CATEGORY_SUB_CATEGORIES(cat) \
    .sub_categories = sub_categories_##cat.data,\
    .sub_category_count = array_size(&sub_categories_##cat)

// categories
constexpr category Fixed{
    .min  = 0x00000000,
    .max  = 0xffffffff,
    .mask = 0xffffffff,
    CATEGORY_INSTRUCTIONS(Fixed),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category SrlRotr{
    .min =  0x00000002,
    .max =  0x00200002,
    .mask = 0xffe0003f,
    CATEGORY_INSTRUCTIONS(SrlRotr),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category SrlvRotrv{
    .min =  0x00000006,
    .max =  0x00000046,
    .mask = 0xfc00007f,
    CATEGORY_INSTRUCTIONS(SrlvRotrv),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Special = {
    &SrlRotr,
    &SrlvRotrv
};

constexpr category Special{
    .min =  0x00000000,
    .max =  0x0000003f,
    .mask = 0xfc00003f,
    CATEGORY_INSTRUCTIONS(Special),
    CATEGORY_SUB_CATEGORIES(Special)
};

constexpr category Cop0CO{
    .min =  0x42000000,
    .max =  0x4200003f,
    .mask = 0xfe00003f,
    CATEGORY_INSTRUCTIONS(Cop0CO),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Cop0 = {
    &Cop0CO,
};

constexpr category Cop0{
    .min =  0x40000000,
    .max =  0x43e00000,
    .mask = 0xffe00000,
    CATEGORY_INSTRUCTIONS(Cop0),
    CATEGORY_SUB_CATEGORIES(Cop0)
};

constexpr category Cop1BC{
    .min =  0x45000000,
    .max =  0x45030000,
    .mask = 0xffe30000,
    CATEGORY_INSTRUCTIONS(Cop1BC),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category Cop1S{
    .min =  0x46000000,
    .max =  0x4600003f,
    .mask = 0xffe0003f,
    CATEGORY_INSTRUCTIONS(Cop1S),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category Cop1W{
    .min =  0x46800000,
    .max =  0x4680003f,
    .mask = 0xffe0003f,
    CATEGORY_INSTRUCTIONS(Cop1W),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Cop1 = {
    &Cop1BC,
    &Cop1S,
    &Cop1W
};

constexpr category Cop1{
    .min =  0x44000000,
    .max =  0x47e00000,
    .mask = 0xffe00000,
    CATEGORY_INSTRUCTIONS(Cop1),
    CATEGORY_SUB_CATEGORIES(Cop1)
};

constexpr category Cop2BC2{
    .min =  0x49000000,
    .max =  0x49030000,
    .mask = 0xffe30000,
    CATEGORY_INSTRUCTIONS(Cop2BC2),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Cop2 = {
    &Cop2BC2,
};

constexpr category Cop2{
    .min =  0x48000000,
    .max =  0x4be00000,
    .mask = 0xffe00000,
    CATEGORY_INSTRUCTIONS(Cop2),
    CATEGORY_SUB_CATEGORIES(Cop2)
};

constexpr category VFPU0{
    .min =  0x60000000,
    .max =  0x63800000,
    .mask = 0xff800000,
    CATEGORY_INSTRUCTIONS(VFPU0),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPU1{
    .min =  0x64000000,
    .max =  0x67800000,
    .mask = 0xff800000,
    CATEGORY_INSTRUCTIONS(VFPU1),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPU3{
    .min =  0x6c000000,
    .max =  0x6f800000,
    .mask = 0xff800000,
    CATEGORY_INSTRUCTIONS(VFPU3),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category Special2{
    .min =  0x70000000,
    .max =  0x7000003f,
    .mask = 0xfc00003f,
    CATEGORY_INSTRUCTIONS(Special2),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category Allegrex0{
    .min =  0x7c000020,
    .max =  0x7c0007e0,
    .mask = 0xfc0007ff,
    CATEGORY_INSTRUCTIONS(Allegrex0),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Special3 = {
    &Allegrex0,
};

constexpr category Special3{
    .min =  0x7c000000,
    .max =  0x7c00003f,
    .mask = 0xfc00003f,
    CATEGORY_INSTRUCTIONS(Special3),
    CATEGORY_SUB_CATEGORIES(Special3),
};

constexpr category VFPU4{
    .min =  0xd0000000,
    .max =  0xd01f0000,
    .mask = 0xffff0000,
    CATEGORY_INSTRUCTIONS(VFPU4),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPU7{
    .min =  0xd0200000,
    .max =  0xd03f0000,
    .mask = 0xffff0000,
    CATEGORY_INSTRUCTIONS(VFPU7),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPU9{
    .min =  0xd0400000,
    .max =  0xd05f0000,
    .mask = 0xffff0000,
    CATEGORY_INSTRUCTIONS(VFPU9),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category vwbn{
    .min =  0xd3000000,
    .max =  0xd3000000,
    .mask = 0xff000000,
    CATEGORY_INSTRUCTIONS(vwbn),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category vcmov{
    .min =  0xd2a00000,
    .max =  0xd2b80000,
    .mask = 0xfff80000,
    CATEGORY_INSTRUCTIONS(vcmov),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_VFPU4Jump = {
    &VFPU4,
    &VFPU7,
    &VFPU9,
    &vwbn,
    &vcmov
};

constexpr category VFPU4Jump{
    .min =  0xd0000000,
    .max =  0xd3e00000,
    .mask = 0xffe00000,
    CATEGORY_INSTRUCTIONS(VFPU4Jump),
    CATEGORY_SUB_CATEGORIES(VFPU4Jump)
};

constexpr category VFPU5{
    .min =  0xdc000000,
    .max =  0xdf800000,
    .mask = 0xff800000,
    CATEGORY_INSTRUCTIONS(VFPU5),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPUMatrix{
    .min =  0xf3800000,
    .max =  0xf38f0000,
    .mask = 0xffef0000,
    CATEGORY_INSTRUCTIONS(VFPUMatrix),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category vhtfm{
    .min =  0xf0800000,
    .max =  0xf1808080,
    .mask = 0xff808080,
    CATEGORY_INSTRUCTIONS(vhtfm),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category crossquat{
    .min =  0xf2808000,
    .max =  0xf2808080,
    .mask = 0xffe08080,
    CATEGORY_INSTRUCTIONS(crossquat),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_VFPU6 = {
    &VFPUMatrix,
    &vhtfm,
    &crossquat
};

constexpr category VFPU6{
    .min =  0xf0000000,
    .max =  0xf3e00000,
    .mask = 0xffe00000,
    CATEGORY_INSTRUCTIONS(VFPU6),
    CATEGORY_SUB_CATEGORIES(VFPU6)
};

constexpr category lvsvrl{
    .min =  0xd4000000,
    .max =  0xf4000002,
    .mask = 0xfc000002,
    CATEGORY_INSTRUCTIONS(lvsvrl),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_Immediate = {
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
};

constexpr category Immediate{
    .min =  0x00000000,
    .max =  0xfc000000,
    .mask = 0xfc000000,
    CATEGORY_INSTRUCTIONS(Immediate),
    CATEGORY_SUB_CATEGORIES(Immediate)
};

constexpr category RegisterImmediate{
    .min =  0x04000000,
    .max =  0x041f0000,
    .mask = 0xfc1f0000,
    CATEGORY_INSTRUCTIONS(RegisterImmediate),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr category VFPUSpecial{
    .min  = 0xffff0000,
    .max  = 0xffff04ff,
    .mask = 0xffff07ff,
    CATEGORY_INSTRUCTIONS(VFPUSpecial),
    .sub_categories = nullptr,
    .sub_category_count = 0
};

constexpr fixed_array sub_categories_AllInstructions = {
    &Fixed,
    &Immediate,
    &RegisterImmediate,
    &VFPUSpecial
};

constexpr category AllInstructions{
    .min  = 0x00000000,
    .max  = 0xffffffff,
    .mask = 0xffffffff,
    .instructions = nullptr,
    .instruction_count = 0,
    CATEGORY_SUB_CATEGORIES(AllInstructions)
};

static void _populate_instruction(instruction *instr, const instruction_info *info, const parse_instructions_config *conf)
{
    instr->mnemonic = info->mnemonic;
    
    if (info->argument_parse_function != nullptr)
        info->argument_parse_function(instr->opcode, instr, conf);

}

static bool _try_parse_category_instruction(u32 opcode, const category *cat, instruction *out, const parse_instructions_config *conf)
{
    if (cat == nullptr)
        return false;

    for (u64 i = 0; i < cat->sub_category_count; ++i)
        if (_try_parse_category_instruction(opcode, cat->sub_categories[i], out, conf))
            return true;

    u32 mop = opcode & cat->mask;

    if (mop < cat->min || mop > cat->max)
        return false;

    for (u64 i = 0; i < cat->instruction_count; ++i)
    {
        const instruction_info &instr = cat->instructions[i];

        if (mop == instr.opcode)
        {
            _populate_instruction(out, &instr, conf);
            return true;
        }
    }

    return false;
}

void parse_instruction(u32 opcode, instruction *out, set<jump_destination> *out_jumps, const parse_instructions_config *conf)
{
    bool found;

    found = _try_parse_category_instruction(opcode, &AllInstructions, out, conf);

    if (!found)
    {
        out->mnemonic = allegrex_mnemonic::_UNKNOWN;
        return;
    }

    if (out_jumps != nullptr)
    {
        // add jumps / branches
        assert(out->argument_count <= MAX_ARGUMENT_COUNT);
        for (u32 i = 0; i < out->argument_count; ++i)
        {
            if (out->argument_types[i] == argument_type::Jump_Address)
                ::insert_element(out_jumps, jump_destination{out->arguments[i].jump_address.data, jump_type::Jump});
            else if (out->argument_types[i] == argument_type::Branch_Address)
                ::insert_element(out_jumps, jump_destination{out->arguments[i].branch_address.data, jump_type::Branch});
        }
    }
}

void parse_instructions(const char *input, u64 size, array<instruction> *out_instructions, set<jump_destination> *out_jumps, const parse_instructions_config *conf)
{
    assert(size % sizeof(u32) == 0);
    assert(size <= max_value(u32));

    u32 instruction_count = (u32)(size / sizeof(u32));
    ::reserve(out_instructions, out_instructions->size + instruction_count);

    u32 *in_data = (u32*)(input);

    for (u32 addr = 0x00000000, i = 0; addr < size; addr += sizeof(u32), ++i)
    {
        instruction *out_inst = ::add_at_end(out_instructions);
        *out_inst = {};
        out_inst->opcode = in_data[i];
        out_inst->address = conf->vaddr + addr;

        parse_instruction(out_inst->opcode, out_inst, out_jumps, conf);
    }
}
