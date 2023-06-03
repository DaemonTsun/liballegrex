
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// ext rt, rs, pos, size
define_test(ext_0)
{
    setup_test_variables();

    parse_opcode(0x7c000000); 

    assert_mnemonic(EXT);
    assert_argument_count(4);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::ZERO);

    assert_argument_type(2, argument_type::Bitfield_Pos);
    assert_argument_equals(2, bitfield_pos, bitfield_pos{0});

    assert_argument_type(3, argument_type::Bitfield_Size);
    assert_argument_equals(3, bitfield_size, bitfield_size{1});
}

define_test(ext_1)
{
    setup_test_variables();

    parse_opcode(0x7c61ff80); 

    assert_mnemonic(EXT);
    assert_argument_count(4);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::AT);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::V1);

    assert_argument_type(2, argument_type::Bitfield_Pos);
    assert_argument_equals(2, bitfield_pos, bitfield_pos{30});

    assert_argument_type(3, argument_type::Bitfield_Size);
    assert_argument_equals(3, bitfield_size, bitfield_size{32});
}

// ins rt, rs, pos, size
define_test(ins_0)
{
    setup_test_variables();

    parse_opcode(0x7c000004); 

    assert_mnemonic(INS);
    assert_argument_count(4);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::ZERO);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::ZERO);

    assert_argument_type(2, argument_type::Bitfield_Pos);
    assert_argument_equals(2, bitfield_pos, bitfield_pos{0});

    assert_argument_type(3, argument_type::Bitfield_Size);
    assert_argument_equals(3, bitfield_size, bitfield_size{1});
}

define_test(ins_1)
{
    setup_test_variables();

    parse_opcode(0x7c61ff84); 

    assert_mnemonic(INS);
    assert_argument_count(4);

    assert_argument_type(0, argument_type::MIPS_Register);
    assert_argument_equals(0, mips_register, mips_register::AT);

    assert_argument_type(1, argument_type::MIPS_Register);
    assert_argument_equals(1, mips_register, mips_register::V1);

    assert_argument_type(2, argument_type::Bitfield_Pos);
    assert_argument_equals(2, bitfield_pos, bitfield_pos{30});

    assert_argument_type(3, argument_type::Bitfield_Size);
    assert_argument_equals(3, bitfield_size, bitfield_size{2});
}

// rdhwr
define_test(rdhwr)
{
    setup_test_variables();

    parse_opcode(0x7c00003b);

    assert_mnemonic(RDHWR);
    assert_argument_count(0);
}

define_default_test_main();
