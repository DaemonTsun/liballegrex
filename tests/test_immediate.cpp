
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

// blez rs, rt, offset
define_test(blez_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x18000000);
    assert_mnemonic(BLEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(blez_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x18600001);
    assert_mnemonic(BLEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(blez_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1860ffff);
    assert_mnemonic(BLEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(blez_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x18600000);
    assert_mnemonic(BLEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgtz rs, rt, offset
define_test(bgtz_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1c000000);
    assert_mnemonic(BGTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgtz_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1c600001);
    assert_mnemonic(BGTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgtz_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x1c60ffff);
    assert_mnemonic(BGTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgtz_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x1c600000);
    assert_mnemonic(BGTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// addi rs, rt, imm
define_test(addi_0)
{
    setup_test_variables();

    parse_opcode(0x20000000);
    assert_mnemonic(ADDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{0});
}

define_test(addi_1)
{
    setup_test_variables();

    parse_opcode(0x20620001);
    assert_mnemonic(ADDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{1});
}

define_test(addi_2)
{
    setup_test_variables();

    parse_opcode(0x2062ffff);
    assert_mnemonic(ADDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{-1});
}

define_test(addi_3)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x2062ffff);
    assert_mnemonic(ADDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{-1});
}

define_test(addi_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x2002ffff);
    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, immediate<s32>);
    assert_argument_equals(1, immediate<s32>{-1});
}

// addiu rs, rt, imm
define_test(addiu_0)
{
    setup_test_variables();

    parse_opcode(0x24000000);
    assert_mnemonic(ADDIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{0});
}

define_test(addiu_1)
{
    setup_test_variables();

    parse_opcode(0x24620001);
    assert_mnemonic(ADDIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{1});
}

define_test(addiu_2)
{
    setup_test_variables();

    parse_opcode(0x2462ffff);
    assert_mnemonic(ADDIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{-1});
}

define_test(addiu_3)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x2462ffff);
    assert_mnemonic(ADDIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{-1});
}

define_test(addiu_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x2402ffff);
    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, immediate<s32>);
    assert_argument_equals(1, immediate<s32>{-1});
}

// slti rs, rt, imm
define_test(slti_0)
{
    setup_test_variables();

    parse_opcode(0x28000000);
    assert_mnemonic(SLTI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{0});
}

define_test(slti_1)
{
    setup_test_variables();

    parse_opcode(0x28620001);
    assert_mnemonic(SLTI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{1});
}

define_test(slti_2)
{
    setup_test_variables();

    parse_opcode(0x2862ffff);
    assert_mnemonic(SLTI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<s32>);
    assert_argument_equals(2, immediate<s32>{-1});
}

// sltiu rs, rt, imm
define_test(sltiu_0)
{
    setup_test_variables();

    parse_opcode(0x2c000000);
    assert_mnemonic(SLTIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0});
}

define_test(sltiu_1)
{
    setup_test_variables();

    parse_opcode(0x2c620001);
    assert_mnemonic(SLTIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{1});
}

define_test(sltiu_2)
{
    setup_test_variables();

    parse_opcode(0x2c62ffff);
    assert_mnemonic(SLTIU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0xffffffff});
}

// andi rs, rt, imm
define_test(andi_0)
{
    setup_test_variables();

    parse_opcode(0x30000000);
    assert_mnemonic(ANDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0});
}

define_test(andi_1)
{
    setup_test_variables();

    parse_opcode(0x30620001);
    assert_mnemonic(ANDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{1});
}

define_test(andi_2)
{
    setup_test_variables();

    parse_opcode(0x3062ffff);
    assert_mnemonic(ANDI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0x0000ffff});
}

// ori rs, rt, imm
define_test(ori_0)
{
    setup_test_variables();

    parse_opcode(0x34000000);
    assert_mnemonic(ORI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0});
}

define_test(ori_1)
{
    setup_test_variables();

    parse_opcode(0x34620001);
    assert_mnemonic(ORI);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, mips_register::V1);
    assert_argument_equals(2, immediate<u32>{1});
}

define_test(ori_2)
{
    setup_test_variables();

    parse_opcode(0x3462ffff);
    assert_mnemonic(ORI);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, mips_register::V1);
    assert_argument_equals(2, immediate<u32>{0x0000ffff});
}

define_test(ori_3)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x3462ffff);
    assert_mnemonic(ORI);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, mips_register::V1);
    assert_argument_equals(2, immediate<u32>{0x0000ffff});
}

define_test(ori_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    parse_opcode(0x3402ffff);
    assert_mnemonic(LI);
    assert_argument_count(2);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, immediate<u32>{0x0000ffff});
}

// xori rs, rt, imm
define_test(xori_0)
{
    setup_test_variables();

    parse_opcode(0x38000000);
    assert_mnemonic(XORI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0});
}

define_test(xori_1)
{
    setup_test_variables();

    parse_opcode(0x38620001);
    assert_mnemonic(XORI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{1});
}

define_test(xori_2)
{
    setup_test_variables();

    parse_opcode(0x3862ffff);
    assert_mnemonic(XORI);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V0);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V1);

    assert_argument_type(2, immediate<u32>);
    assert_argument_equals(2, immediate<u32>{0x0000ffff});
}

// lui rt, imm
define_test(lui_0)
{
    setup_test_variables();

    parse_opcode(0x3c000000);
    assert_mnemonic(LUI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{0});
}

define_test(lui_1)
{
    setup_test_variables();

    parse_opcode(0x3c020001);
    assert_mnemonic(LUI);
    assert_argument_count(2);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, immediate<u16>{1});
}

define_test(lui_2)
{
    setup_test_variables();

    parse_opcode(0x3c02ffff);
    assert_mnemonic(LUI);
    assert_argument_count(2);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, immediate<u16>{0xffff});
}

// beql rs, rt, offset
define_test(beql_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x50000000);
    assert_mnemonic(BEQL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(beql_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x50620001);
    assert_mnemonic(BEQL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{8});
}

define_test(beql_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5062ffff);
    assert_mnemonic(BEQL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{0});
}

define_test(beql_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x50620000);
    assert_mnemonic(BEQL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{36});
}

define_test(beql_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000000;
    parse_opcode(0x50620000);
    assert_mnemonic(BEQL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(beql_5)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000000;
    parse_opcode(0x50210000);
    assert_mnemonic(BL);
    assert_argument_count(1);

    assert_argument_type(0, branch_address);
    assert_argument_equals(0, branch_address{4});
}

// bnel rs, rt, offset
define_test(bnel_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x54000000);
    assert_mnemonic(BNEL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::ZERO);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{4});
}

define_test(bnel_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x54620001);
    assert_mnemonic(BNEL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{8});
}

define_test(bnel_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5462ffff);
    assert_mnemonic(BNEL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{0});
}

define_test(bnel_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x54620000);
    assert_mnemonic(BNEL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, mips_register);
    assert_argument_equals(1, mips_register::V0);

    assert_argument_type(2, branch_address);
    assert_argument_equals(2, branch_address{36});
}

// blezl rs, rt, offset
define_test(blezl_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x58000000);
    assert_mnemonic(BLEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(blezl_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x58600001);
    assert_mnemonic(BLEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(blezl_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5860ffff);
    assert_mnemonic(BLEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(blezl_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x58600000);
    assert_mnemonic(BLEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgtzl rs, rt, offset
define_test(bgtzl_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5c000000);
    assert_mnemonic(BGTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgtzl_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5c600001);
    assert_mnemonic(BGTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgtzl_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x5c60ffff);
    assert_mnemonic(BGTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgtzl_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x5c600000);
    assert_mnemonic(BGTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

define_default_test_main();
