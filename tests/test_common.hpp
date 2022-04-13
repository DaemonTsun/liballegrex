
#include <ostream>
#include "parse_instructions.hpp"

#define clear_instruction() \
    inst.opcode = 0;\
    inst.address = 0;\
    inst.mnemonic = allegrex_mnemonic::_UNKNOWN;\
    inst.arguments.clear();

#define setup_test_variables() \
    instruction inst;\
    clear_instruction();\
    parse_config conf;\
    conf.vaddr = 0;\
    conf.log = nullptr;\
    conf.emit_pseudo = false;\
    parse_data pdata;
    
#define parse_opcode(OPCODE) \
    parse_instruction(OPCODE, &inst, &conf, &pdata);
    
#define assert_mnemonic(MNEM) \
    assert_equal(inst.mnemonic, allegrex_mnemonic::MNEM);

std::ostream &operator<<(std::ostream &lhs, allegrex_mnemonic rhs)
{
    return lhs << get_mnemonic_name(rhs);
}
