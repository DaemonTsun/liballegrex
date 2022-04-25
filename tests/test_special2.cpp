
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// halt
define_test(halt)
{
    setup_test_variables();

    parse_opcode(0x70000000);

    assert_mnemonic(HALT);
    assert_argument_count(0);
}

// mfic
define_test(mfic)
{
    setup_test_variables();

    parse_opcode(0x70000024);

    assert_mnemonic(MFIC);
    assert_argument_count(0);
}

// mtic
define_test(mtic)
{
    setup_test_variables();

    parse_opcode(0x70000026);

    assert_mnemonic(MTIC);
    assert_argument_count(0);
}

define_default_test_main();
