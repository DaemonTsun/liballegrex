
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// srl rd, rt, sa
define_test(srl_0)
{
    setup_test_variables();

    parse_opcode(0x00000002);

    assert_mnemonic(SRL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, shift);
    assert_argument_equals(2, shift{0u});
}

define_test(srl_1)
{
    setup_test_variables();

    parse_opcode(0x000008C2);

    assert_mnemonic(SRL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::AT);
    assert_argument_equals(1, mips_register::ZERO);
    assert_argument_equals(2, shift{3u});
}

define_test(srl_2)
{
    setup_test_variables();

    parse_opcode(0x001fffc2);

    assert_mnemonic(SRL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::RA);
    assert_argument_equals(1, mips_register::RA);
    assert_argument_equals(2, shift{31u});
}

// rotr rd, rt, sa
define_test(rotr_0)
{
    setup_test_variables();

    parse_opcode(0x00200002);

    assert_mnemonic(ROTR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, shift);
    assert_argument_equals(2, shift{0u});
}

define_test(rotr_1)
{
    setup_test_variables();

    parse_opcode(0x002008C2);

    assert_mnemonic(ROTR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::AT);
    assert_argument_equals(1, mips_register::ZERO);
    assert_argument_equals(2, shift{3u});
}

define_test(rotr_2)
{
    setup_test_variables();

    parse_opcode(0x003fffc2);

    assert_mnemonic(ROTR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::RA);
    assert_argument_equals(1, mips_register::RA);
    assert_argument_equals(2, shift{31u});
}

define_default_test_main();
