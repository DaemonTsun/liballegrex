#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// add.s fd, fs, ft
define_test(add_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000000);
    assert_mnemonic(ADD_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(add_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071840);
    assert_mnemonic(ADD_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// sub.s fd, fs, ft
define_test(sub_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000001);
    assert_mnemonic(SUB_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(sub_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071841);
    assert_mnemonic(SUB_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// mul.s fd, fs, ft
define_test(mul_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000002);
    assert_mnemonic(MUL_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(mul_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071842);
    assert_mnemonic(MUL_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// div.s fd, fs, ft
define_test(div_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000003);
    assert_mnemonic(DIV_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(div_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071843);
    assert_mnemonic(DIV_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

define_default_test_main();
