
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// sll rd, rt, sa
define_test(sll_0)
{
    setup_test_variables();

    // 0 is NOP!
    parse_opcode(0x00000000);
    assert_mnemonic(NOP);
    assert_argument_count(0);
}

define_test(sll_1)
{
    setup_test_variables();

    parse_opcode(0x00000840);

    assert_mnemonic(SLL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, shift);
    assert_argument_shift(2, 1u);
}

define_test(sll_2)
{
    setup_test_variables();

    parse_opcode(0x001fffc0);

    assert_mnemonic(SLL);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::RA);
    assert_argument_mips_register(1, mips_register::RA);
    assert_argument_shift(2, 31u);
}

// sra rd, rt, sa
define_test(sra_0)
{
    setup_test_variables();

    parse_opcode(0x00000003);

    assert_mnemonic(SRA);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, shift);
    assert_argument_shift(2, 0u);
}

define_test(sra_1)
{
    setup_test_variables();

    parse_opcode(0x000008C3);

    assert_mnemonic(SRA);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::ZERO);
    assert_argument_shift(2, 3u);
}

define_test(sra_2)
{
    setup_test_variables();

    parse_opcode(0x001fffc3);

    assert_mnemonic(SRA);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::RA);
    assert_argument_mips_register(1, mips_register::RA);
    assert_argument_shift(2, 31u);
}

// sllv rd, rt, rs
define_test(sllv_0)
{
    setup_test_variables();

    parse_opcode(0x00000004);

    assert_mnemonic(SLLV);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(sllv_1)
{
    setup_test_variables();

    parse_opcode(0x00e30804);

    assert_mnemonic(SLLV);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::V1);
    assert_argument_mips_register(2, mips_register::A3);
}

define_test(sllv_2)
{
    setup_test_variables();

    parse_opcode(0x03fff804);

    assert_mnemonic(SLLV);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::RA);
    assert_argument_mips_register(1, mips_register::RA);
    assert_argument_mips_register(2, mips_register::RA);
}

// srav rd, rt, rs
define_test(srav_0)
{
    setup_test_variables();

    parse_opcode(0x00000007);

    assert_mnemonic(SRAV);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(srav_1)
{
    setup_test_variables();

    parse_opcode(0x00e30807);

    assert_mnemonic(SRAV);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::V1);
    assert_argument_mips_register(2, mips_register::A3);
}

define_test(srav_2)
{
    setup_test_variables();

    parse_opcode(0x03fff807);

    assert_mnemonic(SRAV);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::RA);
    assert_argument_mips_register(1, mips_register::RA);
    assert_argument_mips_register(2, mips_register::RA);
}

// jr rs
define_test(jr_0)
{
    setup_test_variables();

    parse_opcode(0x00000008);

    assert_mnemonic(JR);
    assert_argument_count(1);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);
}

define_test(jr_1)
{
    setup_test_variables();

    parse_opcode(0x00200008);

    assert_mnemonic(JR);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::AT);
}

define_test(jr_2)
{
    setup_test_variables();

    parse_opcode(0x03e00008);

    assert_mnemonic(JR);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::RA);
}

