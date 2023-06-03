
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// mfc2 rt, ???
define_test(mfc2_0)
{
    setup_test_variables();

    parse_opcode(0x48000000);
    assert_mnemonic(MFC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{0});
}

define_test(mfc2_1)
{
    setup_test_variables();

    parse_opcode(0x48030001);
    assert_mnemonic(MFC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{1});
}

// cfc2 rt, ???
define_test(cfc2_0)
{
    setup_test_variables();

    parse_opcode(0x48400000);
    assert_mnemonic(CFC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{0});
}

define_test(cfc2_1)
{
    setup_test_variables();

    parse_opcode(0x48430001);
    assert_mnemonic(CFC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{1});
}

// mfv rt, vr
define_test(mfv_0)
{
    setup_test_variables();

    parse_opcode(0x48600000);
    assert_mnemonic(MFV);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(mfv_1)
{
    setup_test_variables();

    parse_opcode(0x48630001);
    assert_mnemonic(MFV);
    assert_argument_count(2);

    assert_argument_equals(0, mips_register, mips_register::V1);
    assert_argument_equals(1, vfpu_register, vfpu_register{1, vfpu_size::Single});
}

// mtc2 rt, ???
define_test(mtc2_0)
{
    setup_test_variables();

    parse_opcode(0x48800000);
    assert_mnemonic(MTC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{0});
}

define_test(mtc2_1)
{
    setup_test_variables();

    parse_opcode(0x48830001);
    assert_mnemonic(MTC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{1});
}

// ctc2 rt, ???
define_test(ctc2_0)
{
    setup_test_variables();

    parse_opcode(0x48c00000);
    assert_mnemonic(CTC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{0});
}

define_test(ctc2_1)
{
    setup_test_variables();

    parse_opcode(0x48c30001);
    assert_mnemonic(CTC2);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::V1);

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{1});
}

// mtv rt, vr
define_test(mtv_0)
{
    setup_test_variables();

    parse_opcode(0x48e00000);
    assert_mnemonic(MTV);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(mtv_1)
{
    setup_test_variables();

    parse_opcode(0x48e30001);
    assert_mnemonic(MTV);
    assert_argument_count(2);

    assert_argument_equals(0, mips_register, mips_register::V1);
    assert_argument_equals(1, vfpu_register, vfpu_register{1, vfpu_size::Single});
}

define_default_test_main();
