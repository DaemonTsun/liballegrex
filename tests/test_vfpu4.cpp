
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vmov vd, vs
define_test(vmov_0)
{
    setup_test_variables();

    parse_opcode(0xd0000000);
    assert_mnemonic(VMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vmov_1)
{
    setup_test_variables();

    parse_opcode(0xd0000301);
    assert_mnemonic(VMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vmov_2)
{
    setup_test_variables();

    parse_opcode(0xd0000080);
    assert_mnemonic(VMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vmov_3)
{
    setup_test_variables();

    parse_opcode(0xd0008000);
    assert_mnemonic(VMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vmov_4)
{
    setup_test_variables();

    parse_opcode(0xd0008080);
    assert_mnemonic(VMOV);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vabs vd, vs
define_test(vabs_0)
{
    setup_test_variables();

    parse_opcode(0xd0010000);
    assert_mnemonic(VABS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vabs_1)
{
    setup_test_variables();

    parse_opcode(0xd0010301);
    assert_mnemonic(VABS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vabs_2)
{
    setup_test_variables();

    parse_opcode(0xd0010080);
    assert_mnemonic(VABS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vabs_3)
{
    setup_test_variables();

    parse_opcode(0xd0018000);
    assert_mnemonic(VABS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vabs_4)
{
    setup_test_variables();

    parse_opcode(0xd0018080);
    assert_mnemonic(VABS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vneg vd, vs
define_test(vneg_0)
{
    setup_test_variables();

    parse_opcode(0xd0020000);
    assert_mnemonic(VNEG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vneg_1)
{
    setup_test_variables();

    parse_opcode(0xd0020301);
    assert_mnemonic(VNEG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vneg_2)
{
    setup_test_variables();

    parse_opcode(0xd0020080);
    assert_mnemonic(VNEG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vneg_3)
{
    setup_test_variables();

    parse_opcode(0xd0028000);
    assert_mnemonic(VNEG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vneg_4)
{
    setup_test_variables();

    parse_opcode(0xd0028080);
    assert_mnemonic(VNEG);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vidt vd
define_test(vidt_0)
{
    setup_test_variables();

    parse_opcode(0xd0030000);
    assert_mnemonic(VIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vidt_1)
{
    setup_test_variables();

    parse_opcode(0xd0030301);
    assert_mnemonic(VIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vidt_2)
{
    setup_test_variables();

    parse_opcode(0xd0030080);
    assert_mnemonic(VIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vidt_3)
{
    setup_test_variables();

    parse_opcode(0xd0038000);
    assert_mnemonic(VIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vidt_4)
{
    setup_test_variables();

    parse_opcode(0xd0038080);
    assert_mnemonic(VIDT);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vsat0 vd, vs
define_test(vsat0_0)
{
    setup_test_variables();

    parse_opcode(0xd0040000);
    assert_mnemonic(VSAT0);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vsat0_1)
{
    setup_test_variables();

    parse_opcode(0xd0040301);
    assert_mnemonic(VSAT0);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vsat0_2)
{
    setup_test_variables();

    parse_opcode(0xd0040080);
    assert_mnemonic(VSAT0);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsat0_3)
{
    setup_test_variables();

    parse_opcode(0xd0048000);
    assert_mnemonic(VSAT0);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsat0_4)
{
    setup_test_variables();

    parse_opcode(0xd0048080);
    assert_mnemonic(VSAT0);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vsat1 vd, vs
define_test(vsat1_0)
{
    setup_test_variables();

    parse_opcode(0xd0050000);
    assert_mnemonic(VSAT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vsat1_1)
{
    setup_test_variables();

    parse_opcode(0xd0050301);
    assert_mnemonic(VSAT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vsat1_2)
{
    setup_test_variables();

    parse_opcode(0xd0050080);
    assert_mnemonic(VSAT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsat1_3)
{
    setup_test_variables();

    parse_opcode(0xd0058000);
    assert_mnemonic(VSAT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsat1_4)
{
    setup_test_variables();

    parse_opcode(0xd0058080);
    assert_mnemonic(VSAT1);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vzero vd
define_test(vzero_0)
{
    setup_test_variables();

    parse_opcode(0xd0060000);
    assert_mnemonic(VZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vzero_1)
{
    setup_test_variables();

    parse_opcode(0xd0060301);
    assert_mnemonic(VZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vzero_2)
{
    setup_test_variables();

    parse_opcode(0xd0060080);
    assert_mnemonic(VZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vzero_3)
{
    setup_test_variables();

    parse_opcode(0xd0068000);
    assert_mnemonic(VZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vzero_4)
{
    setup_test_variables();

    parse_opcode(0xd0068080);
    assert_mnemonic(VZERO);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vone vd
define_test(vone_0)
{
    setup_test_variables();

    parse_opcode(0xd0070000);
    assert_mnemonic(VONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vone_1)
{
    setup_test_variables();

    parse_opcode(0xd0070301);
    assert_mnemonic(VONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vone_2)
{
    setup_test_variables();

    parse_opcode(0xd0070080);
    assert_mnemonic(VONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vone_3)
{
    setup_test_variables();

    parse_opcode(0xd0078000);
    assert_mnemonic(VONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vone_4)
{
    setup_test_variables();

    parse_opcode(0xd0078080);
    assert_mnemonic(VONE);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vrcp vd, vs
define_test(vrcp_0)
{
    setup_test_variables();

    parse_opcode(0xd0100000);
    assert_mnemonic(VRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vrcp_1)
{
    setup_test_variables();

    parse_opcode(0xd0100301);
    assert_mnemonic(VRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vrcp_2)
{
    setup_test_variables();

    parse_opcode(0xd0100080);
    assert_mnemonic(VRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrcp_3)
{
    setup_test_variables();

    parse_opcode(0xd0108000);
    assert_mnemonic(VRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrcp_4)
{
    setup_test_variables();

    parse_opcode(0xd0108080);
    assert_mnemonic(VRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vrsq vd, vs
define_test(vrsq_0)
{
    setup_test_variables();

    parse_opcode(0xd0110000);
    assert_mnemonic(VRSQ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vrsq_1)
{
    setup_test_variables();

    parse_opcode(0xd0110301);
    assert_mnemonic(VRSQ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vrsq_2)
{
    setup_test_variables();

    parse_opcode(0xd0110080);
    assert_mnemonic(VRSQ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrsq_3)
{
    setup_test_variables();

    parse_opcode(0xd0118000);
    assert_mnemonic(VRSQ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrsq_4)
{
    setup_test_variables();

    parse_opcode(0xd0118080);
    assert_mnemonic(VRSQ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vsin vd, vs
define_test(vsin_0)
{
    setup_test_variables();

    parse_opcode(0xd0120000);
    assert_mnemonic(VSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vsin_1)
{
    setup_test_variables();

    parse_opcode(0xd0120301);
    assert_mnemonic(VSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vsin_2)
{
    setup_test_variables();

    parse_opcode(0xd0120080);
    assert_mnemonic(VSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsin_3)
{
    setup_test_variables();

    parse_opcode(0xd0128000);
    assert_mnemonic(VSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsin_4)
{
    setup_test_variables();

    parse_opcode(0xd0128080);
    assert_mnemonic(VSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vcos vd, vs
define_test(vcos_0)
{
    setup_test_variables();

    parse_opcode(0xd0130000);
    assert_mnemonic(VCOS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vcos_1)
{
    setup_test_variables();

    parse_opcode(0xd0130301);
    assert_mnemonic(VCOS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vcos_2)
{
    setup_test_variables();

    parse_opcode(0xd0130080);
    assert_mnemonic(VCOS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vcos_3)
{
    setup_test_variables();

    parse_opcode(0xd0138000);
    assert_mnemonic(VCOS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vcos_4)
{
    setup_test_variables();

    parse_opcode(0xd0138080);
    assert_mnemonic(VCOS);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vexp2 vd, vs
define_test(vexp2_0)
{
    setup_test_variables();

    parse_opcode(0xd0140000);
    assert_mnemonic(VEXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vexp2_1)
{
    setup_test_variables();

    parse_opcode(0xd0140301);
    assert_mnemonic(VEXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vexp2_2)
{
    setup_test_variables();

    parse_opcode(0xd0140080);
    assert_mnemonic(VEXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vexp2_3)
{
    setup_test_variables();

    parse_opcode(0xd0148000);
    assert_mnemonic(VEXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vexp2_4)
{
    setup_test_variables();

    parse_opcode(0xd0148080);
    assert_mnemonic(VEXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vlog2 vd, vs
define_test(vlog2_0)
{
    setup_test_variables();

    parse_opcode(0xd0150000);
    assert_mnemonic(VLOG2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vlog2_1)
{
    setup_test_variables();

    parse_opcode(0xd0150301);
    assert_mnemonic(VLOG2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vlog2_2)
{
    setup_test_variables();

    parse_opcode(0xd0150080);
    assert_mnemonic(VLOG2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vlog2_3)
{
    setup_test_variables();

    parse_opcode(0xd0158000);
    assert_mnemonic(VLOG2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vlog2_4)
{
    setup_test_variables();

    parse_opcode(0xd0158080);
    assert_mnemonic(VLOG2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vsqrt vd, vs
define_test(vsqrt_0)
{
    setup_test_variables();

    parse_opcode(0xd0160000);
    assert_mnemonic(VSQRT);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vsqrt_1)
{
    setup_test_variables();

    parse_opcode(0xd0160301);
    assert_mnemonic(VSQRT);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vsqrt_2)
{
    setup_test_variables();

    parse_opcode(0xd0160080);
    assert_mnemonic(VSQRT);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsqrt_3)
{
    setup_test_variables();

    parse_opcode(0xd0168000);
    assert_mnemonic(VSQRT);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsqrt_4)
{
    setup_test_variables();

    parse_opcode(0xd0168080);
    assert_mnemonic(VSQRT);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vasin vd, vs
define_test(vasin_0)
{
    setup_test_variables();

    parse_opcode(0xd0170000);
    assert_mnemonic(VASIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vasin_1)
{
    setup_test_variables();

    parse_opcode(0xd0170301);
    assert_mnemonic(VASIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vasin_2)
{
    setup_test_variables();

    parse_opcode(0xd0170080);
    assert_mnemonic(VASIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vasin_3)
{
    setup_test_variables();

    parse_opcode(0xd0178000);
    assert_mnemonic(VASIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vasin_4)
{
    setup_test_variables();

    parse_opcode(0xd0178080);
    assert_mnemonic(VASIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vnrcp vd, vs
define_test(vnrcp_0)
{
    setup_test_variables();

    parse_opcode(0xd0180000);
    assert_mnemonic(VNRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vnrcp_1)
{
    setup_test_variables();

    parse_opcode(0xd0180301);
    assert_mnemonic(VNRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vnrcp_2)
{
    setup_test_variables();

    parse_opcode(0xd0180080);
    assert_mnemonic(VNRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vnrcp_3)
{
    setup_test_variables();

    parse_opcode(0xd0188000);
    assert_mnemonic(VNRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vnrcp_4)
{
    setup_test_variables();

    parse_opcode(0xd0188080);
    assert_mnemonic(VNRCP);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vnsin vd, vs
define_test(vnsin_0)
{
    setup_test_variables();

    parse_opcode(0xd01a0000);
    assert_mnemonic(VNSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vnsin_1)
{
    setup_test_variables();

    parse_opcode(0xd01a0301);
    assert_mnemonic(VNSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vnsin_2)
{
    setup_test_variables();

    parse_opcode(0xd01a0080);
    assert_mnemonic(VNSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vnsin_3)
{
    setup_test_variables();

    parse_opcode(0xd01a8000);
    assert_mnemonic(VNSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vnsin_4)
{
    setup_test_variables();

    parse_opcode(0xd01a8080);
    assert_mnemonic(VNSIN);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vrexp2 vd, vs
define_test(vrexp2_0)
{
    setup_test_variables();

    parse_opcode(0xd01c0000);
    assert_mnemonic(VREXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vrexp2_1)
{
    setup_test_variables();

    parse_opcode(0xd01c0301);
    assert_mnemonic(VREXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vrexp2_2)
{
    setup_test_variables();

    parse_opcode(0xd01c0080);
    assert_mnemonic(VREXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrexp2_3)
{
    setup_test_variables();

    parse_opcode(0xd01c8000);
    assert_mnemonic(VREXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrexp2_4)
{
    setup_test_variables();

    parse_opcode(0xd01c8080);
    assert_mnemonic(VREXP2);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
