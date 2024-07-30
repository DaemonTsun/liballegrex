
#include "allegrex/allegrex_mnemonics.hpp"

static const char *_mnemonic_names[] = {
    "nop",
    "sll",
    "srl",
    "sra",
    "sllv",
    "srlv",
    "srav",
    "jr",
    "jalr",
    "movz",
    "movn",
    "syscall",
    "break",
    "sync",
    "mfhi",
    "mthi",
    "mflo",
    "mtlo",
    "clz",
    "clo",
    "mult",
    "multu",
    "div",
    "divu",
    "madd",
    "maddu",
    "add",
    "move",
    "addu",
    "sub",
    "subu",
    "and",
    "or",
    "xor",
    "nor",
    "slt",
    "sltu",
    "max",
    "min",
    "msub",
    "msubu",
    "tge",
    "tgeu",
    "tlt",
    "tltu",
    "teq",
    "tne",
    "rotrv",
    "rotr",
    "bltz",
    "bgez",
    "bltzl",
    "bgezl",
    "tgei",
    "tgeiu",
    "tlti",
    "tltiu",
    "teqi",
    "tnei",
    "bltzal",
    "bgezal",
    "bal",
    "bltzall",
    "bgezall",
    "synci",
    "j",
    "jal",
    "b",
    "beq",
    "bne",
    "blez",
    "bgtz",
    "li",
    "addi",
    "addiu",
    "slti",
    "sltiu",
    "andi",
    "ori",
    "xori",
    "lui",
    "mfc0",
    "mtc0",
    "rdpgpr",
    "mfmc0",
    "wrpgpr",
    "tlbr",
    "tlbwi",
    "tlbwr",
    "tlbp",
    "eret",
    "iack",
    "deret",
    "wait",
    "mfc1",
    "cfc1",
    "mtc1",
    "ctc1",
    "bc1f",
    "bc1t",
    "bc1fl",
    "bc1tl",
    "add.s",
    "sub.s",
    "mul.s",
    "div.s",
    "sqrt.s",
    "abs.s",
    "mov.s",
    "neg.s",
    "round.w.s",
    "trunc.w.s",
    "ceil.w.s",
    "floor.w.s",
    "cvt.s.w",
    "dis.int",
    "c.f.s",
    "c.un.s",
    "c.eq.s",
    "c.ueq.s",
    "c.olt.s",
    "c.ult.s",
    "c.ole.s",
    "c.ule.s",
    "c.sf.s",
    "c.ngle.s",
    "c.seq.s",
    "c.ngl.s",
    "c.lt.s",
    "c.nge.s",
    "c.le.s",
    "c.ngt.s",
    "cvt.s.w",
    "mfc2",
    "cfc2",
    "mfv",
    "mtc2",
    "ctc2",
    "mtv",
    "bvf",
    "bvt",
    "bvfl",
    "bvtl",
    "bl",
    "beql",
    "bnel",
    "blezl",
    "bgtzl",
    "vadd",
    "vsub",
    "vsbn",
    "vdiv",
    "vmul",
    "vdot",
    "vscl",
    "vhdp",
    "vcrs",
    "vdet",
    "vcmp",
    "vmin",
    "vmax",
    "vscmp",
    "vsge",
    "vslt",
    "halt",
    "mfic",
    "mtic",
    "ext",
    "ins",
    "rdhwr",
    "wsbh",
    "wsbw",
    "seb",
    "bitrev",
    "seh",
    "lb",
    "lh",
    "lwl",
    "lw",
    "lbu",
    "lhu",
    "lwr",
    "sb",
    "sh",
    "swl",
    "sw",
    "swr",
    "cache",
    "ll",
    "lwc1",
    "lv.s",
    "vmov",
    "vabs",
    "vneg",
    "vidt",
    "vsat0",
    "vsat1",
    "vzero",
    "vone",
    "vrcp",
    "vrsq",
    "vsin",
    "vcos",
    "vexp2",
    "vlog2",
    "vsqrt",
    "vasin",
    "vnrcp",
    "vnsin",
    "vrexp2",
    "vrnds",
    "vrndi",
    "vrndf1",
    "vrndf2",
    "vf2h",
    "vh2f",
    "vsbz",
    "vlgb",
    "vuc2i",
    "vc2i",
    "vus2i",
    "vs2i",
    "vi2uc",
    "vi2c",
    "vi2us",
    "vi2s",
    "vsrt1",
    "vsrt2",
    "vbfy1",
    "vbfy2",
    "vocp",
    "vsocp",
    "vfad",
    "vavg",
    "vsrt3",
    "vsrt4",
    "vsgn",
    "vmfvc",
    "vmtvc",
    "vt4444",
    "vt5551",
    "vt5650",
    "vcst",
    "vf2in",
    "vf2iz",
    "vf2iu",
    "vf2id",
    "vi2f",
    "vcmovt",
    "vcmovf",
    "vwbn",
    "lvl.q",
    "lvr.q",
    "lv.q",
    "vpfxs",
    "vpfxt",
    "vpfxd",
    "viim.s",
    "vfim.s",
    "sc",
    "swc1",
    "sv.s",
    "vmmul",
    "vhtfm2.p",
    "vtfm2.p",
    "vhtfm3.t",
    "vtfm3.t",
    "vhtfm4.q",
    "vtfm4.q",
    "vmscl",
    "vcrsp.t",
    "vqmul.q",
    "vmmov",
    "vmidt",
    "vmzero",
    "vmone",
    "vrot",
    "svl.q",
    "svr.q",
    "sv.q",
    "vnop",
    "vsync",
    "vflush",

    "[unknown]"
};

