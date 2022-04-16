
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// sll
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

// sra
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

// sllv
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

// srav
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

// jr
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

// jalr
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



define_default_test_main();
