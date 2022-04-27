
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// vrnds vd
define_test(vrnds_0)
{
    setup_test_variables();

    parse_opcode(0xd0200000);
    assert_mnemonic(VRNDS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrnds_1)
{
    setup_test_variables();

    parse_opcode(0xd0200301);
    assert_mnemonic(VRNDS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vrnds_2)
{
    setup_test_variables();

    parse_opcode(0xd0200080);
    assert_mnemonic(VRNDS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrnds_3)
{
    setup_test_variables();

    parse_opcode(0xd0208000);
    assert_mnemonic(VRNDS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrnds_4)
{
    setup_test_variables();

    parse_opcode(0xd0208080);
    assert_mnemonic(VRNDS);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

// vrndi vd
define_test(vrndi_0)
{
    setup_test_variables();

    parse_opcode(0xd0210000);
    assert_mnemonic(VRNDI);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrndi_1)
{
    setup_test_variables();

    parse_opcode(0xd0210301);
    assert_mnemonic(VRNDI);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vrndi_2)
{
    setup_test_variables();

    parse_opcode(0xd0210080);
    assert_mnemonic(VRNDI);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrndi_3)
{
    setup_test_variables();

    parse_opcode(0xd0218000);
    assert_mnemonic(VRNDI);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrndi_4)
{
    setup_test_variables();

    parse_opcode(0xd0218080);
    assert_mnemonic(VRNDI);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vrndf1 vd
define_test(vrndf1_0)
{
    setup_test_variables();

    parse_opcode(0xd0220000);
    assert_mnemonic(VRNDF1);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrndf1_1)
{
    setup_test_variables();

    parse_opcode(0xd0220301);
    assert_mnemonic(VRNDF1);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vrndf1_2)
{
    setup_test_variables();

    parse_opcode(0xd0220080);
    assert_mnemonic(VRNDF1);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrndf1_3)
{
    setup_test_variables();

    parse_opcode(0xd0228000);
    assert_mnemonic(VRNDF1);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrndf1_4)
{
    setup_test_variables();

    parse_opcode(0xd0228080);
    assert_mnemonic(VRNDF1);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vrndf2 vd
define_test(vrndf2_0)
{
    setup_test_variables();

    parse_opcode(0xd0230000);
    assert_mnemonic(VRNDF2);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
}

define_test(vrndf2_1)
{
    setup_test_variables();

    parse_opcode(0xd0230301);
    assert_mnemonic(VRNDF2);
    assert_argument_count(1);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
}

define_test(vrndf2_2)
{
    setup_test_variables();

    parse_opcode(0xd0230080);
    assert_mnemonic(VRNDF2);
    assert_argument_count(1);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
}

define_test(vrndf2_3)
{
    setup_test_variables();

    parse_opcode(0xd0238000);
    assert_mnemonic(VRNDF2);
    assert_argument_count(1);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
}

define_test(vrndf2_4)
{
    setup_test_variables();

    parse_opcode(0xd0238080);
    assert_mnemonic(VRNDF2);
    assert_argument_count(1);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
}

// vf2h vd, vs
define_test(vf2h_0)
{
    setup_test_variables();

    parse_opcode(0xd0320000);
    assert_mnemonic(VF2H);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vf2h_1)
{
    setup_test_variables();

    parse_opcode(0xd0320080);
    assert_mnemonic(VF2H);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vf2h_2)
{
    setup_test_variables();

    parse_opcode(0xd0328080);
    assert_mnemonic(VF2H);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vh2f vd, vs
define_test(vh2f_0)
{
    setup_test_variables();

    parse_opcode(0xd0330000);
    assert_mnemonic(VH2F);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vh2f_1)
{
    setup_test_variables();

    parse_opcode(0xd0330301);
    assert_mnemonic(VH2F);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vh2f_2)
{
    setup_test_variables();

    parse_opcode(0xd0330080);
    assert_mnemonic(VH2F);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

// vsbz vd, vs
define_test(vsbz_0)
{
    setup_test_variables();

    parse_opcode(0xd0360000);
    assert_mnemonic(VSBZ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vsbz_1)
{
    setup_test_variables();

    parse_opcode(0xd0360301);
    assert_mnemonic(VSBZ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vsbz_2)
{
    setup_test_variables();

    parse_opcode(0xd0360080);
    assert_mnemonic(VSBZ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vsbz_3)
{
    setup_test_variables();

    parse_opcode(0xd0368000);
    assert_mnemonic(VSBZ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vsbz_4)
{
    setup_test_variables();

    parse_opcode(0xd0368080);
    assert_mnemonic(VSBZ);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vlgb vd, vs
define_test(vlgb_0)
{
    setup_test_variables();

    parse_opcode(0xd0370000);
    assert_mnemonic(VLGB);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vlgb_1)
{
    setup_test_variables();

    parse_opcode(0xd0370301);
    assert_mnemonic(VLGB);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vlgb_2)
{
    setup_test_variables();

    parse_opcode(0xd0370080);
    assert_mnemonic(VLGB);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vlgb_3)
{
    setup_test_variables();

    parse_opcode(0xd0378000);
    assert_mnemonic(VLGB);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vlgb_4)
{
    setup_test_variables();

    parse_opcode(0xd0378080);
    assert_mnemonic(VLGB);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vuc2i vd, vs
define_test(vuc2i_0)
{
    setup_test_variables();

    parse_opcode(0xd0380000);
    assert_mnemonic(VUC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vuc2i_1)
{
    setup_test_variables();

    parse_opcode(0xd0380301);
    assert_mnemonic(VUC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vuc2i_2)
{
    setup_test_variables();

    parse_opcode(0xd0380080);
    assert_mnemonic(VUC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vuc2i_3)
{
    setup_test_variables();

    parse_opcode(0xd0388000);
    assert_mnemonic(VUC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vuc2i_4)
{
    setup_test_variables();

    parse_opcode(0xd0388080);
    assert_mnemonic(VUC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vc2i vd, vs
define_test(vc2i_0)
{
    setup_test_variables();

    parse_opcode(0xd0390000);
    assert_mnemonic(VC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vc2i_1)
{
    setup_test_variables();

    parse_opcode(0xd0390301);
    assert_mnemonic(VC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vc2i_2)
{
    setup_test_variables();

    parse_opcode(0xd0390080);
    assert_mnemonic(VC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vc2i_3)
{
    setup_test_variables();

    parse_opcode(0xd0398000);
    assert_mnemonic(VC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vc2i_4)
{
    setup_test_variables();

    parse_opcode(0xd0398080);
    assert_mnemonic(VC2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vus2i vd, vs
define_test(vus2i_0)
{
    setup_test_variables();

    parse_opcode(0xd03a0000);
    assert_mnemonic(VUS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vus2i_1)
{
    setup_test_variables();

    parse_opcode(0xd03a0301);
    assert_mnemonic(VUS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vus2i_2)
{
    setup_test_variables();

    parse_opcode(0xd03a0080);
    assert_mnemonic(VUS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vus2i_3)
{
    setup_test_variables();

    parse_opcode(0xd03a8000);
    assert_mnemonic(VUS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vus2i_4)
{
    setup_test_variables();

    parse_opcode(0xd03a8080);
    assert_mnemonic(VUS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vs2i vd, vs
define_test(vs2i_0)
{
    setup_test_variables();

    parse_opcode(0xd03b0000);
    assert_mnemonic(VS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vs2i_1)
{
    setup_test_variables();

    parse_opcode(0xd03b0301);
    assert_mnemonic(VS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vs2i_2)
{
    setup_test_variables();

    parse_opcode(0xd03b0080);
    assert_mnemonic(VS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vs2i_3)
{
    setup_test_variables();

    parse_opcode(0xd03b8000);
    assert_mnemonic(VS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Triple});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vs2i_4)
{
    setup_test_variables();

    parse_opcode(0xd03b8080);
    assert_mnemonic(VS2I);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vi2uc vd, vs
define_test(vi2uc_0)
{
    setup_test_variables();

    parse_opcode(0xd03c0000);
    assert_mnemonic(VI2UC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vi2uc_1)
{
    setup_test_variables();

    parse_opcode(0xd03c0301);
    assert_mnemonic(VI2UC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_equals(0, vfpu_register{1, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{3, vfpu_size::Single});
}

define_test(vi2uc_2)
{
    setup_test_variables();

    parse_opcode(0xd03c0080);
    assert_mnemonic(VI2UC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vi2uc_3)
{
    setup_test_variables();

    parse_opcode(0xd03c8000);
    assert_mnemonic(VI2UC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Triple);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Triple});
}

define_test(vi2uc_4)
{
    setup_test_variables();

    parse_opcode(0xd03c8080);
    assert_mnemonic(VI2UC);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vf2h vd, vs
define_test(vi2c_0)
{
    setup_test_variables();

    parse_opcode(0xd03d0000);
    assert_mnemonic(VI2C);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vi2c_1)
{
    setup_test_variables();

    parse_opcode(0xd03d0080);
    assert_mnemonic(VI2C);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vi2c_2)
{
    setup_test_variables();

    parse_opcode(0xd03d8080);
    assert_mnemonic(VI2C);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vi2us vd, vs
define_test(vi2us_0)
{
    setup_test_variables();

    parse_opcode(0xd03e0000);
    assert_mnemonic(VI2US);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vi2us_1)
{
    setup_test_variables();

    parse_opcode(0xd03e0080);
    assert_mnemonic(VI2US);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vi2us_2)
{
    setup_test_variables();

    parse_opcode(0xd03e8080);
    assert_mnemonic(VI2US);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

// vi2s vd, vs
define_test(vi2s_0)
{
    setup_test_variables();

    parse_opcode(0xd03f0000);
    assert_mnemonic(VI2S);
    assert_argument_count(2);
    assert_argument_vfpu_size(Single);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Invalid});

    assert_argument_type(1, vfpu_register);
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Single});
}

define_test(vi2s_1)
{
    setup_test_variables();

    parse_opcode(0xd03f0080);
    assert_mnemonic(VI2S);
    assert_argument_count(2);
    assert_argument_vfpu_size(Pair);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Pair});
}

define_test(vi2s_2)
{
    setup_test_variables();

    parse_opcode(0xd03f8080);
    assert_mnemonic(VI2S);
    assert_argument_count(2);
    assert_argument_vfpu_size(Quad);

    assert_argument_equals(0, vfpu_register{0, vfpu_size::Pair});
    assert_argument_equals(1, vfpu_register{0, vfpu_size::Quad});
}

define_default_test_main();
