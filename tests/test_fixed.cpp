
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

define_test(nop)
{
    setup_test_variables();

    parse_opcode(0x00000000);

    assert_mnemonic(NOP);
}


define_default_test_main();
