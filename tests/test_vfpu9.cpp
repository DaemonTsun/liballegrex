
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vsrt1 vd, vs
define_test(vsrt1_0)
{
    setup_test_variables();

    parse_opcode(0xd0400000);
    assert_mnemonic(VSRT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsrt1_1)
{
    setup_test_variables();

    parse_opcode(0xd0400301);
    assert_mnemonic(VSRT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsrt1_2)
{
    setup_test_variables();

    parse_opcode(0xd0400080);
    assert_mnemonic(VSRT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsrt1_3)
{
    setup_test_variables();

    parse_opcode(0xd0408000);
    assert_mnemonic(VSRT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsrt1_4)
{
    setup_test_variables();

    parse_opcode(0xd0408080);
    assert_mnemonic(VSRT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsrt2 vd, vs
define_test(vsrt2_0)
{
    setup_test_variables();

    parse_opcode(0xd0410000);
    assert_mnemonic(VSRT2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsrt2_1)
{
    setup_test_variables();

    parse_opcode(0xd0410301);
    assert_mnemonic(VSRT2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsrt2_2)
{
    setup_test_variables();

    parse_opcode(0xd0410080);
    assert_mnemonic(VSRT2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsrt2_3)
{
    setup_test_variables();

    parse_opcode(0xd0418000);
    assert_mnemonic(VSRT2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsrt2_4)
{
    setup_test_variables();

    parse_opcode(0xd0418080);
    assert_mnemonic(VSRT2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vbfy1 vd, vs
define_test(vbfy1_0)
{
    setup_test_variables();

    parse_opcode(0xd0420000);
    assert_mnemonic(VBFY1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vbfy1_1)
{
    setup_test_variables();

    parse_opcode(0xd0420301);
    assert_mnemonic(VBFY1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vbfy1_2)
{
    setup_test_variables();

    parse_opcode(0xd0420080);
    assert_mnemonic(VBFY1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vbfy1_3)
{
    setup_test_variables();

    parse_opcode(0xd0428000);
    assert_mnemonic(VBFY1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vbfy1_4)
{
    setup_test_variables();

    parse_opcode(0xd0428080);
    assert_mnemonic(VBFY1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vbfy2 vd, vs
define_test(vbfy2_0)
{
    setup_test_variables();

    parse_opcode(0xd0430000);
    assert_mnemonic(VBFY2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vbfy2_1)
{
    setup_test_variables();

    parse_opcode(0xd0430301);
    assert_mnemonic(VBFY2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vbfy2_2)
{
    setup_test_variables();

    parse_opcode(0xd0430080);
    assert_mnemonic(VBFY2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vbfy2_3)
{
    setup_test_variables();

    parse_opcode(0xd0438000);
    assert_mnemonic(VBFY2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vbfy2_4)
{
    setup_test_variables();

    parse_opcode(0xd0438080);
    assert_mnemonic(VBFY2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vocp vd, vs
define_test(vocp_0)
{
    setup_test_variables();

    parse_opcode(0xd0440000);
    assert_mnemonic(VOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vocp_1)
{
    setup_test_variables();

    parse_opcode(0xd0440301);
    assert_mnemonic(VOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vocp_2)
{
    setup_test_variables();

    parse_opcode(0xd0440080);
    assert_mnemonic(VOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vocp_3)
{
    setup_test_variables();

    parse_opcode(0xd0448000);
    assert_mnemonic(VOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vocp_4)
{
    setup_test_variables();

    parse_opcode(0xd0448080);
    assert_mnemonic(VOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsocp vd, vs
define_test(vsocp_0)
{
    setup_test_variables();

    parse_opcode(0xd0450000);
    assert_mnemonic(VSOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsocp_1)
{
    setup_test_variables();

    parse_opcode(0xd0450301);
    assert_mnemonic(VSOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsocp_2)
{
    setup_test_variables();

    parse_opcode(0xd0450080);
    assert_mnemonic(VSOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsocp_3)
{
    setup_test_variables();

    parse_opcode(0xd0458000);
    assert_mnemonic(VSOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsocp_4)
{
    setup_test_variables();

    parse_opcode(0xd0458080);
    assert_mnemonic(VSOCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vfad vd, vs
define_test(vfad_0)
{
    setup_test_variables();

    parse_opcode(0xd0460000);
    assert_mnemonic(VFAD);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vfad_1)
{
    setup_test_variables();

    parse_opcode(0xd0460301);
    assert_mnemonic(VFAD);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vfad_2)
{
    setup_test_variables();

    parse_opcode(0xd0460080);
    assert_mnemonic(VFAD);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vfad_3)
{
    setup_test_variables();

    parse_opcode(0xd0468000);
    assert_mnemonic(VFAD);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vfad_4)
{
    setup_test_variables();

    parse_opcode(0xd0468080);
    assert_mnemonic(VFAD);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vavg vd, vs
define_test(vavg_0)
{
    setup_test_variables();

    parse_opcode(0xd0470000);
    assert_mnemonic(VAVG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vavg_1)
{
    setup_test_variables();

    parse_opcode(0xd0470301);
    assert_mnemonic(VAVG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vavg_2)
{
    setup_test_variables();

    parse_opcode(0xd0470080);
    assert_mnemonic(VAVG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vavg_3)
{
    setup_test_variables();

    parse_opcode(0xd0478000);
    assert_mnemonic(VAVG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vavg_4)
{
    setup_test_variables();

    parse_opcode(0xd0478080);
    assert_mnemonic(VAVG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsrt3 vd, vs
define_test(vsrt3_0)
{
    setup_test_variables();

    parse_opcode(0xd0480000);
    assert_mnemonic(VSRT3);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsrt3_1)
{
    setup_test_variables();

    parse_opcode(0xd0480301);
    assert_mnemonic(VSRT3);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsrt3_2)
{
    setup_test_variables();

    parse_opcode(0xd0480080);
    assert_mnemonic(VSRT3);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsrt3_3)
{
    setup_test_variables();

    parse_opcode(0xd0488000);
    assert_mnemonic(VSRT3);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsrt3_4)
{
    setup_test_variables();

    parse_opcode(0xd0488080);
    assert_mnemonic(VSRT3);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsrt4 vd, vs
define_test(vsrt4_0)
{
    setup_test_variables();

    parse_opcode(0xd0490000);
    assert_mnemonic(VSRT4);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsrt4_1)
{
    setup_test_variables();

    parse_opcode(0xd0490301);
    assert_mnemonic(VSRT4);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsrt4_2)
{
    setup_test_variables();

    parse_opcode(0xd0490080);
    assert_mnemonic(VSRT4);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsrt4_3)
{
    setup_test_variables();

    parse_opcode(0xd0498000);
    assert_mnemonic(VSRT4);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsrt4_4)
{
    setup_test_variables();

    parse_opcode(0xd0498080);
    assert_mnemonic(VSRT4);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsgn vd, vs
define_test(vsgn_0)
{
    setup_test_variables();

    parse_opcode(0xd04a0000);
    assert_mnemonic(VSGN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsgn_1)
{
    setup_test_variables();

    parse_opcode(0xd04a0301);
    assert_mnemonic(VSGN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
}

define_test(vsgn_2)
{
    setup_test_variables();

    parse_opcode(0xd04a0080);
    assert_mnemonic(VSGN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsgn_3)
{
    setup_test_variables();

    parse_opcode(0xd04a8000);
    assert_mnemonic(VSGN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsgn_4)
{
    setup_test_variables();

    parse_opcode(0xd04a8080);
    assert_mnemonic(VSGN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vmfvc vd, vs (control register)
define_test(vmfvc_0)
{
    setup_test_variables();

    parse_opcode(0xd0500000);
    assert_mnemonic(VMFVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmfvc_1)
{
    setup_test_variables();

    parse_opcode(0xd0500301);
    assert_mnemonic(VMFVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{131, vfpu_size::Single});
}

define_test(vmfvc_2)
{
    setup_test_variables();

    parse_opcode(0xd0500080);
    assert_mnemonic(VMFVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmfvc_3)
{
    setup_test_variables();

    parse_opcode(0xd0508000);
    assert_mnemonic(VMFVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmfvc_4)
{
    setup_test_variables();

    parse_opcode(0xd0508080);
    assert_mnemonic(VMFVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

// vmtvc vs, vd (control register)
define_test(vmtvc_0)
{
    setup_test_variables();

    parse_opcode(0xd0510000);
    assert_mnemonic(VMTVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmtvc_1)
{
    setup_test_variables();

    parse_opcode(0xd0510301);
    assert_mnemonic(VMTVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{129, vfpu_size::Single});
}

define_test(vmtvc_2)
{
    setup_test_variables();

    parse_opcode(0xd0510080);
    assert_mnemonic(VMTVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmtvc_3)
{
    setup_test_variables();

    parse_opcode(0xd0518000);
    assert_mnemonic(VMTVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

define_test(vmtvc_4)
{
    setup_test_variables();

    parse_opcode(0xd0518080);
    assert_mnemonic(VMTVC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{128, vfpu_size::Single});
}

// vt4444 vd, vs
define_test(vt4444_0)
{
    setup_test_variables();

    parse_opcode(0xd0590000);
    assert_mnemonic(VT4444);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vt4444_1)
{
    setup_test_variables();

    parse_opcode(0xd0590080);
    assert_mnemonic(VT4444);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vt4444_2)
{
    setup_test_variables();

    parse_opcode(0xd0598080);
    assert_mnemonic(VT4444);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vt5551 vd, vs
define_test(vt5551_0)
{
    setup_test_variables();

    parse_opcode(0xd05a0000);
    assert_mnemonic(VT5551);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vt5551_1)
{
    setup_test_variables();

    parse_opcode(0xd05a0080);
    assert_mnemonic(VT5551);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vt5551_2)
{
    setup_test_variables();

    parse_opcode(0xd05a8080);
    assert_mnemonic(VT5551);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vt5650 vd, vs
define_test(vt5650_0)
{
    setup_test_variables();

    parse_opcode(0xd05b0000);
    assert_mnemonic(VT5650);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vt5650_1)
{
    setup_test_variables();

    parse_opcode(0xd05b0080);
    assert_mnemonic(VT5650);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vt5650_2)
{
    setup_test_variables();

    parse_opcode(0xd05b8080);
    assert_mnemonic(VT5650);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
