
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vpfxs [pfx, pfx, pfx, pfx]
define_test(vpfxs_0)
{
    setup_test_variables();

    parse_opcode(0xdc000000);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_type(0, vfpu_prefix_array);
    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::X);
}

define_test(vpfxs_1)
{
    setup_test_variables();

    parse_opcode(0xdc0000e4);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::Y);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::Z);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::W);
}

define_test(vpfxs_2)
{
    setup_test_variables();

    parse_opcode(0xdc0c0ae4);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::ABS_Y);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::NEG_Z);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::NEG_ABS_W);
}

define_test(vpfxs_3)
{
    setup_test_variables();

    parse_opcode(0xdc00f0e4);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::ZERO);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::ONE);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::TWO);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::HALF);
}

define_test(vpfxs_4)
{
    setup_test_variables();

    parse_opcode(0xdc00ffe4);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::THREE);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::THIRD);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::FOURTH);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::SIXTH);
}

define_test(vpfxs_5)
{
    setup_test_variables();

    parse_opcode(0xdc800000);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_type(0, vfpu_prefix_array);
    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::X);
}

// vpfxt [pfx, pfx, pfx, pfx]
define_test(vpfxt_0)
{
    setup_test_variables();

    parse_opcode(0xdd000000);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_type(0, vfpu_prefix_array);
    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::X);
}

define_test(vpfxt_1)
{
    setup_test_variables();

    parse_opcode(0xdd0000e4);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::Y);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::Z);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::W);
}

define_test(vpfxt_2)
{
    setup_test_variables();

    parse_opcode(0xdd0c0ae4);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::ABS_Y);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::NEG_Z);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::NEG_ABS_W);
}

define_test(vpfxt_3)
{
    setup_test_variables();

    parse_opcode(0xdd00f0e4);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::ZERO);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::ONE);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::TWO);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::HALF);
}

define_test(vpfxt_4)
{
    setup_test_variables();

    parse_opcode(0xdd00ffe4);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::THREE);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::THIRD);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::FOURTH);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::SIXTH);
}

define_test(vpfxt_5)
{
    setup_test_variables();

    parse_opcode(0xdd800000);
    assert_mnemonic(VPFXT);
    assert_argument_count(1);

    assert_argument_type(0, vfpu_prefix_array);
    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::X);
}

define_default_test_main();
