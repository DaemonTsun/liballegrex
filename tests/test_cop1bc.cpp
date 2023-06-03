
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// bc1f offset, cc
define_test(bc1f_0)
{
    setup_test_variables();

    parse_opcode(0x45000000);
    assert_mnemonic(BC1F);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{4}); // always adds +4 (sizeof(u32))

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{0});
}

define_test(bc1f_1)
{
    setup_test_variables();

    parse_opcode(0x45040001);
    assert_mnemonic(BC1F);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{8});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{1});
}

define_test(bc1f_2)
{
    setup_test_variables();

    parse_opcode(0x4500FFFF);
    assert_mnemonic(BC1F);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0}); // signed -1 (-4) = 0
}

define_test(bc1f_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x45000000);
    assert_mnemonic(BC1F);
    assert_argument_count(2);

    // relative branch, so have to add address
    assert_argument_equals(0, branch_address, branch_address{0x00000014});
}

// bc1t offset, cc
define_test(bc1t_0)
{
    setup_test_variables();

    parse_opcode(0x45010000);
    assert_mnemonic(BC1T);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{4});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{0});
}

define_test(bc1t_1)
{
    setup_test_variables();

    parse_opcode(0x45050001);
    assert_mnemonic(BC1T);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{8});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{1});
}

define_test(bc1t_2)
{
    setup_test_variables();

    parse_opcode(0x4501FFFF);
    assert_mnemonic(BC1T);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0});
}

define_test(bc1t_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x45010000);
    assert_mnemonic(BC1T);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0x00000014});
}

// bc1fl offset, cc
define_test(bc1fl_0)
{
    setup_test_variables();

    parse_opcode(0x45020000);
    assert_mnemonic(BC1FL);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{4});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{0});
}

define_test(bc1fl_1)
{
    setup_test_variables();

    parse_opcode(0x45060001);
    assert_mnemonic(BC1FL);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{8});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{1});
}

define_test(bc1fl_2)
{
    setup_test_variables();

    parse_opcode(0x4502FFFF);
    assert_mnemonic(BC1FL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0});
}

define_test(bc1fl_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x45020000);
    assert_mnemonic(BC1FL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0x00000014});
}

// bc1tl offset, cc
define_test(bc1tl_0)
{
    setup_test_variables();

    parse_opcode(0x45030000);
    assert_mnemonic(BC1TL);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{4});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{0});
}

define_test(bc1tl_1)
{
    setup_test_variables();

    parse_opcode(0x45070001);
    assert_mnemonic(BC1TL);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::Branch_Address);
    assert_argument_equals(0, branch_address, branch_address{8});

    assert_argument_type(1, argument_type::Condition_Code);
    assert_argument_equals(1, condition_code, condition_code{1});
}

define_test(bc1tl_2)
{
    setup_test_variables();

    parse_opcode(0x4503FFFF);
    assert_mnemonic(BC1TL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0});
}

define_test(bc1tl_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x45030000);
    assert_mnemonic(BC1TL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address, branch_address{0x00000014});
}

define_default_test_main();
