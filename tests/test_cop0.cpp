
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// mfc0 rt, rd, sel
define_test(mfc0_0)
{
    setup_test_variables();

    parse_opcode(0x40000000);
    assert_mnemonic(MFC0);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Coprocessor_Register);
    assert_argument_equals(1, coprocessor_register, coprocessor_register{0, 0});
}

define_test(mfc0_1)
{
    setup_test_variables();

    parse_opcode(0x40071801);
    assert_mnemonic(MFC0);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::A3);

    assert_argument_type(1, argument_type::Coprocessor_Register);
    assert_argument_equals(1, coprocessor_register, coprocessor_register{3, 1});
}

// mtc0 rt, rd, sel
define_test(mtc0_0)
{
    setup_test_variables();

    parse_opcode(0x40800000);
    assert_mnemonic(MTC0);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Coprocessor_Register);
    assert_argument_equals(1, coprocessor_register, coprocessor_register{0, 0});
}

define_test(mtc0_1)
{
    setup_test_variables();

    parse_opcode(0x40871801);
    assert_mnemonic(MTC0);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::A3);

    assert_argument_type(1, argument_type::Coprocessor_Register);
    assert_argument_equals(1, coprocessor_register, coprocessor_register{3, 1});
}

// rdpgpr rd, rt
define_test(rdpgpr_0)
{
    setup_test_variables();

    parse_opcode(0x41600000);
    assert_mnemonic(RDPGPR);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::ZERO);
}

define_test(rdpgpr_1)
{
    setup_test_variables();

    parse_opcode(0x41630800);
    assert_mnemonic(RDPGPR);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::AT);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::V1);
}

// mfmc0
define_test(mfmc0_0)
{
    setup_test_variables();

    parse_opcode(0x41800000);
    assert_mnemonic(MFMC0);
    assert_argument_count(0);
}

// wrpgpr rd, rt
define_test(wrpgpr_0)
{
    setup_test_variables();

    parse_opcode(0x41c00000);
    assert_mnemonic(WRPGPR);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::ZERO);
}

define_test(wrpgpr_1)
{
    setup_test_variables();

    parse_opcode(0x41c30800);
    assert_mnemonic(WRPGPR);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::AT);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::V1);
}

define_default_test_main();
