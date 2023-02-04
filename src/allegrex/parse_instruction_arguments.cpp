
#include <assert.h>

#include "shl/bits.hpp"

#include "allegrex/parse_instruction_arguments.hpp"

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


constexpr s32 sign_extend_16_to_s32(u32 value)
{
	return static_cast<s16>(bitrange(value, 0, 15));
}

constexpr u32 sign_extend_16_to_u32(u32 value)
{
	return static_cast<u32>(sign_extend_16_to_s32(value));
}

constexpr immediate<s32> extend16_imms32(u32 val)
{
    return immediate<s32>{sign_extend_16_to_s32(val)};
}

constexpr immediate<u32> extend16_immu32(u32 val)
{
    return immediate<u32>{sign_extend_16_to_u32(val)};
}

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

void add_vfpu_matrix_argument(u32 mtx, vfpu_size size, instruction *inst)
{
    assert(mtx < 128);

    add_argument(vfpu_matrix{static_cast<u8>(mtx), size}, inst);
}

void add_vfpu_register_argument(u32 reg, u32 size, instruction *inst)
{
    if (size > value(vfpu_size::Invalid))
        size = value(vfpu_size::Invalid);

    add_vfpu_register_argument(reg, static_cast<vfpu_size>(size), inst);
}

void add_jump_address_argument(u32 addr, instruction *inst, parse_data *pdata)
{
    add_argument(jump_address{addr}, inst);
    pdata->jump_destinations->push_back(jump_destination{addr, jump_type::Jump});
}

void add_branch_address_argument(u32 addr, instruction *inst, parse_data *pdata)
{
    add_argument(branch_address{addr}, inst);
    pdata->jump_destinations->push_back(jump_destination{addr, jump_type::Branch});
}

// argument parse functions
void arg_parse_RdRsRt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

void arg_parse_AdduOr(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RdRsRt(opcode, inst, conf, pdata);
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

    arg_parse_RdRsRt(opcode, inst, conf, pdata);
};

// only used by clz & clo...
void arg_parse_RdRs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RsRt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

void arg_parse_RsRtCode(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 code = bitrange(opcode, 6, 15);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(extra{code}, inst);
};

void arg_parse_RdRtShift(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);
    u8 sa = SA(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_argument(shift{sa}, inst);
};

void arg_parse_VarShift(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    // almost the same as RsRtRd, except rt comes before rs
    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};


void arg_parse_Syscall(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 code = bitrange(opcode, 6, 25);
    u16 funcnum = bitrange(code, 0, 11);
	u16 modulenum = bitrange(code, 12, 19);

    const psp_function *sc = get_psp_function(modulenum, funcnum);

    add_argument(sc, inst);
    add_argument(extra{code}, inst);
};

void arg_parse_Sync(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 stype = bitrange(opcode, 6, 10);

    add_argument(extra{stype}, inst);
};

void arg_parse_Rs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_Rd(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
};

void arg_parse_RdRt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rd = RD(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
};

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rt = RT(opcode);
    u8 rd = RD(opcode);
    u8 sel = bitrange(opcode, 0, 2);

    add_register_argument(rt, inst);
    add_argument(coprocessor_register{rd, sel}, inst);
};

void arg_parse_RsImmediateU(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rs, inst);
    add_argument(immediate<u16>{imm}, inst);
};

void arg_parse_RsImmediateS(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rs, inst);
    add_argument(immediate<s16>{imm}, inst);
};