// jalr rd, rs
define_test(jalr_0)
{
    setup_test_variables();

    parse_opcode(0x00000009);

    assert_mnemonic(JALR);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(jalr_1)
{
    setup_test_variables();

    parse_opcode(0x00600809);

    assert_mnemonic(JALR);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

// movz rd, rs, rt
define_test(movz_0)
{
    setup_test_variables();

    parse_opcode(0x0000000a);

    assert_mnemonic(MOVZ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(movz_1)
{
    setup_test_variables();

    parse_opcode(0x00e3080a);

    assert_mnemonic(MOVZ);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// movn rd, rs, rt
define_test(movn_0)
{
    setup_test_variables();

    parse_opcode(0x0000000b);

    assert_mnemonic(MOVN);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(movn_1)
{
    setup_test_variables();

    parse_opcode(0x00e3080b);

    assert_mnemonic(MOVN);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// syscall Syscall
// this is pretty hard to test.
// probably need more real data to test against.
define_test(syscall)
{
    setup_test_variables();

    parse_opcode(0x0000000c);

    assert_mnemonic(SYSCALL);
    assert_argument_non_extra_count(1);

    assert_argument_type(0, const syscall*);
    _assert_argument_equals(0, const syscall*, get_syscall(0, 0));

    /*
    assert_argument_type(1, extra);
    _assert_argument_data_equals(1, extra, 0);
    */
}

// break
define_test(break)
{
    setup_test_variables();

    parse_opcode(0x0000000d);

    assert_mnemonic(BREAK);
    assert_argument_count(0);
}

// sync (stype)
define_test(sync)
{
    setup_test_variables();

    parse_opcode(0x0000000f);

    assert_mnemonic(SYNC);
    assert_argument_count(1);

    assert_argument_type(0, extra);
    _assert_argument_data_equals(0, extra, 0);
}

// mfhi rd
define_test(mfhi_0)
{
    setup_test_variables();

    parse_opcode(0x00000010);

    assert_mnemonic(MFHI);
    assert_argument_count(1);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);
}

define_test(mfhi_1)
{
    setup_test_variables();

    parse_opcode(0x00000810);

    assert_mnemonic(MFHI);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::AT);
}

// mthi rs
define_test(mthi_0)
{
    setup_test_variables();

    parse_opcode(0x00000011);

    assert_mnemonic(MTHI);
    assert_argument_count(1);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);
}

define_test(mthi_1)
{
    setup_test_variables();

    parse_opcode(0x00200011);

    assert_mnemonic(MTHI);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::AT);
}

// mflo rd
define_test(mflo_0)
{
    setup_test_variables();

    parse_opcode(0x00000012);

    assert_mnemonic(MFLO);
    assert_argument_count(1);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);
}

define_test(mflo_1)
{
    setup_test_variables();

    parse_opcode(0x00000812);

    assert_mnemonic(MFLO);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::AT);
}

// mtlo rs
define_test(mtlo_0)
{
    setup_test_variables();

    parse_opcode(0x00000013);

    assert_mnemonic(MTLO);
    assert_argument_count(1);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);
}

define_test(mtlo_1)
{
    setup_test_variables();

    parse_opcode(0x00200013);

    assert_mnemonic(MTLO);
    assert_argument_count(1);

    assert_argument_mips_register(0, mips_register::AT);
}

