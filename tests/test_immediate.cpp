
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

// lb rt, offset (base)
define_test(lb_0)
{
    setup_test_variables();

    parse_opcode(0x80000000);
    assert_mnemonic(LB);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lb_1)
{
    setup_test_variables();

    parse_opcode(0x80620001);
    assert_mnemonic(LB);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lb_2)
{
    setup_test_variables();

    parse_opcode(0x8062ffff);
    assert_mnemonic(LB);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lh rt, offset (base)
define_test(lh_0)
{
    setup_test_variables();

    parse_opcode(0x84000000);
    assert_mnemonic(LH);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lh_1)
{
    setup_test_variables();

    parse_opcode(0x84620001);
    assert_mnemonic(LH);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lh_2)
{
    setup_test_variables();

    parse_opcode(0x8462ffff);
    assert_mnemonic(LH);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lwl rt, offset (base)
define_test(lwl_0)
{
    setup_test_variables();

    parse_opcode(0x88000000);
    assert_mnemonic(LWL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lwl_1)
{
    setup_test_variables();

    parse_opcode(0x88620001);
    assert_mnemonic(LWL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lwl_2)
{
    setup_test_variables();

    parse_opcode(0x8862ffff);
    assert_mnemonic(LWL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lw rt, offset (base)
define_test(lw_0)
{
    setup_test_variables();

    parse_opcode(0x8c000000);
    assert_mnemonic(LW);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lw_1)
{
    setup_test_variables();

    parse_opcode(0x8c620001);
    assert_mnemonic(LW);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lw_2)
{
    setup_test_variables();

    parse_opcode(0x8c62ffff);
    assert_mnemonic(LW);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lbu rt, offset (base)
define_test(lbu_0)
{
    setup_test_variables();

    parse_opcode(0x90000000);
    assert_mnemonic(LBU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lbu_1)
{
    setup_test_variables();

    parse_opcode(0x90620001);
    assert_mnemonic(LBU);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lbu_2)
{
    setup_test_variables();

    parse_opcode(0x9062ffff);
    assert_mnemonic(LBU);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lhu rt, offset (base)
define_test(lhu_0)
{
    setup_test_variables();

    parse_opcode(0x94000000);
    assert_mnemonic(LHU);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lhu_1)
{
    setup_test_variables();

    parse_opcode(0x94620001);
    assert_mnemonic(LHU);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lhu_2)
{
    setup_test_variables();

    parse_opcode(0x9462ffff);
    assert_mnemonic(LHU);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lwr rt, offset (base)
define_test(lwr_0)
{
    setup_test_variables();

    parse_opcode(0x98000000);
    assert_mnemonic(LWR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lwr_1)
{
    setup_test_variables();

    parse_opcode(0x98620001);
    assert_mnemonic(LWR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lwr_2)
{
    setup_test_variables();

    parse_opcode(0x9862ffff);
    assert_mnemonic(LWR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// sb rt, offset (base)
define_test(sb_0)
{
    setup_test_variables();

    parse_opcode(0xa0000000);
    assert_mnemonic(SB);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sb_1)
{
    setup_test_variables();

    parse_opcode(0xa0620001);
    assert_mnemonic(SB);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sb_2)
{
    setup_test_variables();

    parse_opcode(0xa062ffff);
    assert_mnemonic(SB);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// sh rt, offset (base)
define_test(sh_0)
{
    setup_test_variables();

    parse_opcode(0xa4000000);
    assert_mnemonic(SH);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sh_1)
{
    setup_test_variables();

    parse_opcode(0xa4620001);
    assert_mnemonic(SH);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sh_2)
{
    setup_test_variables();

    parse_opcode(0xa462ffff);
    assert_mnemonic(SH);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// swl rt, offset (base)
define_test(swl_0)
{
    setup_test_variables();

    parse_opcode(0xa8000000);
    assert_mnemonic(SWL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(swl_1)
{
    setup_test_variables();

    parse_opcode(0xa8620001);
    assert_mnemonic(SWL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(swl_2)
{
    setup_test_variables();

    parse_opcode(0xa862ffff);
    assert_mnemonic(SWL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// sw rt, offset (base)
define_test(sw_0)
{
    setup_test_variables();

    parse_opcode(0xac000000);
    assert_mnemonic(SW);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sw_1)
{
    setup_test_variables();

    parse_opcode(0xac620001);
    assert_mnemonic(SW);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sw_2)
{
    setup_test_variables();

    parse_opcode(0xac62ffff);
    assert_mnemonic(SW);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// swr rt, offset (base)
define_test(swr_0)
{
    setup_test_variables();

    parse_opcode(0xb8000000);
    assert_mnemonic(SWR);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(swr_1)
{
    setup_test_variables();

    parse_opcode(0xb8620001);
    assert_mnemonic(SWR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(swr_2)
{
    setup_test_variables();

    parse_opcode(0xb862ffff);
    assert_mnemonic(SWR);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// cache op, offset (base)
define_test(cache_0)
{
    setup_test_variables();

    parse_opcode(0xbc000000);
    assert_mnemonic(CACHE);
    assert_argument_count(3);

    assert_argument_type(0, immediate<u32>);
    assert_argument_equals(0, immediate<u32>{0});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(cache_1)
{
    setup_test_variables();

    parse_opcode(0xbc620001);
    assert_mnemonic(CACHE);
    assert_argument_count(3);

    assert_argument_type(0, immediate<u32>);
    assert_argument_equals(0, immediate<u32>{2});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{1});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::V1});
}

// ll rt, offset (base)
define_test(ll_0)
{
    setup_test_variables();

    parse_opcode(0xc0000000);
    assert_mnemonic(LL);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(ll_1)
{
    setup_test_variables();

    parse_opcode(0xc0620001);
    assert_mnemonic(LL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(ll_2)
{
    setup_test_variables();

    parse_opcode(0xc062ffff);
    assert_mnemonic(LL);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lwc1 ft, offset (base)
define_test(lwc1_0)
{
    setup_test_variables();

    parse_opcode(0xc4000000);
    assert_mnemonic(LWC1);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lwc1_1)
{
    setup_test_variables();

    parse_opcode(0xc4620001);
    assert_mnemonic(LWC1);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F2);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lwc1_2)
{
    setup_test_variables();

    parse_opcode(0xc462ffff);
    assert_mnemonic(LWC1);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F2);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lv.s vt, offset (base)
define_test(lv_s_0)
{
    setup_test_variables();

    parse_opcode(0xc8000000);
    assert_mnemonic(LV_S);
    assert_argument_count(3);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lv_s_1)
{
    setup_test_variables();

    parse_opcode(0xc8620004);
    assert_mnemonic(LV_S);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{2, vfpu_size::Single});
    assert_argument_equals(1, memory_offset{4});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lv_s_2)
{
    setup_test_variables();

    parse_opcode(0xc8620001);
    assert_mnemonic(LV_S);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Single});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// lv.q vt, offset (base)
define_test(lv_q_0)
{
    setup_test_variables();

    parse_opcode(0xd8000000);
    assert_mnemonic(LV_Q);
    assert_argument_count(3);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(lv_q_1)
{
    setup_test_variables();

    parse_opcode(0xd8620004);
    assert_mnemonic(LV_Q);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{4});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lv_q_2)
{
    setup_test_variables();

    parse_opcode(0xd8620001);
    assert_mnemonic(LV_Q);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(lv_q_3)
{
    setup_test_variables();

    parse_opcode(0xd8620003);
    assert_mnemonic(LV_Q);
    assert_argument_count(4);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
    assert_argument_type(3, const char *);
    // assert_argument_equals(3, "wb");
}

// sc rt, offset (base)
define_test(sc_0)
{
    setup_test_variables();

    parse_opcode(0xe0000000);
    assert_mnemonic(SC);
    assert_argument_count(3);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sc_1)
{
    setup_test_variables();

    parse_opcode(0xe0620001);
    assert_mnemonic(SC);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sc_2)
{
    setup_test_variables();

    parse_opcode(0xe062ffff);
    assert_mnemonic(SC);
    assert_argument_count(3);

    assert_argument_equals(0, mips_register::V0);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// swc1 ft, offset (base)
define_test(swc1_0)
{
    setup_test_variables();

    parse_opcode(0xe4000000);
    assert_mnemonic(SWC1);
    assert_argument_count(3);

    assert_argument_type(0, mips_fpu_register);
    assert_argument_equals(0, mips_fpu_register::F0);

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(swc1_1)
{
    setup_test_variables();

    parse_opcode(0xe4620001);
    assert_mnemonic(SWC1);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F2);
    assert_argument_equals(1, memory_offset{1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(swc1_2)
{
    setup_test_variables();

    parse_opcode(0xe462ffff);
    assert_mnemonic(SWC1);
    assert_argument_count(3);

    assert_argument_equals(0, mips_fpu_register::F2);
    assert_argument_equals(1, memory_offset{-1});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// sv.s vt, offset (base)
define_test(sv_s_0)
{
    setup_test_variables();

    parse_opcode(0xe8000000);
    assert_mnemonic(SV_S);
    assert_argument_count(3);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Single});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sv_s_1)
{
    setup_test_variables();

    parse_opcode(0xe8620004);
    assert_mnemonic(SV_S);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{2, vfpu_size::Single});
    assert_argument_equals(1, memory_offset{4});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sv_s_2)
{
    setup_test_variables();

    parse_opcode(0xe8620001);
    assert_mnemonic(SV_S);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Single});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
}

// sv.q vt, offset (base)
define_test(sv_q_0)
{
    setup_test_variables();

    parse_opcode(0xf8000000);
    assert_mnemonic(SV_Q);
    assert_argument_count(3);

    assert_argument_type(0, vfpu_register);
    assert_argument_equals(0, vfpu_register{0, vfpu_size::Quad});

    assert_argument_type(1, memory_offset);
    assert_argument_equals(1, memory_offset{0});

    assert_argument_type(2, base_register);
    assert_argument_equals(2, base_register{mips_register::ZERO});
}

define_test(sv_q_1)
{
    setup_test_variables();

    parse_opcode(0xf8620004);
    assert_mnemonic(SV_Q);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{2, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{4});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sv_q_2)
{
    setup_test_variables();

    parse_opcode(0xf8620001);
    assert_mnemonic(SV_Q);
    assert_argument_count(3);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
}

define_test(sv_q_3)
{
    setup_test_variables();

    parse_opcode(0xf8620003);
    assert_mnemonic(SV_Q);
    assert_argument_count(4);

    assert_argument_equals(0, vfpu_register{34, vfpu_size::Quad});
    assert_argument_equals(1, memory_offset{0});
    assert_argument_equals(2, base_register{mips_register::V1});
    assert_argument_type(3, const char *);
    // assert_argument_equals(3, "wb");
}

define_default_test_main();
