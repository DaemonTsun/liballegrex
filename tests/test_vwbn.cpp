
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vwbn vd, vs
define_test(vwbn_0)
{
    setup_test_variables();

    parse_opcode(0xd3000000);
    assert_mnemonic(VWBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(2, immediate<u8>);
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vwbn_1)
{
    setup_test_variables();

    parse_opcode(0xd3050301);
    assert_mnemonic(VWBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(2, immediate<u8>{5});
}

define_test(vwbn_2)
{
    setup_test_variables();

    parse_opcode(0xd3000080);
    assert_mnemonic(VWBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vwbn_3)
{
    setup_test_variables();

    parse_opcode(0xd3008000);
    assert_mnemonic(VWBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(2, immediate<u8>{0});
}

define_test(vwbn_4)
{
    setup_test_variables();

    parse_opcode(0xd3008080);
    assert_mnemonic(VWBN);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(2, immediate<u8>{0});
}

define_default_test_main();
