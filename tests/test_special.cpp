
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
    assert_argument_count(2);

    assert_argument_type(0, const syscall*);
    _assert_argument_equals(0, const syscall*, get_syscall(0, 0));

    assert_argument_type(1, extra);
    _assert_argument_data_equals(1, extra, 0);
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

define_default_test_main();
