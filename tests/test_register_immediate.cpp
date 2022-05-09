
#include <t1/t1.hpp>
#include "tests/test_common.hpp"

// bltz rs, offset
define_test(bltz_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04000000);
    assert_mnemonic(BLTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bltz_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04600001);
    assert_mnemonic(BLTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bltz_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0460ffff);
    assert_mnemonic(BLTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bltz_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04600000);
    assert_mnemonic(BLTZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgez rs, offset
define_test(bgez_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04010000);
    assert_mnemonic(BGEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgez_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04610001);
    assert_mnemonic(BGEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgez_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0461ffff);
    assert_mnemonic(BGEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgez_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04610000);
    assert_mnemonic(BGEZ);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bltzl rs, offset
define_test(bltzl_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04020000);
    assert_mnemonic(BLTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bltzl_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04620001);
    assert_mnemonic(BLTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bltzl_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0462ffff);
    assert_mnemonic(BLTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bltzl_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04620000);
    assert_mnemonic(BLTZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgezl rs, offset
define_test(bgezl_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04030000);
    assert_mnemonic(BGEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgezl_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04630001);
    assert_mnemonic(BGEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgezl_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0463ffff);
    assert_mnemonic(BGEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgezl_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04630000);
    assert_mnemonic(BGEZL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// tgei rs, immediate
define_test(tgei_0)
{
    setup_test_variables();

    parse_opcode(0x04080000);
    assert_mnemonic(TGEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{0});
}

define_test(tgei_1)
{
    setup_test_variables();

    parse_opcode(0x04680001);
    assert_mnemonic(TGEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{1});
}

define_test(tgei_2)
{
    setup_test_variables();

    parse_opcode(0x0468ffff);
    assert_mnemonic(TGEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{-1});
}

// tgeiu rs, immediate
define_test(tgeiu_0)
{
    setup_test_variables();

    parse_opcode(0x04090000);
    assert_mnemonic(TGEIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{0});
}

define_test(tgeiu_1)
{
    setup_test_variables();

    parse_opcode(0x04690001);
    assert_mnemonic(TGEIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{1});
}

define_test(tgeiu_2)
{
    setup_test_variables();

    parse_opcode(0x0469ffff);
    assert_mnemonic(TGEIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{0xffff});
}

// tlti rs, immediate
define_test(tlti_0)
{
    setup_test_variables();

    parse_opcode(0x040a0000);
    assert_mnemonic(TLTI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{0});
}

define_test(tlti_1)
{
    setup_test_variables();

    parse_opcode(0x046a0001);
    assert_mnemonic(TLTI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{1});
}

define_test(tlti_2)
{
    setup_test_variables();

    parse_opcode(0x046affff);
    assert_mnemonic(TLTI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{-1});
}

// tltiu rs, immediate
define_test(tltiu_0)
{
    setup_test_variables();

    parse_opcode(0x040b0000);
    assert_mnemonic(TLTIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{0});
}

define_test(tltiu_1)
{
    setup_test_variables();

    parse_opcode(0x046b0001);
    assert_mnemonic(TLTIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{1});
}

define_test(tltiu_2)
{
    setup_test_variables();

    parse_opcode(0x046bffff);
    assert_mnemonic(TLTIU);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<u16>);
    assert_argument_equals(1, immediate<u16>{0xffff});
}

// teqi rs, immediate
define_test(teqi_0)
{
    setup_test_variables();

    parse_opcode(0x040c0000);
    assert_mnemonic(TEQI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{0});
}

define_test(teqi_1)
{
    setup_test_variables();

    parse_opcode(0x046c0001);
    assert_mnemonic(TEQI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{1});
}

define_test(teqi_2)
{
    setup_test_variables();

    parse_opcode(0x046cffff);
    assert_mnemonic(TEQI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{-1});
}

// tnei rs, immediate
define_test(tnei_0)
{
    setup_test_variables();

    parse_opcode(0x040e0000);
    assert_mnemonic(TNEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{0});
}

define_test(tnei_1)
{
    setup_test_variables();

    parse_opcode(0x046e0001);
    assert_mnemonic(TNEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{1});
}

define_test(tnei_2)
{
    setup_test_variables();

    parse_opcode(0x046effff);
    assert_mnemonic(TNEI);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, immediate<s16>);
    assert_argument_equals(1, immediate<s16>{-1});
}

// bltzal rs, offset
define_test(bltzal_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04100000);
    assert_mnemonic(BLTZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bltzal_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04700001);
    assert_mnemonic(BLTZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bltzal_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0470ffff);
    assert_mnemonic(BLTZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bltzal_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04700000);
    assert_mnemonic(BLTZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgezal rs, offset
define_test(bgezal_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04110000);
    assert_mnemonic(BGEZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgezal_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04710001);
    assert_mnemonic(BGEZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgezal_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0471ffff);
    assert_mnemonic(BGEZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgezal_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04710000);
    assert_mnemonic(BGEZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

define_test(bgezal_4)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000020;
    parse_opcode(0x04710000);
    assert_mnemonic(BGEZAL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

define_test(bgezal_5)
{
    setup_test_variables();

    emit_pseudoinstructions();
    inst.address = 0x00000020;
    parse_opcode(0x04110000);
    assert_mnemonic(BAL);
    assert_argument_count(1);

    assert_argument_type(0, jump_address);
    assert_argument_equals(0, jump_address{36});
}

// bltzall rs, offset
define_test(bltzall_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04120000);
    assert_mnemonic(BLTZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bltzall_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04720001);
    assert_mnemonic(BLTZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bltzall_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0472ffff);
    assert_mnemonic(BLTZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bltzall_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04720000);
    assert_mnemonic(BLTZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// bgezall rs, offset
define_test(bgezall_0)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04130000);
    assert_mnemonic(BGEZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::ZERO);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{4});
}

define_test(bgezall_1)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x04730001);
    assert_mnemonic(BGEZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{8});
}

define_test(bgezall_2)
{
    setup_test_variables();

    inst.address = 0x00000000;
    parse_opcode(0x0473ffff);
    assert_mnemonic(BGEZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{0});
}

define_test(bgezall_3)
{
    setup_test_variables();

    inst.address = 0x00000020;
    parse_opcode(0x04730000);
    assert_mnemonic(BGEZALL);
    assert_argument_count(2);

    assert_argument_type(0, mips_register);
    assert_argument_equals(0, mips_register::V1);

    assert_argument_type(1, branch_address);
    assert_argument_equals(1, branch_address{36});
}

// synci
define_test(synci)
{
    setup_test_variables();

    parse_opcode(0x041f0000);
    assert_mnemonic(SYNCI);
    assert_argument_count(0);
}

define_default_test_main();
