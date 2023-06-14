
#include <algorithm>
#include <ostream>
#include <string.h>

#include "shl/defer.hpp"
#include "allegrex/parse_instructions.hpp"

#define clear_instruction() \
    memset(&inst, 0, sizeof(instruction));\
    inst.mnemonic = allegrex_mnemonic::_UNKNOWN;\

#define setup_test_variables() \
    instruction inst;\
    clear_instruction();\
    parse_instructions_config conf;\
    conf.vaddr = 0;\
    conf.log = nullptr;\
    conf.emit_pseudo = false;\
    instruction_parse_data instruction_data;\
    jump_destinations jumps{};\
    defer { free(&jumps); };\
    instruction_data.jumps = &jumps;

#define emit_pseudoinstructions()\
    conf.emit_pseudo = true;
    
#define parse_opcode(OPCODE) \
    inst.opcode = OPCODE;\
    parse_instruction(OPCODE, &inst, &conf, &instruction_data);
    
#define assert_mnemonic(MNEM) \
    assert_equal(inst.mnemonic, allegrex_mnemonic::MNEM);
    
#define assert_argument_count(N) \
    assert_equal(inst.argument_count, N);
    
#define assert_argument_non_extra_count(N) \
    u32 _count = 0;\
    for (u32 nonextra_it = 0; nonextra_it < inst.argument_count; ++nonextra_it)\
        if (inst.argument_types[nonextra_it] != argument_type::Extra)\
            _count++;\
    assert_equal(_count, N);
    
#define assert_argument_type(N, Type) \
    assert_greater_or_equal(inst.argument_count, N+1);\
    assert_equal(inst.argument_types[N], Type);
    
#define assert_argument_equals(N, UnionMember, ...) \
    assert_equal(inst.arguments[N].UnionMember, (__VA_ARGS__));
    
#define assert_argument_vfpu_prefix_equals(N, ArrayIndex, Value) \
    assert_equal(inst.arguments[N].vfpu_prefix_array.data[ArrayIndex], Value);

#define assert_argument_vfpu_destination_prefix_equals(N, ArrayIndex, Value) \
    assert_equal(inst.arguments[N].vfpu_destination_prefix_array.data[ArrayIndex], Value);
    
#define assert_argument_vfpu_rotation_equals(N, ArrayIndex, Value) \
    assert_equal(inst.arguments[N].vfpu_rotation_array.data[ArrayIndex], Value);
    
#define assert_argument_vfpu_rotation_count(N, Value) \
    assert_equal(inst.arguments[N].vfpu_rotation_array.size, Value);
    
#define assert_argument_vfpu_size(SZ) \
    assert_equal(get_vfpu_size(inst.opcode), vfpu_size::SZ);

std::ostream &operator<<(std::ostream &lhs, allegrex_mnemonic rhs)
{
    return lhs << get_mnemonic_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, mips_register rhs)
{
    return lhs << register_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, base_register rhs)
{
    return lhs << register_name(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, mips_fpu_register rhs)
{
    return lhs << register_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_size rhs)
{
    return lhs << size_suffix(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_register rhs)
{
    return lhs << register_name(rhs) << rhs.size;
}

std::ostream &operator<<(std::ostream &lhs, vfpu_matrix rhs)
{
    return lhs << matrix_name(rhs) << rhs.size;
}

std::ostream &operator<<(std::ostream &lhs, vfpu_condition rhs)
{
    return lhs << vfpu_condition_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, shift rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, memory_offset rhs)
{
    return lhs << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, extra rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, branch_address rhs)
{
    return lhs << std::hex << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, jump_address rhs)
{
    return lhs << std::hex << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, condition_code rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, bitfield_pos rhs)
{
    return lhs << "pos(" << static_cast<int>(rhs.data) << ")";
}

std::ostream &operator<<(std::ostream &lhs, bitfield_size rhs)
{
    return lhs << "size(" << static_cast<int>(rhs.data) << ")";
}

std::ostream &operator<<(std::ostream &lhs, vfpu_prefix rhs)
{
    return lhs << vfpu_prefix_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_prefix_array rhs)
{
    return lhs << '[' << rhs.data[0]
               << ',' << rhs.data[1]
               << ',' << rhs.data[2]
               << ',' << rhs.data[3]
               << ']';
}

std::ostream &operator<<(std::ostream &lhs, vfpu_destination_prefix rhs)
{
    return lhs << vfpu_destination_prefix_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_destination_prefix_array rhs)
{
    return lhs << '[' << rhs.data[0]
               << ',' << rhs.data[1]
               << ',' << rhs.data[2]
               << ',' << rhs.data[3]
               << ']';
}

std::ostream &operator<<(std::ostream &lhs, vfpu_rotation rhs)
{
    return lhs << vfpu_rotation_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_rotation_array rhs)
{
    lhs << '[' << rhs.data[0];

    for (int i = 1; i < rhs.size; ++i)
        lhs << ',' << rhs.data[i];

    return lhs << ']';
}

template<typename T>
std::ostream &operator<<(std::ostream &lhs, immediate<T> rhs)
{
    return lhs << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, coprocessor_register rhs)
{
    return lhs << '[' << static_cast<int>(rhs.rd) << ", " << static_cast<int>(rhs.sel) << ']';
}

std::ostream &operator<<(std::ostream &lhs, string_argument rhs)
{
    return lhs << rhs.data;
}

bool operator==(const shift &lhs, const shift &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const base_register &lhs, const base_register &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const memory_offset &lhs, const memory_offset &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const extra &lhs, const extra &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const branch_address &lhs, const branch_address &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const jump_address &lhs, const jump_address &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const condition_code &lhs, const condition_code &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const bitfield_pos &lhs, const bitfield_pos &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const bitfield_size &lhs, const bitfield_size &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const coprocessor_register &lhs, const coprocessor_register &rhs)
{
    return (lhs.rd == rhs.rd) && (lhs.sel == rhs.sel);
}

template<typename T>
bool operator==(const immediate<T> &lhs, const immediate<T> &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const vfpu_register &lhs, const vfpu_register &rhs)
{
    return (lhs.num == rhs.num) && (lhs.size == rhs.size);
}

bool operator==(const vfpu_matrix &lhs, const vfpu_matrix &rhs)
{
    return (lhs.num == rhs.num) && (lhs.size == rhs.size);
}

bool operator==(const vfpu_prefix_array &lhs, const vfpu_prefix_array &rhs)
{
    for (int i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const vfpu_destination_prefix_array &lhs, const vfpu_destination_prefix_array &rhs)
{
    for (int i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const vfpu_rotation_array &lhs, const vfpu_rotation_array &rhs)
{
    if (lhs.size != rhs.size)
        return false;

    for (int i = 0; i < lhs.size; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const string_argument &lhs, const string_argument &rhs)
{
    return strcmp(lhs.data, rhs.data) == 0;
}
