
#include <t1/t1.hpp>
#include <math.h>
#include "tests/test_common.hpp"

// vpfxs [pfx, pfx, pfx, pfx]
define_test(vpfxs_0)
{
    setup_test_variables();

    parse_opcode(0xdc000000);
    assert_mnemonic(VPFXS);
    assert_argument_count(1);

    assert_argument_type(0, argument_type::VFPU_Prefix_Array);
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

    assert_argument_type(0, argument_type::VFPU_Prefix_Array);
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

    assert_argument_type(0, argument_type::VFPU_Prefix_Array);
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

    assert_argument_type(0, argument_type::VFPU_Prefix_Array);
    assert_argument_vfpu_prefix_equals(0, 0, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 1, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 2, vfpu_prefix::X);
    assert_argument_vfpu_prefix_equals(0, 3, vfpu_prefix::X);
}

// vpfxd [dpfx, dpfx, dpfx, dpfx]
define_test(vpfxd_0)
{
    setup_test_variables();

    parse_opcode(0xde000000);
    assert_mnemonic(VPFXD);
    assert_argument_count(1);

    assert_argument_type(0, argument_type::VFPU_Destination_Prefix_Array);
    assert_argument_vfpu_destination_prefix_equals(0, 0, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 1, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 2, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 3, vfpu_destination_prefix::DEFAULT);
}

define_test(vpfxd_1)
{
    setup_test_variables();

    parse_opcode(0xde0000e4);
    assert_mnemonic(VPFXD);
    assert_argument_count(1);

    assert_argument_vfpu_destination_prefix_equals(0, 0, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 1, vfpu_destination_prefix::CLAMP_0_1);
    assert_argument_vfpu_destination_prefix_equals(0, 2, vfpu_destination_prefix::X);
    assert_argument_vfpu_destination_prefix_equals(0, 3, vfpu_destination_prefix::CLAMP_NEG_1_1);
}

define_test(vpfxd_2)
{
    setup_test_variables();

    parse_opcode(0xde000fe4);
    assert_mnemonic(VPFXD);
    assert_argument_count(1);

    assert_argument_vfpu_destination_prefix_equals(0, 0, vfpu_destination_prefix::M);
    assert_argument_vfpu_destination_prefix_equals(0, 1, vfpu_destination_prefix::M_CLAMP_0_1);
    assert_argument_vfpu_destination_prefix_equals(0, 2, vfpu_destination_prefix::M_X);
    assert_argument_vfpu_destination_prefix_equals(0, 3, vfpu_destination_prefix::M_CLAMP_NEG_1_1);
}

define_test(vpfxd_3)
{
    setup_test_variables();

    parse_opcode(0xde800000);
    assert_mnemonic(VPFXD);
    assert_argument_count(1);

    assert_argument_vfpu_destination_prefix_equals(0, 0, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 1, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 2, vfpu_destination_prefix::DEFAULT);
    assert_argument_vfpu_destination_prefix_equals(0, 3, vfpu_destination_prefix::DEFAULT);
}

// viim vd, imm16
define_test(viim_0)
{
    setup_test_variables();

    parse_opcode(0xdf000000);
    assert_mnemonic(VIIM);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::Immediate_u16);
    assert_argument_equals(1, immediate_u16, immediate<u16>{0});
}

define_test(viim_1)
{
    setup_test_variables();

    parse_opcode(0xdf030001);
    assert_mnemonic(VIIM);
    assert_argument_count(2);

    assert_argument_equals(0, vfpu_register, vfpu_register{3, vfpu_size::Single});
    assert_argument_equals(1, immediate_u16, immediate<u16>{1});
}

// vfim vd, float16
define_test(vfim_0)
{
    setup_test_variables();

    parse_opcode(0xdf800000);
    assert_mnemonic(VFIM);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, argument_type::Immediate_float);
    // this is pretty hard to test because of precision
    assert_argument_equals(1, immediate_float, immediate<float>{0.0f});
}

define_test(vfim_1)
{
    setup_test_variables();

    parse_opcode(0xdf830001);
    assert_mnemonic(VFIM);
    assert_argument_count(2);

    assert_argument_equals(0, vfpu_register, vfpu_register{3, vfpu_size::Single});
    // good luck testing this without calling Float16ToFloat32
    // assert_argument_equals(1, immediate_float, immediate<float>{???});
}

define_default_test_main();
