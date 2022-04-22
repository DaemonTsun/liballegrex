
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// bvf offset, cc
define_test(bvf_0)
{
    setup_test_variables();

    parse_opcode(0x49000000);
    assert_mnemonic(BVF);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4}); // always adds +4 (sizeof(u32))

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{0});
}

define_test(bvf_1)
{
    setup_test_variables();

    parse_opcode(0x49040001);
    assert_mnemonic(BVF);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{8});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{1});
}

define_test(bvf_2)
{
    setup_test_variables();

    parse_opcode(0x4900FFFF);
    assert_mnemonic(BVF);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0}); // signed -1 (-4) = 0
}

define_test(bvf_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x49000000);
    assert_mnemonic(BVF);
    assert_argument_count(2);

    // relative branch, so have to add address
    assert_argument_equals(0, branch_address{0x00000014});
}

// bvt offset, cc
define_test(bvt_0)
{
    setup_test_variables();

    parse_opcode(0x49010000);
    assert_mnemonic(BVT);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{0});
}

define_test(bvt_1)
{
    setup_test_variables();

    parse_opcode(0x49050001);
    assert_mnemonic(BVT);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{8});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{1});
}

define_test(bvt_2)
{
    setup_test_variables();

    parse_opcode(0x4901FFFF);
    assert_mnemonic(BVT);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0});
}

define_test(bvt_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x49010000);
    assert_mnemonic(BVT);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0x00000014});
}

// bvfl offset, cc
define_test(bvfl_0)
{
    setup_test_variables();

    parse_opcode(0x49020000);
    assert_mnemonic(BVFL);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{0});
}

define_test(bvfl_1)
{
    setup_test_variables();

    parse_opcode(0x49060001);
    assert_mnemonic(BVFL);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{8});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{1});
}

define_test(bvfl_2)
{
    setup_test_variables();

    parse_opcode(0x4902FFFF);
    assert_mnemonic(BVFL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0});
}

define_test(bvfl_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x49020000);
    assert_mnemonic(BVFL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0x00000014});
}

// bvtl offset, cc
define_test(bvtl_0)
{
    setup_test_variables();

    parse_opcode(0x49030000);
    assert_mnemonic(BVTL);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{0});
}

define_test(bvtl_1)
{
    setup_test_variables();

    parse_opcode(0x49070001);
    assert_mnemonic(BVTL);
    assert_argument_count(2);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{8});

    assert_argument_type(1, condition_code);
    assert_argument_equals(1, condition_code{1});
}

define_test(bvtl_2)
{
    setup_test_variables();

    parse_opcode(0x4903FFFF);
    assert_mnemonic(BVTL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0});
}

define_test(bvtl_3)
{
    setup_test_variables();
    inst.address = 0x00000010;

    parse_opcode(0x49030000);
    assert_mnemonic(BVTL);
    assert_argument_count(2);

    assert_argument_equals(0, branch_address{0x00000014});
}

define_default_test_main();
