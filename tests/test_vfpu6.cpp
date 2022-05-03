
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vmmul mvd, xvs, mvt
define_test(vmmul_0)
{
    setup_test_variables();

    parse_opcode(0xf0000080);
    assert_mnemonic(VMMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Pair});

    assert_argument_type(1, vfpu_matrix);
    assert_argument_equals(1, vfpu_matrix{32, vfpu_size::Pair});

    assert_argument_type(2, vfpu_matrix);
    assert_argument_equals(2, vfpu_matrix{0, vfpu_size::Pair});
}

define_test(vmmul_1)
{
    setup_test_variables();

    parse_opcode(0xf0030281);
    assert_mnemonic(VMMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_matrix{34, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_matrix{3, vfpu_size::Pair});
}

define_test(vmmul_2)
{
    setup_test_variables();

    parse_opcode(0xf0038201);
    assert_mnemonic(VMMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_matrix{34, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_matrix{3, vfpu_size::Triple});
}

define_test(vmmul_3)
{
    setup_test_variables();

    parse_opcode(0xf0038281);
    assert_mnemonic(VMMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_matrix{34, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_matrix{3, vfpu_size::Quad});
}

// vmscl mvd, mvs, vt(single)
define_test(vmscl_0)
{
    setup_test_variables();

    parse_opcode(0xf2000080);
    assert_mnemonic(VMSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_type(0, vfpu_matrix);
    assert_argument_equals(0, vfpu_matrix{0, vfpu_size::Pair});

    assert_argument_type(1, vfpu_matrix);
    assert_argument_equals(1, vfpu_matrix{0, vfpu_size::Pair});

    assert_argument_type(2, vfpu_register);
    assert_argument_equals(2, vfpu_register{0, vfpu_size::Single});
}

define_test(vmscl_1)
{
    setup_test_variables();

    parse_opcode(0xf2030281);
    assert_mnemonic(VMSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_matrix{2, vfpu_size::Pair});
    assert_argument_equals(2, vfpu_register{3, vfpu_size::Single});
}

define_test(vmscl_2)
{
    setup_test_variables();

    parse_opcode(0xf2038201);
    assert_mnemonic(VMSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_matrix{2, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register{3, vfpu_size::Single});
}

define_test(vmscl_3)
{
    setup_test_variables();

    parse_opcode(0xf2038281);
    assert_mnemonic(VMSCL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_matrix{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_matrix{2, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register{3, vfpu_size::Single});
}

// vrot [rot, ...]
define_test(vrot_0)
{
    setup_test_variables();

    parse_opcode(0xf3a00000);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, vfpu_rotation_array);
    assert_argument_vfpu_rotation_count(2, 1);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::COS);
}

define_test(vrot_1)
{
    setup_test_variables();

    parse_opcode(0xf3a00381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::COS);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::SIN);
}

define_test(vrot_2)
{
    setup_test_variables();

    parse_opcode(0xf3a10381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::SIN);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::COS);
}

define_test(vrot_3)
{
    setup_test_variables();

    parse_opcode(0xf3a20381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::SIN);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::ZERO);
}

define_test(vrot_4)
{
    setup_test_variables();

    parse_opcode(0xf3a30381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::SIN);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::ZERO);
}

define_test(vrot_5)
{
    setup_test_variables();

    parse_opcode(0xf3a40381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::COS);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::SIN);
}

define_test(vrot_6)
{
    setup_test_variables();

    parse_opcode(0xf3a50381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::SIN);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::COS);
}

define_test(vrot_7)
{
    setup_test_variables();

    parse_opcode(0xf3a60381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::ZERO);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::SIN);
}

define_test(vrot_8)
{
    setup_test_variables();

    parse_opcode(0xf3a70381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::ZERO);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::SIN);
}

define_test(vrot_9)
{
    setup_test_variables();

    parse_opcode(0xf3a80381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::COS);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::ZERO);
}

define_test(vrot_10)
{
    setup_test_variables();

    parse_opcode(0xf3a90381);
    assert_mnemonic(VROT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});

    assert_argument_vfpu_rotation_count(2, 2);
    assert_argument_vfpu_rotation_equals(2, 0, vfpu_rotation::ZERO);
    assert_argument_vfpu_rotation_equals(2, 1, vfpu_rotation::COS);
}

// repeat for a-f, triple, quad, ... lets just assume it works :^)

define_default_test_main();
