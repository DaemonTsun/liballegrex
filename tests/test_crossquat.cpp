
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vcrsp vd, vs, vt
define_test(vcrsp_0)
{
    setup_test_variables();

    parse_opcode(0xf2808000);
    assert_mnemonic(VCRSP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Triple});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Triple});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Triple});
}

define_test(vcrsp_1)
{
    setup_test_variables();

    parse_opcode(0xf2878301);
    assert_mnemonic(VCRSP);
    assert_argument_count(3);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Triple});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Triple});
}

// vqmul vd, vs, vt
define_test(vqmul_0)
{
    setup_test_variables();

    parse_opcode(0xf2808080);
    assert_mnemonic(VQMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::VFPU_Register);
    assert_argument_equals(1, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(2, argument_type::VFPU_Register);
    assert_argument_equals(2, vfpu_register, vfpu_register{0, vfpu_size::Quad});
}

define_test(vqmul_1)
{
    setup_test_variables();

    parse_opcode(0xf2878381);
    assert_mnemonic(VQMUL);
    assert_argument_count(3);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register, vfpu_register{1, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register, vfpu_register{3, vfpu_size::Quad});
    assert_argument_equals(2, vfpu_register, vfpu_register{7, vfpu_size::Quad});
}

define_default_test_main();