void arg_parse_RtImmediateU(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rt = RT(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_argument(immediate<u16>{imm}, inst);
};

void arg_parse_RsBranchAddress(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_register_argument(rs, inst);
    add_branch_address_argument(off, inst, pdata);
};

void arg_parse_Bgezal(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    // pseudoinstruction Bal
    if (!conf->emit_pseudo)
    {
        arg_parse_RsBranchAddress(opcode, inst, conf, pdata);
        return;
    }

    u32 rs = RS(opcode);
    
    if (rs > 0)
    {
        arg_parse_RsBranchAddress(opcode, inst, conf, pdata);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::BAL;
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    // we register this as jump, like mipsdisasm (sm64tools) does
    add_jump_address_argument(off, inst, pdata);
};

void arg_parse_JumpAddress(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 off = bitrange(opcode, 0, 25) << 2;
    u32 addr = inst->address & 0xf0000000;
    addr |= off;

    add_jump_address_argument(addr, inst, pdata);
}

void arg_parse_RsRtBranchAddress(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_branch_address_argument(off, inst, pdata);
}

void arg_parse_Beq(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtBranchAddress(opcode, inst, conf, pdata);
        return;
    }
    
    // pseudoinstruction B
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    if (rs != rt)
    {
        arg_parse_RsRtBranchAddress(opcode, inst, conf, pdata);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::B;
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_branch_address_argument(off, inst, pdata);
}

void arg_parse_Beql(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RsRtBranchAddress(opcode, inst, conf, pdata);
        return;
    }
    
    // pseudoinstruction BL
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    if (rs != rt)
    {
        arg_parse_RsRtBranchAddress(opcode, inst, conf, pdata);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::BL;
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_branch_address_argument(off, inst, pdata);
}

void arg_parse_RtRsSignExtendedImmediateU(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(extend16_immu32(imm), inst);
};

void arg_parse_RtRsImmediateU(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(immediate<u32>{imm}, inst);
};

void arg_parse_RtRsImmediateS(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(extend16_imms32(imm), inst);
};

void arg_parse_Addi(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RtRsImmediateS(opcode, inst, conf, pdata);
        return;
    }
    
    // pseudoinstruction LI
    u32 rs = RS(opcode);

    if (rs != 0)
    {
        arg_parse_RtRsImmediateS(opcode, inst, conf, pdata);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::LI;
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);
    add_register_argument(rt, inst);
    add_argument(extend16_imms32(imm), inst);
};

void arg_parse_Ori(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    if (!conf->emit_pseudo)
    {
        arg_parse_RtRsImmediateU(opcode, inst, conf, pdata);
        return;
    }
    
    // pseudoinstruction LI
    u32 rs = RS(opcode);

    if (rs != 0)
    {
        arg_parse_RtRsImmediateU(opcode, inst, conf, pdata);
        return;
    }

    inst->mnemonic = allegrex_mnemonic::LI;
    u32 rt = RT(opcode);
    u32 imm = bitrange(opcode, 0, 15);
    add_register_argument(rt, inst);
    add_argument(immediate<u32>{imm}, inst);
};

void arg_parse_RsRtMemOffset(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_register_argument(rt, inst);
    add_argument(memory_offset{imm}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
};

void arg_parse_Cache(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    s16 off = bitrange(opcode, 0, 15);
    u32 rs = RS(opcode);
    u32 func = bitrange(opcode, 16, 20);

    add_argument(immediate<u32>{func}, inst);
    add_argument(memory_offset{off}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
}

void arg_parse_Ext(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 pos = bitrange(opcode, 6, 10);
    u32 sz = bitrange(opcode, 11, 15);
    sz += 1;

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(bitfield_pos{pos}, inst);
    add_argument(bitfield_size{sz}, inst);
}

void arg_parse_Ins(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 pos = bitrange(opcode, 6, 10);
    u32 sz = bitrange(opcode, 11, 15);
    sz += 1;
    sz -= pos;

    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
    add_argument(bitfield_pos{pos}, inst);
    add_argument(bitfield_size{sz}, inst);
}

void arg_parse_FPUBranchAddress(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 16)) << 2;
    off += imm + sizeof(opcode);
    u8 cc = bitrange(opcode, 18, 20);

    add_branch_address_argument(off, inst, pdata);
    add_argument(condition_code{cc}, inst);
};

void arg_parse_RsFtMemOffset(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 ft = FT(opcode);
    s16 imm = bitrange(opcode, 0, 15);

    add_fpu_register_argument(ft, inst);
    add_argument(memory_offset{imm}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
};

void arg_parse_FPUFdFsFt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 ft = FT(opcode);
    u32 fs = FS(opcode);
    u32 fd = FD(opcode);
    // u32 fmt = bitrange(opcode, 21, 25); // unused

    add_fpu_register_argument(fd, inst);
    add_fpu_register_argument(fs, inst);
    add_fpu_register_argument(ft, inst);
}

void arg_parse_FPUFdFs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 fs = FS(opcode);
    u32 fd = FD(opcode);
    // u32 fmt = bitrange(opcode, 21, 25); // unused

    add_fpu_register_argument(fd, inst);
    add_fpu_register_argument(fs, inst);
}