// clz rd, rs
define_test(clz_0)
{
    setup_test_variables();

    parse_opcode(0x00000016);

    assert_mnemonic(CLZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(clz_1)
{
    setup_test_variables();

    parse_opcode(0x00600816);

    assert_mnemonic(CLZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

// clo rd, rs
define_test(clo_0)
{
    setup_test_variables();

    parse_opcode(0x00000017);

    assert_mnemonic(CLO);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(clo_1)
{
    setup_test_variables();

    parse_opcode(0x00600817);

    assert_mnemonic(CLO);
    assert_argument_count(2);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::V1);
}

// mult rs, rt
define_test(mult_0)
{
    setup_test_variables();

    parse_opcode(0x00000018);

    assert_mnemonic(MULT);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(mult_1)
{
    setup_test_variables();

    parse_opcode(0x00610018);

    assert_mnemonic(MULT);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// multu rs, rt
define_test(multu_0)
{
    setup_test_variables();

    parse_opcode(0x00000019);

    assert_mnemonic(MULTU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(multu_1)
{
    setup_test_variables();

    parse_opcode(0x00610019);

    assert_mnemonic(MULTU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// div rs, rt
define_test(div_0)
{
    setup_test_variables();

    parse_opcode(0x0000001a);

    assert_mnemonic(DIV);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(div_1)
{
    setup_test_variables();

    parse_opcode(0x0061001a);

    assert_mnemonic(DIV);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// divu rs, rt
define_test(divu_0)
{
    setup_test_variables();

    parse_opcode(0x0000001b);

    assert_mnemonic(DIVU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(divu_1)
{
    setup_test_variables();

    parse_opcode(0x0061001b);

    assert_mnemonic(DIVU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// madd rs, rt
define_test(madd_0)
{
    setup_test_variables();

    parse_opcode(0x0000001c);

    assert_mnemonic(MADD);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(madd_1)
{
    setup_test_variables();

    parse_opcode(0x0061001c);

    assert_mnemonic(MADD);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// maddu rs, rt
define_test(maddu_0)
{
    setup_test_variables();

    parse_opcode(0x0000001d);

    assert_mnemonic(MADDU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(maddu_1)
{
    setup_test_variables();

    parse_opcode(0x0061001d);

    assert_mnemonic(MADDU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// add rd, rs, rt
define_test(add_0)
{
    setup_test_variables();

    parse_opcode(0x00000020);

    assert_mnemonic(ADD);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(add_1)
{
    setup_test_variables();

    parse_opcode(0x00e30820);

    assert_mnemonic(ADD);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// addu rd, rs, rt
define_test(addu_0)
{
    setup_test_variables();

    parse_opcode(0x00000021);

    assert_mnemonic(ADDU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(addu_1)
{
    setup_test_variables();

    parse_opcode(0x00e30821);

    assert_mnemonic(ADDU);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// li rd, 0
define_test(addu_li_0)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00000021);

    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_immediate(1, s16, 0);
}

define_test(addu_li_1)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00000821);

    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, immediate<s16>);
    assert_argument_immediate(1, s16, 0);
}

// move rd, rt
define_test(addu_move_0)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00010021);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// move rd, rs
define_test(addu_move_1)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00200021);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

define_test(addu_move_2)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00030821);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

define_test(addu_move_3)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00600821);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

// sub rd, rs, rt
define_test(sub_0)
{
    setup_test_variables();

    parse_opcode(0x00000022);

    assert_mnemonic(SUB);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(sub_1)
{
    setup_test_variables();

    parse_opcode(0x00e30822);

    assert_mnemonic(SUB);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// subu rd, rs, rt
define_test(subu_0)
{
    setup_test_variables();

    parse_opcode(0x00000023);

    assert_mnemonic(SUBU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(subu_1)
{
    setup_test_variables();

    parse_opcode(0x00e30823);

    assert_mnemonic(SUBU);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// and rd, rs, rt
define_test(and_0)
{
    setup_test_variables();

    parse_opcode(0x00000024);

    assert_mnemonic(AND);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(and_1)
{
    setup_test_variables();

    parse_opcode(0x00e30824);

    assert_mnemonic(AND);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// or rd, rs, rt
define_test(or_0)
{
    setup_test_variables();

    parse_opcode(0x00000025);

    assert_mnemonic(OR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(or_1)
{
    setup_test_variables();

    parse_opcode(0x00e30825);

    assert_mnemonic(OR);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// li rd, 0
define_test(or_li_0)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00000025);

    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_immediate(1, s16, 0);
}

define_test(or_li_1)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00000825);

    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, immediate<s16>);
    assert_argument_immediate(1, s16, 0);
}

// move rd, rt
define_test(or_move_0)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00010025);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// move rd, rs
define_test(or_move_1)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00200025);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

define_test(or_move_2)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00030825);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

define_test(or_move_3)
{
    setup_test_variables();
    emit_pseudoinstructions();

    parse_opcode(0x00600825);

    assert_mnemonic(MOVE);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::V1);
}

// xor rd, rs, rt
define_test(xor_0)
{
    setup_test_variables();

    parse_opcode(0x00000026);

    assert_mnemonic(XOR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(xor_1)
{
    setup_test_variables();

    parse_opcode(0x00e30826);

    assert_mnemonic(XOR);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// nor rd, rs, rt
define_test(nor_0)
{
    setup_test_variables();

    parse_opcode(0x00000027);

    assert_mnemonic(NOR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(nor_1)
{
    setup_test_variables();

    parse_opcode(0x00e30827);

    assert_mnemonic(NOR);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// slt rd, rs, rt
define_test(slt_0)
{
    setup_test_variables();

    parse_opcode(0x0000002a);

    assert_mnemonic(SLT);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(slt_1)
{
    setup_test_variables();

    parse_opcode(0x00e3082a);

    assert_mnemonic(SLT);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// sltu rd, rs, rt
define_test(sltu_0)
{
    setup_test_variables();

    parse_opcode(0x0000002b);

    assert_mnemonic(SLTU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(sltu_1)
{
    setup_test_variables();

    parse_opcode(0x00e3082b);

    assert_mnemonic(SLTU);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// max rd, rs, rt
define_test(max_0)
{
    setup_test_variables();

    parse_opcode(0x0000002c);

    assert_mnemonic(MAX);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(max_1)
{
    setup_test_variables();

    parse_opcode(0x00e3082c);

    assert_mnemonic(MAX);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// min rd, rs, rt
define_test(min_0)
{
    setup_test_variables();

    parse_opcode(0x0000002d);

    assert_mnemonic(MIN);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);

    assert_argument_type(2, mips_register);
    assert_argument_mips_register(2, mips_register::ZERO);
}

define_test(min_1)
{
    setup_test_variables();

    parse_opcode(0x00e3082d);

    assert_mnemonic(MIN);
    assert_argument_count(3);

    assert_argument_mips_register(0, mips_register::AT);
    assert_argument_mips_register(1, mips_register::A3);
    assert_argument_mips_register(2, mips_register::V1);
}

// msub rs, rt
define_test(msub_0)
{
    setup_test_variables();

    parse_opcode(0x0000002e);

    assert_mnemonic(MSUB);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(msub_1)
{
    setup_test_variables();

    parse_opcode(0x0061002e);

    assert_mnemonic(MSUB);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// msubu rs, rt
define_test(msubu_0)
{
    setup_test_variables();

    parse_opcode(0x0000002f);

    assert_mnemonic(MSUBU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(msubu_1)
{
    setup_test_variables();

    parse_opcode(0x0061002f);

    assert_mnemonic(MSUBU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// tge rs, rt
define_test(tge_0)
{
    setup_test_variables();

    parse_opcode(0x00000030);

    assert_mnemonic(TGE);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(tge_1)
{
    setup_test_variables();

    parse_opcode(0x00610030);

    assert_mnemonic(TGE);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// tgeu rs, rt
define_test(tgeu_0)
{
    setup_test_variables();

    parse_opcode(0x00000031);

    assert_mnemonic(TGEU);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(tgeu_1)
{
    setup_test_variables();

    parse_opcode(0x00610031);

    assert_mnemonic(TGEU);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// tlt rs, rt
define_test(tlt_0)
{
    setup_test_variables();

    parse_opcode(0x00000032);

    assert_mnemonic(TLT);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(tlt_1)
{
    setup_test_variables();

    parse_opcode(0x00610032);

    assert_mnemonic(TLT);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// tltu rs, rt
define_test(tltu_0)
{
    setup_test_variables();

    parse_opcode(0x00000033);

    assert_mnemonic(TLTU);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(tltu_1)
{
    setup_test_variables();

    parse_opcode(0x00610033);

    assert_mnemonic(TLTU);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// teq rs, rt
define_test(teq_0)
{
    setup_test_variables();

    parse_opcode(0x00000034);

    assert_mnemonic(TEQ);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(teq_1)
{
    setup_test_variables();

    parse_opcode(0x00610034);

    assert_mnemonic(TEQ);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

// tne rs, rt
define_test(tne_0)
{
    setup_test_variables();

    parse_opcode(0x00000036);

    assert_mnemonic(TNE);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::ZERO);
}

define_test(tne_1)
{
    setup_test_variables();

    parse_opcode(0x00610036);

    assert_mnemonic(TNE);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_mips_register(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_mips_register(1, mips_register::AT);
}

define_default_test_main();
