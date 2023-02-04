
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vmul vd, vs, vt
define_test(vmul_0)
{
    setup_test_variables();

    parse_opcode(0x64000000);
    assert_mnemonic(VMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vmul_1)
{
    setup_test_variables();

    parse_opcode(0x64070301);
    assert_mnemonic(VMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register{7, vfpu_size::Single});
}

define_test(vmul_2)
{
    setup_test_variables();

    parse_opcode(0x64000080);
    assert_mnemonic(VMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Pair});
}

define_test(vmul_3)
{
    setup_test_variables();

    parse_opcode(0x64008000);
    assert_mnemonic(VMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Triple});
}

define_test(vmul_4)
{
    setup_test_variables();

    parse_opcode(0x64008080);
    assert_mnemonic(VMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Quad});
}

// vdot vd, vs, vt
define_test(vdot_0)
{
    setup_test_variables();

    parse_opcode(0x64800000);
    assert_mnemonic(VDOT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vdot_1)
{
    setup_test_variables();

    parse_opcode(0x64870301);
    assert_mnemonic(VDOT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register{7, vfpu_size::Single});
}

define_test(vdot_2)
{
    setup_test_variables();

    parse_opcode(0x64800080);
    assert_mnemonic(VDOT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Pair});
}

define_test(vdot_3)
{
    setup_test_variables();

    parse_opcode(0x64808000);
    assert_mnemonic(VDOT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Triple});
}

define_test(vdot_4)
{
    setup_test_variables();

    parse_opcode(0x64808080);
    assert_mnemonic(VDOT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Quad});
}

// vscl vd, vs, vt
define_test(vscl_0)
{
    setup_test_variables();

    parse_opcode(0x65000000);
    assert_mnemonic(VSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vscl_1)
{
    setup_test_variables();

    parse_opcode(0x65070301);
    assert_mnemonic(VSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register{7, vfpu_size::Single});
}

define_test(vscl_2)
{
    setup_test_variables();

    parse_opcode(0x65000080);
    assert_mnemonic(VSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vscl_3)
{
    setup_test_variables();

    parse_opcode(0x65008000);
    assert_mnemonic(VSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vscl_4)
{
    setup_test_variables();

    parse_opcode(0x65008080);
    assert_mnemonic(VSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

// vhdp vd, vs, vt
define_test(vhdp_0)
{
    setup_test_variables();

    parse_opcode(0x66000000);
    assert_mnemonic(VHDP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vhdp_1)
{
    setup_test_variables();

    parse_opcode(0x66070301);
    assert_mnemonic(VHDP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register{7, vfpu_size::Single});
}

define_test(vhdp_2)
{
    setup_test_variables();

    parse_opcode(0x66000080);
    assert_mnemonic(VHDP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Pair});
}

define_test(vhdp_3)
{
    setup_test_variables();

    parse_opcode(0x66008000);
    assert_mnemonic(VHDP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Triple});
}

define_test(vhdp_4)
{
    setup_test_variables();

    parse_opcode(0x66008080);
    assert_mnemonic(VHDP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Quad});
}

// vcrs vd, vs, vt
define_test(vcrs_0)
{
    setup_test_variables();

    parse_opcode(0x66800000);
    assert_mnemonic(VCRS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, invalid_argument);
}

define_test(vcrs_1)
{
    setup_test_variables();

    parse_opcode(0x66870301);
    assert_mnemonic(VCRS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, invalid_argument);
}

define_test(vcrs_2)
{
    setup_test_variables();

    parse_opcode(0x66800080);
    assert_mnemonic(VCRS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_type(0, invalid_argument);
}

define_test(vcrs_3)
{
    setup_test_variables();

    parse_opcode(0x66808000);
    assert_mnemonic(VCRS);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Triple});
}

define_test(vcrs_4)
{
    setup_test_variables();

    parse_opcode(0x66808080);
    assert_mnemonic(VCRS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_type(0, invalid_argument);
}

// vdet vd, vs, vt
define_test(vdet_0)
{
    setup_test_variables();

    parse_opcode(0x67000000);
    assert_mnemonic(VDET);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vdet_1)
{
    setup_test_variables();

    parse_opcode(0x67070301);
    assert_mnemonic(VDET);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, vfpu_register{7, vfpu_size::Single});
}

define_test(vdet_2)
{
    setup_test_variables();

    parse_opcode(0x67000080);
    assert_mnemonic(VDET);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Pair});
}

define_test(vdet_3)
{
    setup_test_variables();

    parse_opcode(0x67008000);
    assert_mnemonic(VDET);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Triple});
}

define_test(vdet_4)
{
    setup_test_variables();

    parse_opcode(0x67008080);
    assert_mnemonic(VDET);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
