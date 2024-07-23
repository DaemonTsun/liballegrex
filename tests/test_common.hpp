
#include "t1/t1.hpp"
#include "shl/defer.hpp"
#include "shl/memory.hpp"
#include "allegrex/parse_instructions.hpp"

#define clear_instruction() \
    fill_memory(&inst, 0);\
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
    assert_equal(inst.argument_count, (u32)N);
    
#define assert_argument_non_extra_count(N) \
    if constexpr(u32 _count = 0; true)\
    {\
        for (u32 nonextra_it = 0; nonextra_it < inst.argument_count; ++nonextra_it)\
            if (inst.argument_types[nonextra_it] != argument_type::Extra)\
                _count++;\
        assert_equal(_count, (u32)N);\
    }
    
#define assert_argument_type(N, Type) \
    assert_greater_or_equal(inst.argument_count, (u32)N+1);\
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
    assert_equal(inst.arguments[N].vfpu_rotation_array.size, (u64)Value);
    
#define assert_argument_vfpu_size(SZ) \
    assert_equal(get_vfpu_size(inst.opcode), vfpu_size::SZ);

define_t1_to_string(allegrex_mnemonic x, "%s", get_mnemonic_name(x));
define_t1_to_string(mips_register x, "%s", register_name(x));
define_t1_to_string(base_register x, "%s", register_name(x.data));
define_t1_to_string(mips_fpu_register x, "%s", register_name(x));
define_t1_to_string(vfpu_size x, "%s", size_suffix(x));
define_t1_to_string(vfpu_register x, "%s", register_name(x));
define_t1_to_string(vfpu_matrix x, "%s", matrix_name(x));
define_t1_to_string(vfpu_condition x, "%s", vfpu_condition_name(x));
define_t1_to_string(shift x, "%d", (int)(x.data));
define_t1_to_string(memory_offset x, "%u", x.data);
define_t1_to_string(extra x, "%d", (int)(x.data));
define_t1_to_string(branch_address x, "%x", x.data);
define_t1_to_string(jump_address x, "%x", x.data);
define_t1_to_string(condition_code x, "%d", (int)(x.data));
define_t1_to_string(bitfield_pos x, "pos(%d)", (int)(x.data));
define_t1_to_string(bitfield_size x, "size(%d)", (int)(x.data));
define_t1_to_string(vfpu_prefix x, "%s", vfpu_prefix_name(x));
define_t1_to_string(vfpu_prefix_array x, "[%x,%x,%x,%x]", (u8)x.data[0]
                                                        , (u8)x.data[1]
                                                        , (u8)x.data[2]
                                                        , (u8)x.data[3]);

define_t1_to_string(vfpu_destination_prefix x, "%s", vfpu_destination_prefix_name(x));
define_t1_to_string(vfpu_destination_prefix_array x, "[%x,%x,%x,%x]", (u8)x.data[0]
                                                                    , (u8)x.data[1]
                                                                    , (u8)x.data[2]
                                                                    , (u8)x.data[3]);

define_t1_to_string(vfpu_rotation x, "%s", vfpu_rotation_name(x));

[[maybe_unused]] t1_string _t1_to_string(vfpu_rotation_array x)
{
    switch (x.size)
    {
    case 1: return t1_tprintf("[%x]",          (u8)x.data[0]);
    case 2: return t1_tprintf("[%x,%x]",       (u8)x.data[0], (u8)x.data[1]);
    case 3: return t1_tprintf("[%x,%x,%x]",    (u8)x.data[0], (u8)x.data[1], (u8)x.data[2]);
    case 4: return t1_tprintf("[%x,%x,%x,%x]", (u8)x.data[0], (u8)x.data[1], (u8)x.data[2], (u8)x.data[3]);
    default: return t1_tprintf("[]");
    }
}

define_t1_to_string(immediate<u8> x,  "%u", x.data);
define_t1_to_string(immediate<u16> x, "%u", x.data);
define_t1_to_string(immediate<u32> x, "%u", x.data);
define_t1_to_string(immediate<s16> x, "%d", x.data);
define_t1_to_string(immediate<s32> x, "%d", x.data);

define_t1_to_string(coprocessor_register x, "[%d, %d]", (int)x.rd, (int)x.sel);
define_t1_to_string(string_argument x, "%s", x.data);
define_t1_to_string(const psp_module *x, "%p", x);
define_t1_to_string(const psp_function *x, "%p", x);

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
    for (u32 i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const vfpu_destination_prefix_array &lhs, const vfpu_destination_prefix_array &rhs)
{
    for (u32 i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const vfpu_rotation_array &lhs, const vfpu_rotation_array &rhs)
{
    if (lhs.size != rhs.size)
        return false;

    for (u32 i = 0; i < lhs.size; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const string_argument &lhs, const string_argument &rhs)
{
    return strcmp(lhs.data, rhs.data) == 0;
}
