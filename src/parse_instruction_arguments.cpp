
#include <assert.h>

#include "parse_instruction_arguments.hpp"

// TODO: write tests for all instruction parsings...

#define RS(opcode) bitrange(opcode, 21u, 25u)
#define RT(opcode) bitrange(opcode, 16u, 20u)
#define RD(opcode) bitrange(opcode, 11u, 15u)
#define SA(opcode) bitrange(opcode, 6u, 10u)

#define FT(opcode) bitrange(opcode, 16u, 20u)
#define FS(opcode) bitrange(opcode, 11u, 15u)
#define FD(opcode) bitrange(opcode, 6u, 10u)

#define VD(opcode) bitrange(opcode, 0u, 6u)
#define VS(opcode) bitrange(opcode, 8u, 14u)
#define VT(opcode) bitrange(opcode, 16u, 22u)

static_assert(bitrange(0x00ff, 0, 0) == 0x1);
static_assert(bitrange(0x00ff, 0, 1) == 0x3);
static_assert(bitrange(0x00ff, 0, 3) == 0xf);
static_assert(bitrange(0x00ff, 0, 7) == 0xff);
static_assert(bitrange(0x01ff, 0, 7) == 0xff);
static_assert(bitrange(0x00ff, 0, 8) == 0xff);
static_assert(bitrange(0x01ff, 1, 8) == 0xff);
static_assert(bitrange(0x0ff0, 4, 11) == 0xff);
static_assert(bitrange(0xff00, 8, 15) == 0xff);

template<typename T>
void add_argument(T val, instruction *inst)
{
    inst->arguments.push_back(val);
}

void add_register_argument(u32 reg, instruction *inst)
{
    assert(reg < 32);

    add_argument(static_cast<mips_register>(reg), inst);
}

void add_fpu_register_argument(u32 reg, instruction *inst)
{
    assert(reg < 32);

    add_argument(static_cast<mips_fpu_register>(reg), inst);
}

void add_vfpu_register_argument(u32 reg, vfpu_size size, instruction *inst)
{
    assert(reg < 256);

    add_argument(vfpu_register{static_cast<u8>(reg), size}, inst);
}

void add_vfpu_register_argument(u32 reg, u32 size, instruction *inst)
{
    if (size > static_cast<u32>(vfpu_size::Invalid))
        size = static_cast<u32>(vfpu_size::Invalid);

    add_vfpu_register_argument(reg, static_cast<vfpu_size>(size), inst);
}

// argument parse functions
// R-type instruction: xxxxxx ..... ..... ..... ..... xxxxxx
// 3: first 3 (from left to right) sets of 5 bits are parameters
// the last one is shift (unused for most instructions)
void arg_parse_RsRtRd(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

void arg_parse_AdduOr(u32 opcode, instruction *inst, const parse_config *conf)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtRd(opcode, inst, conf);
        return;
    }

    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    if (rs == 0 && rt == 0)
    {
        inst->mnemonic = allegrex_mnemonic::LI;
        add_register_argument(rd, inst);
        add_argument(immediate<s16>{0}, inst);
        return;
    }
    else if (rs == 0)
    {
        inst->mnemonic = allegrex_mnemonic::MOVE;
        add_register_argument(rd, inst);
        add_register_argument(rt, inst);
        return;
    }
    else if (rt == 0)
    {
        inst->mnemonic = allegrex_mnemonic::MOVE;
        add_register_argument(rd, inst);
        add_register_argument(rs, inst);
        return;
    }

    arg_parse_RsRtRd(opcode, inst, conf);
};