void arg_parse_FPUCompare(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 ft = FT(opcode);
    u32 fs = FS(opcode);
    u32 cc = bitrange(opcode, 8, 10);

    add_fpu_register_argument(fs, inst);
    add_fpu_register_argument(ft, inst);
    add_argument(extra{cc}, inst);
}

void arg_parse_FPURtFs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rt = RT(opcode);
    u32 fs = FS(opcode);

    add_register_argument(rt, inst);
    add_fpu_register_argument(fs, inst);
}

// VFPU
void arg_parse_VFPU_Cop2(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rt = RT(opcode);
    u16 unk = bitrange(opcode, 0u, 15u);

    add_register_argument(rt, inst);
    add_argument(immediate<u16>{unk}, inst);
}

void arg_parse_VFPU_MFTV(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    // ppsspp
    u32 rt = RT(opcode);
    u32 vr = bitrange(opcode, 0, 7);

    add_register_argument(rt, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vd_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_VdSingle_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_Vd_Vs_VtSingle(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vcrs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    if (sz != vfpu_size::Triple)
        add_argument(invalid_argument{"vector size not triple"}, inst);
    else
    {
        add_vfpu_register_argument(vd, sz, inst);
        add_vfpu_register_argument(vs, sz, inst);
        add_vfpu_register_argument(vt, sz, inst);
    }
}

void arg_parse_VFPU_Vcmp(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);
    u32 cond = bitrange(opcode, 0, 3);

    add_argument(static_cast<vfpu_condition>(cond), inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, sz, inst);
}

void arg_parse_VFPU_Vd_Vs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_VdSingle_Vs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vd_Vs_Imm5(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u8 imm = bitrange(opcode, 16, 20);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_argument(immediate<u8>{imm}, inst);
}

void arg_parse_VFPU_Vd(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);

    add_vfpu_register_argument(vd, sz, inst);
}

void arg_parse_VFPU_VdSingle(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vd = VD(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
}

void arg_parse_VFPU_VdHalf_Vs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size hsz = half_size(sz);

    /*
    if (bitrange(opcode, 16, 17) == 0)
        hsz = vfpu_size::Single;
    */

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, hsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_VdDouble_Vs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size dsz = double_size(sz);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, dsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vmfvc(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vd = VD(opcode);
    u32 vr = VS(opcode) + 128;

    add_vfpu_register_argument(vd, vfpu_size::Single, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vmtvc(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vr = VD(opcode) + 128;
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vs, vfpu_size::Single, inst);
    add_vfpu_register_argument(vr, vfpu_size::Single, inst);
}

void arg_parse_VFPU_ColorConv(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    vfpu_size hsz = half_size(sz);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_register_argument(vd, hsz, inst);
    add_vfpu_register_argument(vs, sz, inst);
}

void arg_parse_VFPU_Vwbn(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u8 imm = bitrange(opcode, 16, 23);

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_argument(immediate<u8>{imm}, inst);
}

void arg_parse_VFPU_Vcst(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);

    u32 vd = VD(opcode);
    u32 constant = bitrange(opcode, 16, 20);

    add_vfpu_register_argument(vd, sz, inst);
    add_argument(static_cast<vfpu_constant>(constant), inst);
}

void arg_parse_VFPU_Vcmov(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);

    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    // u32 tf = bitrange(opcode, 19, 20);
    u8 imm = bitrange(opcode, 16, 18);

    if (imm > 6)
    {
        add_argument(invalid_argument{"invalid immediate"}, inst);
        return;
    }

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, sz, inst);
    add_argument(immediate<u8>{imm}, inst);
}

