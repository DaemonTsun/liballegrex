
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// wsbh rd, rt
define_test(wsbh_0)
{
    setup_test_variables();

    parse_opcode(0x7c0000a0);
    assert_mnemonic(WSBH);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);
}

define_test(wsbh_1)
{
    setup_test_variables();

    parse_opcode(0x7c0308a0);
    assert_mnemonic(WSBH);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);
}

// wsbw rd, rt
define_test(wsbw_0)
{
    setup_test_variables();

    parse_opcode(0x7c0000e0);
    assert_mnemonic(WSBW);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);
}

define_test(wsbw_1)
{
    setup_test_variables();

    parse_opcode(0x7c0308e0);
    assert_mnemonic(WSBW);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);
}

// seb rd, rt
define_test(seb_0)
{
    setup_test_variables();

    parse_opcode(0x7c000420);
    assert_mnemonic(SEB);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);
}

define_test(seb_1)
{
    setup_test_variables();

    parse_opcode(0x7c030c20);
    assert_mnemonic(SEB);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);
}

// bitrev rd, rt
define_test(bitrev_0)
{
    setup_test_variables();

    parse_opcode(0x7c000520);
    assert_mnemonic(BITREV);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);
}

define_test(bitrev_1)
{
    setup_test_variables();

    parse_opcode(0x7c030d20);
    assert_mnemonic(BITREV);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);
}

// seh rd, rt
define_test(seh_0)
{
    setup_test_variables();

    parse_opcode(0x7c000620);
    assert_mnemonic(SEH);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);
}

define_test(seh_1)
{
    setup_test_variables();

    parse_opcode(0x7c030e20);
    assert_mnemonic(SEH);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::AT);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);
}

define_default_test_main();
