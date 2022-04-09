
#include "string.hpp"
#include "format_instructions.hpp"
#include "file_stream.hpp"
#include "instruction.hpp"

template<typename... Ts>
int format(FILE *stream, const char *fmt, Ts &&...ts)
{
    return fprintf(stream, fmt, std::forward<Ts>(ts)...);
}

template<typename... Ts>
int format(char *str, const char *fmt, Ts &&...ts)
{
    return sprintf(str, fmt, std::forward<Ts>(ts)...);
}

template<typename T>
int default_instruction_format(T *stream, const instruction *inst)
{
    const char *name = get_mnemonic_name(inst->mnemonic);
    int ret = format(stream, "%06x %08x   %-10s", inst->address, inst->opcode, name);

    for (auto arg : inst->arguments)
        ret += format_instruction_argument(stream, arg);

    return ret;
}

template<typename T>
int vfpu_instruction_format(T *stream, const instruction *inst)
{
    const char *name = get_mnemonic_name(inst->mnemonic);
    vfpu_size sz = get_vfpu_size(inst->opcode);
    const char *suf = size_suffix(sz);
    auto fullname = str(name, suf); // slow lol

    int ret = format(stream, "%06x %08x   %-10s", inst->address, inst->opcode, fullname.c_str());

    for (auto arg : inst->arguments)
        ret += format_instruction_argument(stream, arg);

    return ret;
}

template<typename T>
int _format_instruction(T *stream, const instruction *inst)
{
    if (requires_vfpu_suffix(inst->mnemonic))
        return vfpu_instruction_format(stream, inst);

    return default_instruction_format(stream, inst);
}

int format_instruction(file_stream *stream, const instruction *inst)
{
    return format_instruction(stream->handle, inst);
}

int format_instruction(FILE *stream, const instruction *inst)
{
    return _format_instruction<FILE>(stream, inst);
}

int format_instruction(char *str, const instruction *inst)
{
    return _format_instruction<char>(str, inst);
}

int format_instruction_argument(file_stream *stream, instruction_argument arg)
{
    return format_instruction_argument(stream->handle, arg);
}

#define IF_ARG_TYPE_LOG(stream, arg, T, FMT) \
    if (std::holds_alternative<T>(arg)) \
    { \
        return format(stream, FMT, std::get<T>(arg).data); \
    }

template<typename T>
int _format_instruction_argument(T *stream, instruction_argument arg)
{
    if (std::holds_alternative<const char*>(arg))
    {
        return format(stream, " %s", std::get<const char*>(arg));
    }
    else if (std::holds_alternative<mips_register>(arg))
    {
        return format(stream, " %s", register_name(std::get<mips_register>(arg)));
    }
    else if (std::holds_alternative<mips_fpu_register>(arg))
    {
        return format(stream, " %s", register_name(std::get<mips_fpu_register>(arg)));
    }
    else if (std::holds_alternative<vfpu_register>(arg))
    {
        auto &reg = std::get<vfpu_register>(arg);
        return format(stream, " %s%s", register_name(reg)
                             , size_suffix(reg.size));
    }
    else if (std::holds_alternative<vfpu_matrix>(arg))
    {
        auto &mtx = std::get<vfpu_matrix>(arg);
        return format(stream, " %s%s", matrix_name(mtx)
                                      , size_suffix(mtx.size));
    }
    else if (std::holds_alternative<vfpu_condition>(arg))
    {
        return format(stream, " %s", vfpu_condition_name(std::get<vfpu_condition>(arg)));
    }
    else if (std::holds_alternative<vfpu_constant>(arg))
    {
        return format(stream, " %s", vfpu_constant_name(std::get<vfpu_constant>(arg)));
    }
    else if (std::holds_alternative<vfpu_prefix_array>(arg))
    {
        auto &arr = std::get<vfpu_prefix_array>(arg).data;
        return format(stream, " [%s,%s,%s,%s]", vfpu_prefix_name(arr[0])
                                  , vfpu_prefix_name(arr[1])
                                  , vfpu_prefix_name(arr[2])
                                  , vfpu_prefix_name(arr[3])
           );
    }
    else if (std::holds_alternative<vfpu_destination_prefix_array>(arg))
    {
        auto &arr = std::get<vfpu_destination_prefix_array>(arg).data;
        return format(stream, " [%s,%s,%s,%s]", vfpu_destination_prefix_name(arr[0])
                                  , vfpu_destination_prefix_name(arr[1])
                                  , vfpu_destination_prefix_name(arr[2])
                                  , vfpu_destination_prefix_name(arr[3])
           );
    }
    else if (std::holds_alternative<vfpu_rotation_array>(arg))
    {
        auto &arr = std::get<vfpu_rotation_array>(arg);
        int ret = format(stream, " [%s", vfpu_rotation_name(arr.data[0]));

        for (int i = 1; i < arr.size; ++i)
            ret += format(stream, ",%s", vfpu_rotation_name(arr.data[i]));

        ret += format(stream, "]");
        return ret;
    }
    else if (std::holds_alternative<base_register>(arg))
    {
        return format(stream, "(%s)", register_name(std::get<base_register>(arg).data));
    }
    else if (std::holds_alternative<const syscall*>(arg))
    {
        const syscall *sc = std::get<const syscall*>(arg);
        return format(stream, " %s <0x%08x>", sc->function_name, sc->id);
    }
    else IF_ARG_TYPE_LOG(stream, arg, shift, " %u")
    else IF_ARG_TYPE_LOG(stream, arg, address, " %x")
    else IF_ARG_TYPE_LOG(stream, arg, memory_offset, " %x")
    else IF_ARG_TYPE_LOG(stream, arg, immediate<u32>, " %u")
    else IF_ARG_TYPE_LOG(stream, arg, immediate<u16>, " %u")
    else IF_ARG_TYPE_LOG(stream, arg, immediate<s16>, " %d")
    else IF_ARG_TYPE_LOG(stream, arg, immediate<u8>, " %u")
    else IF_ARG_TYPE_LOG(stream, arg, immediate<float>, " %f")
    else IF_ARG_TYPE_LOG(stream, arg, condition_code, " (CC[%x])")
    else IF_ARG_TYPE_LOG(stream, arg, bitfield_pos, " %x")
    else IF_ARG_TYPE_LOG(stream, arg, bitfield_size, " %x")
    else if (std::holds_alternative<coprocessor_register>(arg))
    {
        coprocessor_register &d = std::get<coprocessor_register>(arg);
        return format(stream, " [%u, %u]", d.rd, d.sel);
    }

    return 0;
}

int format_instruction_argument(FILE *stream, instruction_argument arg)
{
    return _format_instruction_argument<FILE>(stream, arg);
}

int format_instruction_argument(char *str, instruction_argument arg)
{
    return _format_instruction_argument<char>(str, arg);
}