void arg_parse_VFPU_PrefixST(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 data = bitrange(opcode, 0, 19);
    vfpu_prefix_array arr;

    for (u32 i = 0; i < 4; ++i)
    {
        u32 regnum    = (data >> (i  * 2)) & 3;
        u32 abs	      = (data >> (8  + i)) & 1;
        u32 neg       = (data >> (16 + i)) & 1;
        u32 constants = (data >> (12 + i)) & 1;
        u32 pfx = 0;

        if (constants == 0)
            pfx = regnum + neg * 4 + abs * 8;
        else
            pfx = regnum + 16 + abs * 4;

        arr.data[i] = static_cast<vfpu_prefix>(pfx);
    }

    add_argument(arr, inst);
}

void arg_parse_VFPU_PrefixDest(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 data = bitrange(opcode, 0, 19);
    vfpu_destination_prefix_array arr;

    for (u32 i = 0; i < 4; ++i)
    {
        u32 sat  = (data >> (i * 2)) & 3;
        u32 mask = (data >> (8 + i)) & 1;
        u32 pfx = sat + mask * 4;

        arr.data[i] = static_cast<vfpu_destination_prefix>(pfx);
    }

    add_argument(arr, inst);
}

void arg_parse_VFPU_Viim(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vt = VT(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
    add_argument(immediate<u16>{imm}, inst);
}

float Float16ToFloat32(u16 l)
{
    // https://github.com/hrydgard/ppsspp/blob/748eef05d0c64b7aa5be6714fa52fa84a5977f05/Core/MIPS/MIPSVFPUUtils.cpp#L616
    union float2int {
        uint32_t i;
        float f;
    };

#define VFPU_FLOAT16_EXP_MAX    0x1f
#define VFPU_SH_FLOAT16_SIGN    15
#define VFPU_MASK_FLOAT16_SIGN  0x1
#define VFPU_SH_FLOAT16_EXP     10
#define VFPU_MASK_FLOAT16_EXP   0x1f
#define VFPU_SH_FLOAT16_FRAC    0
#define VFPU_MASK_FLOAT16_FRAC  0x3ff

	float2int f2i;

	unsigned short float16 = l;
	unsigned int sign = (float16 >> VFPU_SH_FLOAT16_SIGN) & VFPU_MASK_FLOAT16_SIGN;
	int exponent = (float16 >> VFPU_SH_FLOAT16_EXP) & VFPU_MASK_FLOAT16_EXP;
	unsigned int fraction = float16 & VFPU_MASK_FLOAT16_FRAC;

	float f;
	if (exponent == VFPU_FLOAT16_EXP_MAX)
	{
		f2i.i = sign << 31;
		f2i.i |= 255 << 23;
		f2i.i |= fraction;
		f = f2i.f;
	}
	else if (exponent == 0 && fraction == 0)
	{
		f = sign == 1 ? -0.0f : 0.0f;
	}
	else
	{
		if (exponent == 0)
		{
			do
			{
				fraction <<= 1;
				exponent--;
			}
			while (!(fraction & (VFPU_MASK_FLOAT16_FRAC + 1)));

			fraction &= VFPU_MASK_FLOAT16_FRAC;
		}

		/* Convert to 32-bit single-precision IEEE754. */
		f2i.i = sign << 31;
		f2i.i |= (exponent + 112) << 23;
		f2i.i |= fraction << 13;
		f=f2i.f;
	}

	return f;
}

void arg_parse_VFPU_Vfim(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vt = VT(opcode);
    u16 imm = bitrange(opcode, 0, 15);

    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
    add_argument(immediate<float>{Float16ToFloat32(imm)}, inst);
}

void arg_parse_VFPU_LvSv_S(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 vt = bitrange(opcode, 16, 20) | (bitrange(opcode, 0, 1) << 5);
    s16 offset = bitrange(opcode, 2, 15) << 2;

    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
    add_argument(memory_offset{offset}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
}

void arg_parse_VFPU_LvSv_Q(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 vt = bitrange(opcode, 16, 20) | (bitrange(opcode, 0, 0) << 5);
    s16 offset = bitrange(opcode, 2, 15) << 2;

    add_vfpu_register_argument(vt, vfpu_size::Quad, inst);
    add_argument(memory_offset{offset}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);

    if (bitrange(opcode, 1, 1))
        add_argument(string_arg{"wb"}, inst); // ??
}

void arg_parse_VFPU_LvSv_LRQ(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 rs = RS(opcode);
    u32 vt = bitrange(opcode, 16, 20) | (bitrange(opcode, 0, 0) << 5);
    s16 offset = bitrange(opcode, 2, 15) << 2;

    add_vfpu_register_argument(vt, vfpu_size::Quad, inst);
    add_argument(memory_offset{offset}, inst);
    add_argument(base_register{static_cast<mips_register>(rs)}, inst);
}

void arg_parse_VFPU_MVd(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);

    add_vfpu_matrix_argument(vd, sz, inst);
}

void arg_parse_VFPU_MVd_MVs(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);

    add_vfpu_matrix_argument(vd, sz, inst);
    add_vfpu_matrix_argument(vs, sz, inst);
}

