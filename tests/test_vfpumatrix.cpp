
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vmmov mvd, mvs
define_test(vmmov_0)
{
    setup_test_variables();

    parse_opcode(0xf3800000);
    assert_mnemonic(VMMOV);
    assert_argument_count(2);
    // technically not allowed
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_matrix);
    assert_argument_equals(1, vfpu_matrix{0, vfpu_size::Single});
}

define_test(vmmov_1)
{
    setup_test_variables();

    parse_opcode(0xf3800301);
    assert_mnemonic(VMMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_matrix{3, vfpu_size::Single});
}

define_test(vmmov_2)
{
    setup_test_variables();

    parse_opcode(0xf3800381);
    assert_mnemonic(VMMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_matrix{3, vfpu_size::Pair});
}

define_test(vmmov_3)
{
    setup_test_variables();

    parse_opcode(0xf3808301);
    assert_mnemonic(VMMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_matrix{3, vfpu_size::Triple});
}

define_test(vmmov_4)
{
    setup_test_variables();

    parse_opcode(0xf3808381);
    assert_mnemonic(VMMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_matrix{3, vfpu_size::Quad});
}

// vmidt mvd
define_test(vmidt_0)
{
    setup_test_variables();

    parse_opcode(0xf3830000);
    assert_mnemonic(VMIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Single});
}

define_test(vmidt_1)
{
    setup_test_variables();

    parse_opcode(0xf3830001);
    assert_mnemonic(VMIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Single});
}

define_test(vmidt_2)
{
    setup_test_variables();

    parse_opcode(0xf3830081);
    assert_mnemonic(VMIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
}

define_test(vmidt_3)
{
    setup_test_variables();

    parse_opcode(0xf3838001);
    assert_mnemonic(VMIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
}

define_test(vmidt_4)
{
    setup_test_variables();

    parse_opcode(0xf3838081);
    assert_mnemonic(VMIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
}

// vmzero mvd
define_test(vmzero_0)
{
    setup_test_variables();

    parse_opcode(0xf3860000);
    assert_mnemonic(VMZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Single});
}

define_test(vmzero_1)
{
    setup_test_variables();

    parse_opcode(0xf3860001);
    assert_mnemonic(VMZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Single});
}

define_test(vmzero_2)
{
    setup_test_variables();

    parse_opcode(0xf3860081);
    assert_mnemonic(VMZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
}

define_test(vmzero_3)
{
    setup_test_variables();

    parse_opcode(0xf3868001);
    assert_mnemonic(VMZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
}

define_test(vmzero_4)
{
    setup_test_variables();

    parse_opcode(0xf3868081);
    assert_mnemonic(VMZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
}

// vmone mvd
define_test(vmone_0)
{
    setup_test_variables();

    parse_opcode(0xf3870000);
    assert_mnemonic(VMONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Single});
}

define_test(vmone_1)
{
    setup_test_variables();

    parse_opcode(0xf3870001);
    assert_mnemonic(VMONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Single});
}

define_test(vmone_2)
{
    setup_test_variables();

    parse_opcode(0xf3870081);
    assert_mnemonic(VMONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
}

define_test(vmone_3)
{
    setup_test_variables();

    parse_opcode(0xf3878001);
    assert_mnemonic(VMONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
}

define_test(vmone_4)
{
    setup_test_variables();

    parse_opcode(0xf3878081);
    assert_mnemonic(VMONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
}

define_default_test_main();
