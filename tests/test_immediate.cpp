
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// j address
define_test(j_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08000000);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_type(0, jump_address);
    assert_argument_equals(0, jump_address{0});
}

define_test(j_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08000001);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{4});
}

define_test(j_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x03fffffc});
}

define_test(j_3)
{
    setup_test_variables();

    inst.address = 0x10000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x13fffffc});
}

define_test(j_4)
{
    setup_test_variables();

    inst.address = 0xf0000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0xf3fffffc});
}

// jal address
define_test(jal_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0c000000);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_type(0, jump_address);
    assert_argument_equals(0, jump_address{0});
}

define_test(jal_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0c000001);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{4});
}

define_test(jal_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x03fffffc});
}

define_test(jal_3)
{
    setup_test_variables();

    inst.address = 0x10000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x13fffffc});
}

define_test(jal_4)
{
    setup_test_variables();

    inst.address = 0xf0000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0xf3fffffc});
}

define_default_test_main();