void arg_parse_VFPU_MVd_XVs_MVt(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    // https://github.com/hrydgard/ppsspp/blob/6f04f52f5ca51b60c719e074199691b2ccf32860/Core/MIPS/MIPSDisVFPU.cpp#L291
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode) ^ 0x20; // Xpose??
    u32 vt = VT(opcode);

    add_vfpu_matrix_argument(vd, sz, inst);
    add_vfpu_matrix_argument(vs, sz, inst);
    add_vfpu_matrix_argument(vt, sz, inst);
}

void arg_parse_VFPU_Vhtfm2(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Pair, inst);
    add_vfpu_matrix_argument(vs,   vfpu_size::Pair, inst);
    add_vfpu_register_argument(vt, vfpu_size::Pair, inst);
}

void arg_parse_VFPU_Vhtfm3(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Triple, inst);
    add_vfpu_matrix_argument(vs,   vfpu_size::Triple, inst);
    add_vfpu_register_argument(vt, vfpu_size::Triple, inst);
}

void arg_parse_VFPU_Vhtfm4(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_register_argument(vd, vfpu_size::Quad, inst);
    add_vfpu_matrix_argument(vs,   vfpu_size::Quad, inst);
    add_vfpu_register_argument(vt, vfpu_size::Quad, inst);
}

void arg_parse_VFPU_MVd_MVs_VtSingle(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 vt = VT(opcode);

    add_vfpu_matrix_argument(vd, sz, inst);
    add_vfpu_matrix_argument(vs, sz, inst);
    add_vfpu_register_argument(vt, vfpu_size::Single, inst);
}

void arg_parse_VFPU_Vrot(u32 opcode, instruction *inst, const parse_config *conf, parse_data *pdata)
{
    vfpu_size sz = get_vfpu_size(opcode);
    u32 vd = VD(opcode);
    u32 vs = VS(opcode);
    u32 imm = bitrange(opcode, 16, 20);

    u32 sin = bitrange(imm, 2, 3);
    u32 cos = bitrange(imm, 0, 1);
    u32 negsin = bitrange(imm, 4, 4);

    vfpu_rotation_array arr{{vfpu_rotation::ZERO}};
    arr.size = value(sz) + 1;

    if (sin == cos)
        for (u32 i = 0; i < arr.size; ++i)
            arr.data[i] = vfpu_rotation::SIN;

    arr.data[sin] = vfpu_rotation::SIN;
    arr.data[cos] = vfpu_rotation::COS;

    if (negsin)
        for (u32 i = 0; i < arr.size; ++i)
            if (arr.data[i] == vfpu_rotation::SIN)
                arr.data[i] = vfpu_rotation::NEG_SIN;

    add_vfpu_register_argument(vd, sz, inst);
    add_vfpu_register_argument(vs, vfpu_size::Single, inst);
    add_argument(arr, inst);
}
