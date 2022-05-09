
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vnop
define_test(vnop)
{
    setup_test_variables();

    parse_opcode(0xffff0000);
    assert_mnemonic(VNOP);
    assert_argument_count(0);
}

// vsync
define_test(vsync)
{
    setup_test_variables();

    parse_opcode(0xffff0320);
    assert_mnemonic(VSYNC);
    assert_argument_count(0);
}

// vflush
define_test(vflush)
{
    setup_test_variables();

    parse_opcode(0xffff040d);
    assert_mnemonic(VFLUSH);
    assert_argument_count(0);
}

define_default_test_main();
