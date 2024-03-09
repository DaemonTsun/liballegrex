
#include "shl/defer.hpp"
#include "shl/streams.hpp"
#include "allegrex/disassemble.hpp"

void init(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    init(&disasm->psp_module);
    ::init(&disasm->instruction_datas);
    ::init(&disasm->jumps.data);
}

void free(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    ::free(&disasm->jumps);
    ::free<true>(&disasm->instruction_datas);
    free(&disasm->psp_module);
}

static void _add_symbols_to_jumps(jump_destinations *jumps, hash_table<u32, elf_symbol> *syms)
{
    // this adds symbols as jumps so they appear in the disassembly
    for_hash_table(k, _, syms)
        ::insert_element(jumps, jump_destination{*k, jump_type::Jump});
}

static void _add_imports_to_jumps(jump_destinations *jumps, array<module_import> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::insert_element(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

static void _add_exports_to_jumps(jump_destinations *jumps, array<module_export> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::insert_element(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

bool disassemble_psp_elf(const char *path, psp_disassembly *out, error *err)
{
    assert(path != nullptr);
    assert(out != nullptr);

    memory_stream stream{};

    if (!read_entire_file(path, &stream, err))
        return false;

    defer { free(&stream); };

    return disassemble_psp_elf(&stream, out, err);
}

bool disassemble_psp_elf(char *data, u64 size, psp_disassembly *out, error *err)
{
    assert(data != nullptr);
    assert(out != nullptr);

    memory_stream stream{};
    stream.data = data;
    stream.size = size;

    return disassemble_psp_elf(&stream, out, err);
}

bool disassemble_psp_elf(memory_stream *in, psp_disassembly *out, error *err)
{
    assert(in != nullptr);
    assert(out != nullptr);

    file_stream log;
    log.handle = stdout_handle();

    psp_parse_elf_config elfconf;
    elfconf.section = ""_cs;
    elfconf.vaddr = INFER_VADDR;
    elfconf.verbose = false;
    elfconf.log = &log;

    if (!parse_psp_module_from_elf(in, &out->psp_module, &elfconf, err))
        return false;

    ::resize(&out->instruction_datas, out->psp_module.sections.size);
    
    for_array(i, sec, &out->psp_module.sections)
    {
        parse_instructions_config pconf;
        pconf.log = &log;
        pconf.vaddr = sec->vaddr;
        pconf.verbose = false;
        pconf.emit_pseudo = true;

        instruction_parse_data *instruction_data = out->instruction_datas.data + i;
        init(instruction_data);
        instruction_data->jumps = &out->jumps;
        instruction_data->section_index = (u32)i;

        if (sec->content_size > 0)
            parse_instructions(sec->content, sec->content_size, &pconf, instruction_data);
    }

    _add_symbols_to_jumps(&out->jumps, &out->psp_module.symbols);
    _add_imports_to_jumps(&out->jumps, &out->psp_module.imported_modules);
    _add_exports_to_jumps(&out->jumps, &out->psp_module.exported_modules);

    return true;
}
