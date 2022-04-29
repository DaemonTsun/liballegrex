
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vcmovt vd, vs
define_test(vcmovt_0)
{
    setup_test_variables();

    parse_opcode(0xd2a00000);
    assert_mnemonic(VCMOVT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, immediate<u8>);
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovt_1)
{
    setup_test_variables();

    parse_opcode(0xd2a50301);
    assert_mnemonic(VCMOVT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate<u8>{5});
}

define_test(vcmovt_2)
{
    setup_test_variables();

    parse_opcode(0xd2a00080);
    assert_mnemonic(VCMOVT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovt_3)
{
    setup_test_variables();

    parse_opcode(0xd2a08000);
    assert_mnemonic(VCMOVT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovt_4)
{
    setup_test_variables();

    parse_opcode(0xd2a08080);
    assert_mnemonic(VCMOVT);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovt_5)
{
    setup_test_variables();

    parse_opcode(0xd2a70301);
    assert_mnemonic(VCMOVT);
    assert_argument_count(1);

    assert_argument_type(0, error);
    /*
    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate<u8>{7});
    */
}

// vcmovf vd, vs
define_test(vcmovf_0)
{
    setup_test_variables();

    parse_opcode(0xd2a80000);
    assert_mnemonic(VCMOVF);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, immediate<u8>);
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovf_1)
{
    setup_test_variables();

    parse_opcode(0xd2ad0301);
    assert_mnemonic(VCMOVF);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate<u8>{5});
}

define_test(vcmovf_2)
{
    setup_test_variables();

    parse_opcode(0xd2a80080);
    assert_mnemonic(VCMOVF);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovf_3)
{
    setup_test_variables();

    parse_opcode(0xd2a88000);
    assert_mnemonic(VCMOVF);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovf_4)
{
    setup_test_variables();

    parse_opcode(0xd2a88080);
    assert_mnemonic(VCMOVF);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vcmovf_5)
{
    setup_test_variables();

    parse_opcode(0xd2af0301);
    assert_mnemonic(VCMOVF);
    assert_argument_count(1);

    assert_argument_type(0, error);
    /*
    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate<u8>{7});
    */
}

define_default_test_main();
