
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vcmp vd, vs, vt
define_test(vcmp_0)
{
    setup_test_variables();

    parse_opcode(0x6c000000);
    assert_mnemonic(VCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Condition);
    assert_argument_equals(0, vfpu_condition, vfpu_condition::FL);

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vcmp_1)
{
    setup_test_variables();

    parse_opcode(0x6c070301);
    assert_mnemonic(VCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_condition, vfpu_condition::EQ);
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vcmp_2)
{
    setup_test_variables();

    parse_opcode(0x6c000080);
    assert_mnemonic(VCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_condition, vfpu_condition::FL);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vcmp_3)
{
    setup_test_variables();

    parse_opcode(0x6c008000);
    assert_mnemonic(VCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_condition, vfpu_condition::FL);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vcmp_4)
{
    setup_test_variables();

    parse_opcode(0x6c008080);
    assert_mnemonic(VCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_condition, vfpu_condition::FL);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vmin vd, vs, vt
define_test(vmin_0)
{
    setup_test_variables();

    parse_opcode(0x6d000000);
    assert_mnemonic(VMIN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vmin_1)
{
    setup_test_variables();

    parse_opcode(0x6d070301);
    assert_mnemonic(VMIN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vmin_2)
{
    setup_test_variables();

    parse_opcode(0x6d000080);
    assert_mnemonic(VMIN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vmin_3)
{
    setup_test_variables();

    parse_opcode(0x6d008000);
    assert_mnemonic(VMIN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vmin_4)
{
    setup_test_variables();

    parse_opcode(0x6d008080);
    assert_mnemonic(VMIN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vmax vd, vs, vt
define_test(vmax_0)
{
    setup_test_variables();

    parse_opcode(0x6d800000);
    assert_mnemonic(VMAX);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vmax_1)
{
    setup_test_variables();

    parse_opcode(0x6d870301);
    assert_mnemonic(VMAX);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vmax_2)
{
    setup_test_variables();

    parse_opcode(0x6d800080);
    assert_mnemonic(VMAX);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vmax_3)
{
    setup_test_variables();

    parse_opcode(0x6d808000);
    assert_mnemonic(VMAX);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vmax_4)
{
    setup_test_variables();

    parse_opcode(0x6d808080);
    assert_mnemonic(VMAX);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vscmp vd, vs, vt
define_test(vscmp_0)
{
    setup_test_variables();

    parse_opcode(0x6e800000);
    assert_mnemonic(VSCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vscmp_1)
{
    setup_test_variables();

    parse_opcode(0x6e870301);
    assert_mnemonic(VSCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vscmp_2)
{
    setup_test_variables();

    parse_opcode(0x6e800080);
    assert_mnemonic(VSCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vscmp_3)
{
    setup_test_variables();

    parse_opcode(0x6e808000);
    assert_mnemonic(VSCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vscmp_4)
{
    setup_test_variables();

    parse_opcode(0x6e808080);
    assert_mnemonic(VSCMP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsge vd, vs, vt
define_test(vsge_0)
{
    setup_test_variables();

    parse_opcode(0x6f000000);
    assert_mnemonic(VSGE);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsge_1)
{
    setup_test_variables();

    parse_opcode(0x6f070301);
    assert_mnemonic(VSGE);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vsge_2)
{
    setup_test_variables();

    parse_opcode(0x6f000080);
    assert_mnemonic(VSGE);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsge_3)
{
    setup_test_variables();

    parse_opcode(0x6f008000);
    assert_mnemonic(VSGE);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsge_4)
{
    setup_test_variables();

    parse_opcode(0x6f008080);
    assert_mnemonic(VSGE);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vslt vd, vs, vt
define_test(vslt_0)
{
    setup_test_variables();

    parse_opcode(0x6f800000);
    assert_mnemonic(VSLT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vslt_1)
{
    setup_test_variables();

    parse_opcode(0x6f870301);
    assert_mnemonic(VSLT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vslt_2)
{
    setup_test_variables();

    parse_opcode(0x6f800080);
    assert_mnemonic(VSLT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vslt_3)
{
    setup_test_variables();

    parse_opcode(0x6f808000);
    assert_mnemonic(VSLT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vslt_4)
{
    setup_test_variables();

    parse_opcode(0x6f808080);
    assert_mnemonic(VSLT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
