#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// add.s fd, fs, ft
define_test(add_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000000);
    assert_mnemonic(ADD_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(add_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071840);
    assert_mnemonic(ADD_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// sub.s fd, fs, ft
define_test(sub_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000001);
    assert_mnemonic(SUB_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(sub_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071841);
    assert_mnemonic(SUB_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// mul.s fd, fs, ft
define_test(mul_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000002);
    assert_mnemonic(MUL_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(mul_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071842);
    assert_mnemonic(MUL_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// div.s fd, fs, ft
define_test(div_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000003);
    assert_mnemonic(DIV_S);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);

    assert_argument_type(2, mips_fpu_register);
    assert_argument_equals(2, mips_fpu_register::F0);
}

define_test(div_s_1)
{
    setup_test_variables();

    parse_opcode(0x46071843);
    assert_mnemonic(DIV_S);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
    assert_argument_equals(2, mips_fpu_register::F7);
}

// sqrt.s fd, fs
define_test(sqrt_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000004);
    assert_mnemonic(SQRT_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(sqrt_s_1)
{
    setup_test_variables();

    parse_opcode(0x46001844);
    assert_mnemonic(SQRT_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// abs.s fd, fs
define_test(abs_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000005);
    assert_mnemonic(ABS_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(abs_s_1)
{
    setup_test_variables();

    parse_opcode(0x46001845);
    assert_mnemonic(ABS_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// mov.s fd, fs
define_test(mov_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000006);
    assert_mnemonic(MOV_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(mov_s_1)
{
    setup_test_variables();

    parse_opcode(0x46001846);
    assert_mnemonic(MOV_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// neg.s fd, fs
define_test(neg_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000007);
    assert_mnemonic(NEG_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(neg_s_1)
{
    setup_test_variables();

    parse_opcode(0x46001847);
    assert_mnemonic(NEG_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// round.w.s fd, fs
define_test(round_w_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600000c);
    assert_mnemonic(ROUND_W_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(round_w_s_1)
{
    setup_test_variables();

    parse_opcode(0x4600184c);
    assert_mnemonic(ROUND_W_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// trunc.w.s fd, fs
define_test(trunc_w_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600000d);
    assert_mnemonic(TRUNC_W_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(trunc_w_s_1)
{
    setup_test_variables();

    parse_opcode(0x4600184d);
    assert_mnemonic(TRUNC_W_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// ceil.w.s fd, fs
define_test(ceil_w_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600000e);
    assert_mnemonic(CEIL_W_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(ceil_w_s_1)
{
    setup_test_variables();

    parse_opcode(0x4600184e);
    assert_mnemonic(CEIL_W_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// floor.w.s fd, fs
define_test(floor_w_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600000f);
    assert_mnemonic(FLOOR_W_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(floor_w_s_1)
{
    setup_test_variables();

    parse_opcode(0x4600184f);
    assert_mnemonic(FLOOR_W_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// cvt.w.s fd, fs
define_test(cvt_w_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000024);
    assert_mnemonic(CVT_W_S);
    assert_argument_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(cvt_w_s_1)
{
    setup_test_variables();

    parse_opcode(0x46001864);
    assert_mnemonic(CVT_W_S);
    assert_argument_count(2);

    assert_argument_equals(0, mips_fpu_register::F1);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// dis.int
define_test(dis_int)
{
    setup_test_variables();

    parse_opcode(0x46000026);
    assert_mnemonic(DIS_INT);
    assert_argument_count(0);
}

define_default_test_main();
