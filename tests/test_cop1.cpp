#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// mfc1 rt, fs
define_test(mfc1_0)
{
    setup_test_variables();

    parse_opcode(0x44000000);
    assert_mnemonic(MFC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F0);
}

define_test(mfc1_1)
{
    setup_test_variables();

    parse_opcode(0x44030800);
    assert_mnemonic(MFC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F1);
}

// cfc1 rt, fs
define_test(cfc1_0)
{
    setup_test_variables();

    parse_opcode(0x44400000);
    assert_mnemonic(CFC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F0);
}

define_test(cfc1_1)
{
    setup_test_variables();

    parse_opcode(0x44430800);
    assert_mnemonic(CFC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F1);
}

// mtc1 rt, fs
define_test(mtc1_0)
{
    setup_test_variables();

    parse_opcode(0x44800000);
    assert_mnemonic(MTC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F0);
}

define_test(mtc1_1)
{
    setup_test_variables();

    parse_opcode(0x44830800);
    assert_mnemonic(MTC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F1);
}

// ctc1 rt, fs
define_test(ctc1_0)
{
    setup_test_variables();

    parse_opcode(0x44c00000);
    assert_mnemonic(CTC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F0);
}

define_test(ctc1_1)
{
    setup_test_variables();

    parse_opcode(0x44c30800);
    assert_mnemonic(CTC1);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F1);
}

define_default_test_main();
