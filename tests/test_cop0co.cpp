
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// tlbr
define_test(tlbr)
{
    setup_test_variables();

    parse_opcode(0x42000001);
    assert_mnemonic(TLBR);
    assert_argument_count(0);
}

// tlbwi
define_test(tlbwi)
{
    setup_test_variables();

    parse_opcode(0x42000002);
    assert_mnemonic(TLBWI);
    assert_argument_count(0);
}

// tlbwr
define_test(tlbwr)
{
    setup_test_variables();

    parse_opcode(0x42000006);
    assert_mnemonic(TLBWR);
    assert_argument_count(0);
}

// tlbp
define_test(tlbp)
{
    setup_test_variables();

    parse_opcode(0x42000008);
    assert_mnemonic(TLBP);
    assert_argument_count(0);
}

// eret
define_test(eret)
{
    setup_test_variables();

    parse_opcode(0x42000018);
    assert_mnemonic(ERET);
    assert_argument_count(0);
}

// iack
define_test(iack)
{
    setup_test_variables();

    parse_opcode(0x42000019);
    assert_mnemonic(IACK);
    assert_argument_count(0);
}

// deret
define_test(deret)
{
    setup_test_variables();

    parse_opcode(0x4200001f);
    assert_mnemonic(DERET);
    assert_argument_count(0);
}

// wait
define_test(wait)
{
    setup_test_variables();

    parse_opcode(0x42000020);
    assert_mnemonic(WAIT);
    assert_argument_count(0);
}

define_default_test_main();
