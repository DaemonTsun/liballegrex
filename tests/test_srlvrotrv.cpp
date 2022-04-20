
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// srlv rd, rt, rs
define_test(srlv_0)
{
    setup_test_variables();

    parse_opcode(0x00000006);

    assert_mnemonic(SRLV);
    assert_argument_count(3);

    assert_argument_type(0, mips_register); // rd
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register); // rt
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, mips_register); // rs
    assert_argument_equals(2, mips_register::ZERO);
}

define_test(srlv_1)
{
    setup_test_variables();

    parse_opcode(0x00e30806);

    assert_mnemonic(SRLV);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::AT);
    assert_argument_equals(1, mips_register::V1);
    assert_argument_equals(2, mips_register::A3);
}

define_test(srlv_2)
{
    setup_test_variables();

    parse_opcode(0x03fff806);

    assert_mnemonic(SRLV);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::RA);
    assert_argument_equals(1, mips_register::RA);
    assert_argument_equals(2, mips_register::RA);
}

// rotrv rd, rt, rs
define_test(rotrv_0)
{
    setup_test_variables();

    parse_opcode(0x00000046);

    assert_mnemonic(ROTRV);
    assert_argument_count(3);

    assert_argument_type(0, mips_register); // rd
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register); // rt
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, mips_register); // rs
    assert_argument_equals(2, mips_register::ZERO);
}

define_test(rotrv_1)
{
    setup_test_variables();

    parse_opcode(0x00e30846);

    assert_mnemonic(ROTRV);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::AT);
    assert_argument_equals(1, mips_register::V1);
    assert_argument_equals(2, mips_register::A3);
}

define_test(rotrv_2)
{
    setup_test_variables();

    parse_opcode(0x03fff846);

    assert_mnemonic(ROTRV);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::RA);
    assert_argument_equals(1, mips_register::RA);
    assert_argument_equals(2, mips_register::RA);
}

define_default_test_main();