// only used by clz & clo...
void arg_parse_RsRd(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RsRt(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

void arg_parse_RsRtCode(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 code = bitrange(opcode, 6, 15);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(extra{code}, inst);
};

void arg_parse_RdRtShift(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);
    u8 sa = SA(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_argument(shift{sa}, inst);
};

void arg_parse_VarShift(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    // almost the same as RsRtRd, except rt comes before rs
    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRs(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};


void arg_parse_Syscall(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 code = bitrange(opcode, 6, 25);
    u16 funcnum = bitrange(code, 0, 11);
	u16 modulenum = bitrange(code, 12, 19);

    const syscall *sc = get_syscall(modulenum, funcnum);

    add_argument(sc, inst);
    add_argument(extra{code}, inst);
};

void arg_parse_Sync(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 stype = bitrange(opcode, 6, 10);

    add_argument(extra{stype}, inst);
};

void arg_parse_Rs(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_Rd(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
};

void arg_parse_RdRt(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rd = RD(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
};

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rt = RT(opcode);
    u8 rd = RD(opcode);
    u8 sel = bitrange(opcode, 0, 2);

    add_register_argument(rt, inst);
    add_argument(coprocessor_register{rd, sel}, inst);
};

void arg_parse_RsImmediateU(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rs, inst);
    add_argument(immediate<u16>{imm}, inst);
};

void arg_parse_RsImmediateS(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rs, inst);
    add_argument(immediate<s16>{imm}, inst);
};

void arg_parse_RtImmediateU(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rt = RT(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_argument(immediate<u16>{imm}, inst);
};

void arg_parse_RsRelAddress(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_register_argument(rs, inst);
    add_argument(address{off}, inst);
};

void arg_parse_JumpAddress(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 off = bitrange(opcode, 0, 25) << 2;
    u32 addr = bitrange(inst->address, 28, 31) | off;

    add_argument(address{addr}, inst);
};

void arg_parse_RsRtRelAddress(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(address{off}, inst);
}

void arg_parse_Beq(u32 opcode, instruction *inst, const parse_config *conf)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtRelAddress(opcode, inst, conf);
        return;
    }
    
    // pseudoinstruction B
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    if (rs != rt)
    {
        arg_parse_RsRtRelAddress(opcode, inst, conf);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::B;
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_argument(address{off}, inst);
}

void arg_parse_Beql(u32 opcode, instruction *inst, const parse_config *conf)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtRelAddress(opcode, inst, conf);
        return;
    }
    
    // pseudoinstruction BL
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    if (rs != rt)
    {
        arg_parse_RsRtRelAddress(opcode, inst, conf);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::BL;
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_argument(address{off}, inst);
}

void arg_parse_RsRtImmediateU(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(immediate<u16>{imm}, inst);
};

void arg_parse_RsRtImmediateS(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(immediate<s16>{imm}, inst);
};

void arg_parse_Addi(u32 opcode, instruction *inst, const parse_config *conf)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtImmediateS(opcode, inst, conf);
        return;
    }
    
    // pseudoinstruction LI
    u32 rs = RS(opcode);

    if (rs != 0)
    {
        arg_parse_RsRtImmediateS(opcode, inst, conf);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::LI;
    u32 rt = RT(opcode);
    s16 imm = bitrange(opcode, 0, 15);
    add_register_argument(rt, inst);
    add_argument(immediate<s16>{imm}, inst);
};

void arg_parse_Ori(u32 opcode, instruction *inst, const parse_config *conf)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtImmediateU(opcode, inst, conf);
        return;
    }
    
    // pseudoinstruction LI
    u32 rs = RS(opcode);

    if (rs != 0)
    {
        arg_parse_RsRtImmediateU(opcode, inst, conf);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::LI;
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);
    add_register_argument(rt, inst);
    add_argument(immediate<u32>{imm}, inst);
};

void arg_parse_RsRtMemOffset(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_argument(memory_offset{imm}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
};

void arg_parse_Cache(u32 opcode, instruction *inst, const parse_config *conf)
{
    s16 off = bitrange(opcode, 0, 15);
    u32 rs = RS(opcode);
    u32 func = bitrange(opcode, 16, 20);

    add_argument(immediate<u32>{func}, inst);
    add_argument(memory_offset{off}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
}

void arg_parse_Ext(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 pos = bitrange(opcode, 6, 10);
    u32 sz = bitrange(opcode, 11, 15);
    sz += 1;

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(bitfield_pos{pos}, inst);
    add_argument(bitfield_size{sz}, inst);
}

void arg_parse_Ins(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 pos = bitrange(opcode, 6, 10);
    u32 sz = bitrange(opcode, 11, 15);
    sz += 1;
    sz -= pos;

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(bitfield_pos{pos}, inst);
    add_argument(bitfield_size{sz}, inst);
}

void arg_parse_FPURelAddress(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 16)) << 2;
    off += imm + sizeof(opcode);
    u8 cc = bitrange(opcode, 18, 20);

    add_argument(address{off}, inst);
    add_argument(condition_code{cc}, inst);
};

