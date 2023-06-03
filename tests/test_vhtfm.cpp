
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vhtfm2 vd, vs, vt
define_test(vhtfm2_0)
{
    setup_test_variables();

    parse_opcode(0xf0800000);
    assert_mnemonic(VHTFM2);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Pair});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vhtfm2_1)
{
    setup_test_variables();

    parse_opcode(0xf0870301);
    assert_mnemonic(VHTFM2);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Pair});
}

// vtfm2 vd, vs, vt
define_test(vtfm2_0)
{
    setup_test_variables();

    parse_opcode(0xf0800080);
    assert_mnemonic(VTFM2);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Pair});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Pair});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Pair});
}

define_test(vtfm2_1)
{
    setup_test_variables();

    parse_opcode(0xf0870381);
    assert_mnemonic(VTFM2);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Pair});
}

// vhtfm3 vd, vs, vt
define_test(vhtfm3_0)
{
    setup_test_variables();

    parse_opcode(0xf1000080);
    assert_mnemonic(VHTFM3);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Triple});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vhtfm3_1)
{
    setup_test_variables();

    parse_opcode(0xf1070381);
    assert_mnemonic(VHTFM3);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Triple});
}

// vtfm3 vd, vs, vt
define_test(vtfm3_0)
{
    setup_test_variables();

    parse_opcode(0xf1008000);
    assert_mnemonic(VTFM3);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Triple});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vtfm3_1)
{
    setup_test_variables();

    parse_opcode(0xf1078301);
    assert_mnemonic(VTFM3);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Triple});
}

// vhtfm4 vd, vs, vt
define_test(vhtfm4_0)
{
    setup_test_variables();

    parse_opcode(0xf1808000);
    assert_mnemonic(VHTFM4);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Quad});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_test(vhtfm4_1)
{
    setup_test_variables();

    parse_opcode(0xf1878301);
    assert_mnemonic(VHTFM4);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Quad});
}

// vtfm4 vd, vs, vt
define_test(vtfm4_0)
{
    setup_test_variables();

    parse_opcode(0xf1808080);
    assert_mnemonic(VTFM4);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::VFPU_Matrix);
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{0, vfpu_size::Quad});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_test(vtfm4_1)
{
    setup_test_variables();

    parse_opcode(0xf1878381);
    assert_mnemonic(VTFM4);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_matrix, vfpu_matrix{3, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Quad});
}

define_default_test_main();
