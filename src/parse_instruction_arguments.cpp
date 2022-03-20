
#include <assert.h>

#include "parse_instruction_arguments.hpp"

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

// argument parse functions
// R-type instruction: xxxxxx ..... ..... ..... ..... xxxxxx
// 3: first 3 (from left to right) sets of 5 bits are parameters
// the last one is shift (unused for most instructions)
void arg_parse_R3(u32 opcode, instruction *inst, const parse_config *conf)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    // destination comes first
    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

// only used by clz & clo...
void arg_parse_R2(u32 opcode, instruction *inst, const parse_config *conf)
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

    // almost the same as R3, except rt comes before rs
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

    /*
     * TODO: implement
    inst->name = "b";
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 15)) << 2;
    off += imm + sizeof(opcode);

    add_argument(address{off}, inst);
    */
}

void arg_parse_Beql(u32 opcode, instruction *inst, const parse_config *conf)
{
    // TODO: pseudoinstruction BL
    /*
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    if (rs == rt)
        ...
    */

    arg_parse_RsRtRelAddress(opcode, inst, conf);
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
    // TODO: pseudoinstruction LI
    /*
    u32 rs = RS(opcode);

    if (rs == 0)
        ...
    */

    arg_parse_RsRtImmediateS(opcode, inst, conf);
};

void arg_parse_Addiu(u32 opcode, instruction *inst, const parse_config *conf)
{
    // TODO: pseudoinstruction LI
    /*
    u32 rs = RS(opcode);

    if (rs == 0)
        ...
    */

    arg_parse_RsRtImmediateU(opcode, inst, conf);
};

void arg_parse_Ori(u32 opcode, instruction *inst, const parse_config *conf)
{
    // TODO: pseudoinstruction LI
    /*
    u32 rs = RS(opcode);

    if (rs == 0)
        ...
    */

    arg_parse_RsRtImmediateU(opcode, inst, conf);
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
    auto cc = bitrange(opcode, 18, 20); // can probably omit this

    add_argument(address{off}, inst);
    add_argument(extra{cc}, inst);
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
