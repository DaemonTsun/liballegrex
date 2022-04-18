
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// nop
define_test(nop)
{
    setup_test_variables();

    parse_opcode(0x00000000);

    assert_mnemonic(NOP);
    assert_argument_count(0);
}


define_default_test_main();
