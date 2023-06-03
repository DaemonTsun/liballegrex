#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// cvt.s.w fd, fs
define_test(cvt_s_w_0)
{
    setup_test_variables();

    parse_opcode(0x46800020);
    assert_mnemonic(CVT_S_W);
    assert_argument_count(2);

    assert_argument_type(0, argument_type::MIPS_FPU_Register);
    assert_argument_equals(0, mips_fpu_register, mips_fpu_register::F0);

    assert_argument_type(1, argument_type::MIPS_FPU_Register);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F0);
}

define_test(cvt_s_w_1)
{
    setup_test_variables();

    parse_opcode(0x46801860);
    assert_mnemonic(CVT_S_W);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register, mips_fpu_register::F3);
}

define_default_test_main();
