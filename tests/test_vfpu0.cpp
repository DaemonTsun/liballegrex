
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vadd vd, vs, vt
define_test(vadd_0)
{
    setup_test_variables();

    parse_opcode(0x60000000);
    assert_mnemonic(VADD);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vadd_1)
{
    setup_test_variables();

    parse_opcode(0x60070301);
    assert_mnemonic(VADD);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vadd_2)
{
    setup_test_variables();

    parse_opcode(0x60000080);
    assert_mnemonic(VADD);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vadd_3)
{
    setup_test_variables();

    parse_opcode(0x60008000);
    assert_mnemonic(VADD);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vadd_4)
{
    setup_test_variables();

    parse_opcode(0x60008080);
    assert_mnemonic(VADD);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsub vd, vs, vt
define_test(vsub_0)
{
    setup_test_variables();

    parse_opcode(0x60800000);
    assert_mnemonic(VSUB);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsub_1)
{
    setup_test_variables();

    parse_opcode(0x60870301);
    assert_mnemonic(VSUB);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vsub_2)
{
    setup_test_variables();

    parse_opcode(0x60800080);
    assert_mnemonic(VSUB);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsub_3)
{
    setup_test_variables();

    parse_opcode(0x60808000);
    assert_mnemonic(VSUB);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsub_4)
{
    setup_test_variables();

    parse_opcode(0x60808080);
    assert_mnemonic(VSUB);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vsbn vd, vs, vt
define_test(vsbn_0)
{
    setup_test_variables();

    parse_opcode(0x61000000);
    assert_mnemonic(VSBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vsbn_1)
{
    setup_test_variables();

    parse_opcode(0x61070301);
    assert_mnemonic(VSBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vsbn_2)
{
    setup_test_variables();

    parse_opcode(0x61000080);
    assert_mnemonic(VSBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsbn_3)
{
    setup_test_variables();

    parse_opcode(0x61008000);
    assert_mnemonic(VSBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsbn_4)
{
    setup_test_variables();

    parse_opcode(0x61008080);
    assert_mnemonic(VSBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

// vdiv vd, vs, vt
define_test(vdiv_0)
{
    setup_test_variables();

    parse_opcode(0x63800000);
    assert_mnemonic(VDIV);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Single});
}

define_test(vdiv_1)
{
    setup_test_variables();

    parse_opcode(0x63870301);
    assert_mnemonic(VDIV);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Single});
}

define_test(vdiv_2)
{
    setup_test_variables();

    parse_opcode(0x63800080);
    assert_mnemonic(VDIV);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vdiv_3)
{
    setup_test_variables();

    parse_opcode(0x63808000);
    assert_mnemonic(VDIV);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vdiv_4)
{
    setup_test_variables();

    parse_opcode(0x63808080);
    assert_mnemonic(VDIV);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
