
#pragma once

#include "shl/number_types.hpp"
#include "allegrex/parse_instructions.hpp"

typedef void(*argument_parse_function_t)(u32 opcode, instruction*, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_RdRsRt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_AdduOr(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// clz, clo
void arg_parse_RdRs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RsRt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// tge, tgeu etc
void arg_parse_RsRtCode(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RdRtShift(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VarShift(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// jr
void arg_parse_RegJumpRs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// jalr
void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Syscall(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Sync(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_Rs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Rd(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RdRt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_RsImmediateU(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RsImmediateS(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RtImmediateU(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RsBranchAddress(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Bgezal(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_JumpAddress(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_RsRtBranchAddress(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// B pseudoinstruction
void arg_parse_Beq(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// BL pseudoinstruction
void arg_parse_Beql(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_RtRsSignExtendedImmediateU(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RtRsImmediateU(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RtRsImmediateS(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
// LI pseudoinstruction
void arg_parse_Addi(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Ori(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata); // technically same as Addiu

// lb, lh, lw, etc...
void arg_parse_RsRtMemOffset(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_Cache(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// special3
void arg_parse_Ext(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_Ins(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// FPU
void arg_parse_FPUBranchAddress(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_RsFtMemOffset(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_FPUFdFsFt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_FPUFdFs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_FPUCompare(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_FPURtFs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// VFPU
void arg_parse_VFPU_Cop2(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_MFTV(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// 3op, e.g. vadd
void arg_parse_VFPU_Vd_Vs_Vt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_VdSingle_Vs_Vt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vd_Vs_VtSingle(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_Vcrs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vcmp(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// 2op, e.g. vmov
void arg_parse_VFPU_Vd_Vs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_VdSingle_Vs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vd_Vs_Imm5(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// 1op, e.g. vidt
void arg_parse_VFPU_Vd(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_VdSingle(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_VdHalf_Vs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_VdDouble_Vs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_Vmfvc(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vmtvc(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_ColorConv(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vwbn(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vcst(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vcmov(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_PrefixST(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_PrefixDest(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Viim(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vfim(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_LvSv_S(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_LvSv_Q(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_LvSv_LRQ(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// matrix functions
void arg_parse_VFPU_MVd(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_MVd_MVs(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

// may as well be called vmmul
void arg_parse_VFPU_MVd_XVs_MVt(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_Vhtfm2(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vhtfm3(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
void arg_parse_VFPU_Vhtfm4(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_MVd_MVs_VtSingle(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);

void arg_parse_VFPU_Vrot(u32 opcode, instruction *inst, const parse_instructions_config *conf, instruction_parse_data *pdata);
