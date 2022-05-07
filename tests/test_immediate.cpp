
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// j address
define_test(j_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08000000);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_type(0, jump_address);
    assert_argument_equals(0, jump_address{0});
}

define_test(j_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08000001);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{4});
}

define_test(j_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x03fffffc});
}

define_test(j_3)
{
    setup_test_variables();

    inst.address = 0x10000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x13fffffc});
}

define_test(j_4)
{
    setup_test_variables();

    inst.address = 0xf0000000;
    parse_opcode(0x08ffffff);
    assert_mnemonic(J);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0xf3fffffc});
}

// jal address
define_test(jal_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0c000000);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_type(0, jump_address);
    assert_argument_equals(0, jump_address{0});
}

define_test(jal_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0c000001);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{4});
}

define_test(jal_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x03fffffc});
}

define_test(jal_3)
{
    setup_test_variables();

    inst.address = 0x10000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0x13fffffc});
}

define_test(jal_4)
{
    setup_test_variables();

    inst.address = 0xf0000000;
    parse_opcode(0x0cffffff);
    assert_mnemonic(JAL);
    assert_argument_count(1);

    assert_argument_equals(0, jump_address{0xf3fffffc});
}

// beq rs, rt, offset
define_test(beq_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x10000000);
    assert_mnemonic(BEQ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(beq_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x10620001);
    assert_mnemonic(BEQ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{8});
}

define_test(beq_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1062ffff);
    assert_mnemonic(BEQ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{0});
}

define_test(beq_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x10620000);
    assert_mnemonic(BEQ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{36});
}

define_test(beq_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000000;
    parse_opcode(0x10620000);
    assert_mnemonic(BEQ);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(beq_5)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000000;
    parse_opcode(0x10210000);
    assert_mnemonic(B);
    assert_argument_count(1);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4});
}

// bne rs, rt, offset
define_test(bne_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x14000000);
    assert_mnemonic(BNE);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(bne_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x14620001);
    assert_mnemonic(BNE);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{8});
}

define_test(bne_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1462ffff);
    assert_mnemonic(BNE);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{0});
}

define_test(bne_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x14620000);
    assert_mnemonic(BNE);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{36});
}

define_default_test_main();
