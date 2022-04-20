
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// mfc0 rt, rd, sel
define_test(mfc0)
{
    setup_test_variables();

    parse_opcode(0x40000000);
    assert_mnemonic(MFC0);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, coprocessor_register);
    assert_argument_equals(1, coprocessor_register{0, 0});
}

define_default_test_main();
