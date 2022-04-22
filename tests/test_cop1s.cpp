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

// c.f.s fs, ft
define_test(c_f_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000030);
    assert_mnemonic(C_F_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_f_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030830);
    assert_mnemonic(C_F_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.un.s fs, ft
define_test(c_un_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000031);
    assert_mnemonic(C_UN_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_un_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030831);
    assert_mnemonic(C_UN_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.eq.s fs, ft
define_test(c_eq_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000032);
    assert_mnemonic(C_EQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_eq_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030832);
    assert_mnemonic(C_EQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ueq.s fs, ft
define_test(c_ueq_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000033);
    assert_mnemonic(C_UEQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ueq_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030833);
    assert_mnemonic(C_UEQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.olt.s fs, ft
define_test(c_olt_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000034);
    assert_mnemonic(C_OLT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_olt_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030834);
    assert_mnemonic(C_OLT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ult.s fs, ft
define_test(c_ult_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000035);
    assert_mnemonic(C_ULT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ult_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030835);
    assert_mnemonic(C_ULT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ole.s fs, ft
define_test(c_ole_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000036);
    assert_mnemonic(C_OLE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ole_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030836);
    assert_mnemonic(C_OLE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ule.s fs, ft
define_test(c_ule_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000037);
    assert_mnemonic(C_ULE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ule_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030837);
    assert_mnemonic(C_ULE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.sf.s fs, ft
define_test(c_sf_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000038);
    assert_mnemonic(C_SF_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_sf_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030838);
    assert_mnemonic(C_SF_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ngle.s fs, ft
define_test(c_ngle_s_0)
{
    setup_test_variables();

    parse_opcode(0x46000039);
    assert_mnemonic(C_NGLE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ngle_s_1)
{
    setup_test_variables();

    parse_opcode(0x46030839);
    assert_mnemonic(C_NGLE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.seq.s fs, ft
define_test(c_seq_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003a);
    assert_mnemonic(C_SEQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_seq_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083a);
    assert_mnemonic(C_SEQ_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ngl.s fs, ft
define_test(c_ngl_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003b);
    assert_mnemonic(C_NGL_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ngl_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083b);
    assert_mnemonic(C_NGL_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.lt.s fs, ft
define_test(c_lt_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003c);
    assert_mnemonic(C_LT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_lt_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083c);
    assert_mnemonic(C_LT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.nge.s fs, ft
define_test(c_nge_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003d);
    assert_mnemonic(C_NGE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_nge_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083d);
    assert_mnemonic(C_NGE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.le.s fs, ft
define_test(c_le_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003e);
    assert_mnemonic(C_LE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_le_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083e);
    assert_mnemonic(C_LE_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

// c.ngt.s fs, ft
define_test(c_ngt_s_0)
{
    setup_test_variables();

    parse_opcode(0x4600003f);
    assert_mnemonic(C_NGT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F0);
}

define_test(c_ngt_s_1)
{
    setup_test_variables();

    parse_opcode(0x4603083f);
    assert_mnemonic(C_NGT_S);
    assert_argument_non_extra_count(2);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F1);

    assert_argument_type(1, mips_fpu_register);
    assert_argument_equals(1, mips_fpu_register::F3);
}

define_default_test_main();