void arg_parse_RsFtMemOffset(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 ft = FT(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_fpu_register_argument(ft, inst);
    add_argument(memory_offset{imm}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
};

void arg_parse_FPUFtFsFd(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 ft = FT(opcode);
    u32 fs = FS(opcode);
    u32 fd = FD(opcode);
    // u32 fmt = bitrange(opcode, 21, 25); // unused

    add_fpu_register_argument(fd, inst);
    add_fpu_register_argument(fs, inst);
    add_fpu_register_argument(ft, inst);
}

void arg_parse_FPUFsFd(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 fs = FS(opcode);
    u32 fd = FD(opcode);
    // u32 fmt = bitrange(opcode, 21, 25); // unused

    add_fpu_register_argument(fd, inst);
    add_fpu_register_argument(fs, inst);
}

void arg_parse_FPUCompare(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 ft = FT(opcode);
    u32 fs = FS(opcode);
    u32 cc = bitrange(opcode, 8, 10);

    add_fpu_register_argument(fs, inst);
    add_fpu_register_argument(ft, inst);
    add_argument(extra{cc}, inst);
}

void arg_parse_FPURtFs(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rt = RT(opcode);
    u32 fs = FS(opcode);

    add_register_argument(rt, inst);
    add_fpu_register_argument(fs, inst);
}

// VFPU
void arg_parse_VFPU_Cop2(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rt = RT(opcode);
    u16 unk = bitrange(opcode, 0u, 15u);

    add_register_argument(rt, inst);
    add_argument(immediate<u16>{unk}, inst);
}

void arg_parse_VFPU_MFTV(u32 opcode, instruction *inst, const parse_config *conf)
{
    // ppsspp
    u32 rt = RT(opcode);
    u32 vr = bitrange(opcode, 0, 7);

    add_register_argument(rt, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vd_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_VdSingle_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_Vd_Vs_VtSingle(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vcrs(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    if (sz != vfpu_size::Triple)
        add_argument(error{"vector size not triple"}, inst);
    else
    {
        add_vfpu_register_argument(vd, sz, inst);
        add_vfpu_register_argument(vs, sz, inst);
        add_vfpu_register_argument(vt, sz, inst);
    }
}

void arg_parse_VFPU_Vcmp(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);
    u32 cond = bitrange(opcode, 0, 3);

    add_argument(static_cast<vfpu_condition>(cond), inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_Vd_Vs(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_VdSingle_Vs(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vd_Vs_Imm5(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u8 imm = bitrange(opcode, 16, 20);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_argument(immediate<u8>{imm}, inst);
}

void arg_parse_VFPU_Vd(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);

    add_vfpu_register_argument(vd, sz, inst);
}

void arg_parse_VFPU_VdSingle(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 vd = VD(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
}

void arg_parse_VFPU_VdHalf_Vs(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size hsz = half_size(sz);

    if (bitrange(opcode, 16, 17) == 0)
        hsz = vfpu_size::Single;

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, hsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_VdDouble_Vs(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size dsz = double_size(sz);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, dsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vmfvc(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 vd = VD(opcode);
    u32 vr = VS(opcode) + 128;

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vmtvc(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 vr = VD(opcode) + 128;
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vs, vfpu_size::Single, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_ColorConv(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size hsz = half_size(sz);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, hsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vwbn(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u8 imm = bitrange(opcode, 16, 23);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_argument(immediate<u8>{imm}, inst);
}

void arg_parse_VFPU_Vcst(u32 opcode, instruction *inst, const parse_config *conf)
{
    vfpu_size sz = get_vfpu_size(opcode);

    u32 vd = VD(opcode);
    u32 constant = bitrange(opcode, 16, 20);

    add_vfpu_register_argument(vd, sz, inst);
    add_argument(vfpu_constant{constant}, inst);
}