const char *get_mnemonic_name(allegrex_mnemonic mne)
{
    auto i = value(mne);

    if (i >= value(allegrex_mnemonic::_MAX))
        i = value(allegrex_mnemonic::_UNKNOWN);

    return _mnemonic_names[i];
}

bool requires_vfpu_suffix(allegrex_mnemonic mne)
{
    /*
    vadd
    vsub
    vsbn
    vdiv
    vmul
    vdot
    vscl
    vhdp
    vcrs
    vdet
    vcmp
    vmin
    vmax
    vscmp
    vsge
    vslt

    vmov
    vabs
    vneg
    vidt
    vsat0
    vsat1
    vzero
    vone
    vrcp
    vrsq
    vsin
    vcos
    vexp2
    vlog2
    vsqrt
    vasin
    vnrcp
    vnsin
    vrexp2
    vf2h
    vh2f
    vsbz
    vlgb
    vuc2i
    vc2i
    vus2i
    vs2i
    vi2uc
    vi2c
    vi2us
    vi2s
    vsrt1
    vsrt2
    vbfy1
    vbfy2
    vocp
    vsocp
    vfad
    vavg
    vsrt3
    vsrt4
    vsgn

    vt4444
    vt5551
    vt5650
    vcst
    vf2in
    vf2iz
    vf2iu
    vf2id
    vi2f

    vcmovt
    vcmovf
    vwbn
    
    vmmul
    
    vmscl
    
    vmmov
    vmidt
    vmzero
    vmone
    vrot
    */

#define between(x, MNEM1, MNEM2) \
    (x >= value(allegrex_mnemonic::MNEM1) && x <= value(allegrex_mnemonic::MNEM2))

    auto x = value(mne);

    if (x < value(allegrex_mnemonic::VADD))
        return false;

    if (x > value(allegrex_mnemonic::VROT))
        return false;

    if (between(x, VADD, VSLT))
        return true;

    if (between(x, VMOV, VSGN))
        return true;

    if (between(x, VT4444, VI2F))
        return true;

    if (between(x, VCMOVT, VWBN))
        return true;

    if (x == value(allegrex_mnemonic::VMMUL))
        return true;

    if (x == value(allegrex_mnemonic::VMSCL))
        return true;

    if (between(x, VMMOV, VROT))
        return true;

    return false;
}
