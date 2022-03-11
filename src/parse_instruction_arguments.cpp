
#include <stdexcept>

#include "parse_instruction_arguments.hpp"

template<typename T>
void add_argument(T val, instruction *inst)
{
    inst->arguments.push_back(val);
}

void add_register_argument(u32 reg, instruction *inst)
{
    if (reg > 31)
        throw std::runtime_error(str("unknown normal register ", reg));

    add_argument(static_cast<mips_register>(reg), inst);
}

// argument parse functions
// R-type instruction: xxxxxx ..... ..... ..... ..... xxxxxx
// 3: first 3 (from left to right) sets of 5 bits are parameters
// the last one is shift (unused for most instructions)
void arg_parse_R3(u32 opcode, instruction *inst)
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
void arg_parse_R2(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RsRt(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
};

void arg_parse_RsRtCode(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 code = bitrange(opcode, 6, 15);

    add_register_argument(rs, inst);
    add_register_argument(rt, inst);
    add_argument(extra{code}, inst);
};

void arg_parse_RdRtShift(u32 opcode, instruction *inst)
{
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);
    u8 sa = SA(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_argument(shift{sa}, inst);
};

void arg_parse_VarShift(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 rt = RT(opcode);
    u32 rd = RD(opcode);

    // almost the same as R3, except rt comes before rs
    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRs(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rs, inst);
};

void arg_parse_Syscall(u32 opcode, instruction *inst)
{
    u32 code = bitrange(opcode, 6, 25);
    int funcnum = code & 0xFFF;
	int modulenum = (code & 0xFF000) >> 12;
    // TODO: get function name
    // https://github.com/hrydgard/ppsspp/blob/c1a41bef72cb824eaa10e17790029866c4ed68da/Core/HLE/HLE.cpp

    add_argument(extra{code}, inst);
};

void arg_parse_Sync(u32 opcode, instruction *inst)
{
    u32 stype = bitrange(opcode, 6, 10);

    add_argument(extra{stype}, inst);
};

void arg_parse_Rs(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);

    add_register_argument(rs, inst);
};

void arg_parse_Rd(u32 opcode, instruction *inst)
{
    u32 rd = RD(opcode);

    add_register_argument(rd, inst);
};

void arg_parse_RdRt(u32 opcode, instruction *inst)
{
    u32 rd = RD(opcode);
    u32 rt = RT(opcode);

    add_register_argument(rd, inst);
    add_register_argument(rt, inst);
};

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst)
{
    u32 rt = RT(opcode);
    u8 rd = RD(opcode);
    u8 sel = bitrange(opcode, 0, 2);

    add_register_argument(rt, inst);
    add_argument(coprocessor_register{rd, sel}, inst);
};

void arg_parse_RsImmediate(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u16 imm = bitrange(opcode, 0, 16);

    add_register_argument(rs, inst);
    add_argument(immediate{imm}, inst);
};

void arg_parse_RsRelAddress(u32 opcode, instruction *inst)
{
    u32 rs = RS(opcode);
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 16)) << 2;
    off += imm + sizeof(opcode);

    add_register_argument(rs, inst);
    add_argument(address{off}, inst);
};

void arg_parse_FPURelAddress(u32 opcode, instruction *inst)
{
    u32 off = inst->address;
    s16 imm = (s16)(bitrange(opcode, 0, 16)) << 2;
    off += imm + sizeof(opcode);
    auto cc = bitrange(opcode, 18, 20); // can probably omit this

    add_argument(address{off}, inst);
    add_argument(extra{cc}, inst);
};

void arg_parse_Ext(u32 opcode, instruction *inst)
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

void arg_parse_Ins(u32 opcode, instruction *inst)
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
