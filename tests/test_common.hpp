
#include <algorithm>
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

#define emit_pseudoinstructions()\
    conf.emit_pseudo = true;
    
#define parse_opcode(OPCODE) \
    inst.opcode = OPCODE;\
    parse_instruction(OPCODE, &inst, &conf, &pdata);
    
#define assert_mnemonic(MNEM) \
    assert_equal(inst.mnemonic, allegrex_mnemonic::MNEM);
    
#define assert_argument_count(N) \
    assert_equal(inst.arguments.size(), N);
    
#define assert_argument_non_extra_count(N) \
    auto _count = std::count_if(inst.arguments.begin(), \
                                inst.arguments.end(), \
                                [](const instruction_argument &arg){ return !std::holds_alternative<extra>(arg); }\
                               ); \
    assert_equal(_count, N);
    
#define assert_argument_type(N, T) \
    assert_equal(std::holds_alternative<T>(inst.arguments.at(N)), true);
    
#define _assert_argument_equals(N, T, V) \
    assert_equal(std::get<T>(inst.arguments.at(N)), V);
    
#define _assert_argument_data_equals(N, T, V) \
    assert_equal(std::get<T>(inst.arguments.at(N)).data, V);
    
#define assert_argument_mips_register(N, R) \
    _assert_argument_equals(N, mips_register, R)
    
#define assert_argument_immediate(N, T, S) \
    _assert_argument_data_equals(N, immediate<T>, S)
    
#define assert_argument_shift(N, S) \
    _assert_argument_data_equals(N, shift, S)

std::ostream &operator<<(std::ostream &lhs, allegrex_mnemonic rhs)
{
    return lhs << get_mnemonic_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, mips_register rhs)
{
    return lhs << register_name(rhs);
}
