
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vcst vd, vs
define_test(vcst_0)
{
    setup_test_variables();

    parse_opcode(0xd0600000);
    assert_mnemonic(VCST);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Constant);
    assert_argument_equals(1, vfpu_constant, vfpu_constant::VFPU_UNDEFINED);
}

define_test(vcst_1)
{
    setup_test_variables();

    parse_opcode(0xd0630001);
    assert_mnemonic(VCST);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_constant, vfpu_constant::VFPU_SQRT1_2);
}

define_test(vcst_2)
{
    setup_test_variables();

    parse_opcode(0xd0600080);
    assert_mnemonic(VCST);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_constant, vfpu_constant::VFPU_UNDEFINED);
}

define_test(vcst_3)
{
    setup_test_variables();

    parse_opcode(0xd0608000);
    assert_mnemonic(VCST);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_constant, vfpu_constant::VFPU_UNDEFINED);
}

define_test(vcst_4)
{
    setup_test_variables();

    parse_opcode(0xd0608080);
    assert_mnemonic(VCST);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_constant, vfpu_constant::VFPU_UNDEFINED);
}

// vf2in vd, vs, imm
define_test(vf2in_0)
{
    setup_test_variables();

    parse_opcode(0xd2000000);
    assert_mnemonic(VF2IN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::Immediate_u8);
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2in_1)
{
    setup_test_variables();

    parse_opcode(0xd2050301);
    assert_mnemonic(VF2IN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate_u8, immediate<u8>{5});
}

define_test(vf2in_2)
{
    setup_test_variables();

    parse_opcode(0xd2000080);
    assert_mnemonic(VF2IN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2in_3)
{
    setup_test_variables();

    parse_opcode(0xd2008000);
    assert_mnemonic(VF2IN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2in_4)
{
    setup_test_variables();

    parse_opcode(0xd2008080);
    assert_mnemonic(VF2IN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

// vf2iz vd, vs, imm
define_test(vf2iz_0)
{
    setup_test_variables();

    parse_opcode(0xd2200000);
    assert_mnemonic(VF2IZ);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::Immediate_u8);
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iz_1)
{
    setup_test_variables();

    parse_opcode(0xd2250301);
    assert_mnemonic(VF2IZ);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate_u8, immediate<u8>{5});
}

define_test(vf2iz_2)
{
    setup_test_variables();

    parse_opcode(0xd2200080);
    assert_mnemonic(VF2IZ);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iz_3)
{
    setup_test_variables();

    parse_opcode(0xd2208000);
    assert_mnemonic(VF2IZ);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iz_4)
{
    setup_test_variables();

    parse_opcode(0xd2208080);
    assert_mnemonic(VF2IZ);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

// vf2iu vd, vs, imm
define_test(vf2iu_0)
{
    setup_test_variables();

    parse_opcode(0xd2400000);
    assert_mnemonic(VF2IU);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::Immediate_u8);
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iu_1)
{
    setup_test_variables();

    parse_opcode(0xd2450301);
    assert_mnemonic(VF2IU);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate_u8, immediate<u8>{5});
}

define_test(vf2iu_2)
{
    setup_test_variables();

    parse_opcode(0xd2400080);
    assert_mnemonic(VF2IU);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iu_3)
{
    setup_test_variables();

    parse_opcode(0xd2408000);
    assert_mnemonic(VF2IU);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2iu_4)
{
    setup_test_variables();

    parse_opcode(0xd2408080);
    assert_mnemonic(VF2IU);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

// vf2id vd, vs, imm
define_test(vf2id_0)
{
    setup_test_variables();

    parse_opcode(0xd2600000);
    assert_mnemonic(VF2ID);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::Immediate_u8);
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2id_1)
{
    setup_test_variables();

    parse_opcode(0xd2650301);
    assert_mnemonic(VF2ID);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate_u8, immediate<u8>{5});
}

define_test(vf2id_2)
{
    setup_test_variables();

    parse_opcode(0xd2600080);
    assert_mnemonic(VF2ID);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2id_3)
{
    setup_test_variables();

    parse_opcode(0xd2608000);
    assert_mnemonic(VF2ID);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vf2id_4)
{
    setup_test_variables();

    parse_opcode(0xd2608080);
    assert_mnemonic(VF2ID);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

// vi2f vd, vs, imm
define_test(vi2f_0)
{
    setup_test_variables();

    parse_opcode(0xd2800000);
    assert_mnemonic(VI2F);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::Immediate_u8);
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vi2f_1)
{
    setup_test_variables();

    parse_opcode(0xd2850301);
    assert_mnemonic(VI2F);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate_u8, immediate<u8>{5});
}

define_test(vi2f_2)
{
    setup_test_variables();

    parse_opcode(0xd2800080);
    assert_mnemonic(VI2F);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vi2f_3)
{
    setup_test_variables();

    parse_opcode(0xd2808000);
    assert_mnemonic(VI2F);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_test(vi2f_4)
{
    setup_test_variables();

    parse_opcode(0xd2808080);
    assert_mnemonic(VI2F);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate_u8, immediate<u8>{0});
}

define_default_test_main();
