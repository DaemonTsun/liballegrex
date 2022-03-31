
#pragma once

#include "number_types.hpp"

// not called instruction to avoid confusion between
// instruction struct and mnemonics.
// also these are just the mnemonics.
enum class allegrex_mnemonic : u32
{
    NOP,
    SLL,
    SRL,
    SRA,
    SLLV,
    SRLV,
    SRAV,
    JR,
    JALR,
    MOVZ,
    MOVN,
    SYSCALL,
    BREAK,
    SYNC,
    MFHI,
    MTHI,
    MFLO,
    MTLO,
    CLZ,
    CLO,
    MULT,
    MULTU,
    DIV,
    DIVU,
    MADD,
    MADDU,
    ADD,
    MOVE,
    ADDU,
    SUB,
    SUBU,
    AND,
    OR,
    XOR,
    NOR,
    SLT,
    SLTU,
    MAX,
    MIN,
    MSUB,
    MSUBU,
    TGE,
    TGEU,
    TLT,
    TLTU,
    TEQ,
    TNE,
    ROTRV,
    ROTR,
    BLTZ,
    BGEZ,
    BLTZL,
    BGEZL,
    TGEI,
    TGEIU,
    TLTI,
    TLTIU,
    TEQI,
    TNEI,
    BLTZAL,
    BGEZAL,
    BLTZALL,
    BGEZALL,
    SYNCI,
    J,
    JAL,
    B,
    BEQ,
    BNE,
    BLEZ,
    BGTZ,
    LI,
    ADDI,
    ADDIU,
    SLTI,
    SLTIU,
    ANDI,
    ORI,
    XORI,
    LUI,
    MFC0,
    MTC0,
    RDPGPR,
    MFMC0,
    WRPGPR,
    TLBR,
    TLBWI,
    TLBWR,
    TLBP,
    ERET,
    IACK,
    DERET,
    WAIT,
    MFC1,
    CFC1,
    MTC1,
    CTC1,
    BC1F,
    BC1T,
    BC1FL,
    BC1TL,
    ADD_S,
    SUB_S,
    MUL_S,
    DIV_S,
    SQRT_S,
    ABS_S,
    MOV_S,
    NEG_S,
    ROUND_W_S,
    TRUNC_W_S,
    CEIL_W_S,
    FLOOR_W_S,
    CVT_W_S,
    DIS_INT,
    C_F_S,
    C_UN_S,
    C_EQ_S,
    C_UEQ_S,
    C_OLT_S,
    C_OLE_S,
    C_ULE_S,
    C_SF_S,
    C_NGLE_S,
    C_SEQ_S,
    C_LT_S,
    C_NGE_S,
    C_LE_S,
    C_NGT_S,
    CVT_S_W,
    MFC2,
    CFC2,
    MFV,
    MTC2,
    CTC2,
    MTV,
    BVF,
    BVT,
    BVFL,
    BVTL,
    BL,
    BEQL,
    BNEL,
    BLEZL,
    BGTZL,
    VADD,
    VSUB,
    VSBN,
    VDIV,
    VMUL,
    VDOT,
    VSCL,
    VHDP,
    VCRS,
    VDET,
    VCMP,
    VMIN,
    VMAX,
    VSCMP,
    VSGE,
    VSLT,
    HALT,
    MFIC,
    MTIC,
    EXT,
    INS,
    RDHWR,
    WSBH,
    WSBW,
    SEB,
    BITREV,
    SEH,
    LB,
    LH,
    LWL,
    LW,
    LBU,
    LHU,
    LWR,
    SB,
    SH,
    SWL,
    SW,
    SWR,
    CACHE,
    LL,
    LWC1,
    LV_S,
    VMOV,
    VABS,
    VNEG,
    VIDT,
    VSAT0,
    VSAT1,
    VZERO,
    VONE,
    VRCP,
    VRSQ,
    VSIN,
    VCOS,
    VEXP2,
    VLOG2,
    VSQRT,
    VASIN,
    VNRCP,
    VNSIN,
    VREXP2,
    VRNDS,
    VRNDI,
    VRNDF1,
    VRNDF2,
    VF2H,
    VH2F,
    VSBZ,
    VLGB,
    VUC2I,
    VC2I,
    VUS2I,
    VS2I,
    VI2UC,
    VI2C,
    VI2US,
    VI2S,
    VSRT1,
    VSRT2,
    VBFY1,
    VBFY2,
    VOCP,
    VSOCP,
    VFAD,
    VAVG,
    VSRT3,
    VSRT4,
    VSGN,
    VMFVC,
    VMTVC,
    VT4444,
    VT5551,
    VT5650,
    VCST,
    VF2IN,
    VF2IZ,
    VF2IU,
    VF2ID,
    VF2F,
    VCMOV,
    VCMOVT,
    VCMOVF,
    VWBN,
    LV,
    LVL,
    LVR,
    LV_Q,
    VPFXS,
    VPFXT,
    VPFXD,
    VIIM,
    VFIM,
    SC,
    SWC1,
    SV_S,
    VMMUL,
    VHTFM2,
    VTFM2,
    VHTFM3,
    VTFM3,
    VHTFM4,
    VTFM4,
    VMSCL,
    VCRSP,
    VMMOV,
    VMIDT,
    VMZERO,
    VMONE,
    VROT,
    SV,
    SVL,
    SVR,
    SV_Q,
    VNOP,
    VSYNC,
    VFLUSH,

    _UNKNOWN,
    _MAX
};

// does not include VFPU vector size suffixes
const char *get_mnemonic_name(allegrex_mnemonic mne);

// TODO: VFPU vector size name
