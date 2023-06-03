
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// lvl vt, offset(reg)
define_test(lvl_0)
{
    setup_test_variables();

    parse_opcode(0xd4000000);
    assert_mnemonic(LVL);
    assert_argument_count(3);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::Memory_Offset);
    assert_argument_equals(1, memory_offset, memory_offset{0});

    assert_argument_type(2, argument_type::Base_Register);
    assert_argument_equals(2, base_register, base_register{mips_register::ZERO});
}

define_test(lvl_1)
{
    setup_test_variables();

    parse_opcode(0xd4620004);
    assert_mnemonic(LVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(lvl_2)
{
    setup_test_variables();

    parse_opcode(0xd4620005);
    assert_mnemonic(LVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(lvl_3)
{
    setup_test_variables();

    parse_opcode(0xd462fffc);
    assert_mnemonic(LVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{-4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

// lvr vt, offset(reg)
define_test(lvr_0)
{
    setup_test_variables();

    parse_opcode(0xd4000002);
    assert_mnemonic(LVR);
    assert_argument_count(3);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::Memory_Offset);
    assert_argument_equals(1, memory_offset, memory_offset{0});

    assert_argument_type(2, argument_type::Base_Register);
    assert_argument_equals(2, base_register, base_register{mips_register::ZERO});
}

define_test(lvr_1)
{
    setup_test_variables();

    parse_opcode(0xd4620006);
    assert_mnemonic(LVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(lvr_2)
{
    setup_test_variables();

    parse_opcode(0xd4620007);
    assert_mnemonic(LVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(lvr_3)
{
    setup_test_variables();

    parse_opcode(0xd462fffe);
    assert_mnemonic(LVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{-4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

// svl vt, offset(reg)
define_test(svl_0)
{
    setup_test_variables();

    parse_opcode(0xf4000000);
    assert_mnemonic(SVL);
    assert_argument_count(3);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::Memory_Offset);
    assert_argument_equals(1, memory_offset, memory_offset{0});

    assert_argument_type(2, argument_type::Base_Register);
    assert_argument_equals(2, base_register, base_register{mips_register::ZERO});
}

define_test(svl_1)
{
    setup_test_variables();

    parse_opcode(0xf4620004);
    assert_mnemonic(SVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(svl_2)
{
    setup_test_variables();

    parse_opcode(0xf4620005);
    assert_mnemonic(SVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(svl_3)
{
    setup_test_variables();

    parse_opcode(0xf462fffc);
    assert_mnemonic(SVL);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{-4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

// svr vt, offset(reg)
define_test(svr_0)
{
    setup_test_variables();

    parse_opcode(0xf4000002);
    assert_mnemonic(SVR);
    assert_argument_count(3);

    assert_argument_type(0, argument_type::VFPU_Register);
    assert_argument_equals(0, vfpu_register, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, argument_type::Memory_Offset);
    assert_argument_equals(1, memory_offset, memory_offset{0});

    assert_argument_type(2, argument_type::Base_Register);
    assert_argument_equals(2, base_register, base_register{mips_register::ZERO});
}

define_test(svr_1)
{
    setup_test_variables();

    parse_opcode(0xf4620006);
    assert_mnemonic(SVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(svr_2)
{
    setup_test_variables();

    parse_opcode(0xf4620007);
    assert_mnemonic(SVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_test(svr_3)
{
    setup_test_variables();

    parse_opcode(0xf462fffe);
    assert_mnemonic(SVR);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset, memory_offset{-4});
    assert_argument_equals(2, base_register, base_register{mips_register::V1});
}

define_default_test_main();
