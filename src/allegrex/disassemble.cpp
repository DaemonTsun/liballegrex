
#include "shl/defer.hpp"
#include "shl/streams.hpp"
#include "allegrex/disassemble.hpp"

void init(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    init(&disasm->psp_module);
    ::init(&disasm->instruction_datas);
    ::init(&disasm->jump_destinations);
}

void free(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    ::free(&disasm->jump_destinations);
    ::free<true>(&disasm->instruction_datas);
    free(&disasm->psp_module);
}

void add_symbols_to_jumps(array<jump_destination> *jumps, hash_table<u32, elf_symbol> *syms)
{
    // this adds symbols as jumps so they appear in the disassembly
    for_hash_table(k, _, syms)
        ::add_at_end(jumps, jump_destination{*k, jump_type::Jump});
}

void add_imports_to_jumps(array<jump_destination> *jumps, array<module_import> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::add_at_end(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

void add_exports_to_jumps(array<jump_destination> *jumps, array<module_export> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::add_at_end(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

void disassemble_psp_elf(const char *path, psp_disassembly *out)
{
    assert(path != nullptr);
    assert(out != nullptr);

    memory_stream stream;
    init(&stream);
    defer { close(&stream); };

    read_entire_file(path, &stream);
    disassemble_psp_elf(&stream, out);
}

void disassemble_psp_elf(char *data, u64 size, psp_disassembly *out)
{
    assert(data != nullptr);
    assert(out != nullptr);

    memory_stream stream{};
    stream.data = data;
    stream.size = size;

    disassemble_psp_elf(&stream, out);
}

void disassemble_psp_elf(memory_stream *in, psp_disassembly *out)
{
    assert(in != nullptr);
    assert(out != nullptr);

    file_stream log;
    log.handle = stdout;

    psp_parse_elf_config elfconf;
    elfconf.section = ""_cs;
    elfconf.vaddr = INFER_VADDR;
    elfconf.verbose = false;
    elfconf.log = &log;

    parse_psp_module_from_elf(in, &out->psp_module, &elfconf);

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
        instruction_data->jump_destinations = &out->jump_destinations;
        instruction_data->section_index = i;

        if (sec->content_size > 0)
            parse_instructions(sec->content, sec->content_size, &pconf, instruction_data);
    }

    add_symbols_to_jumps(&out->jump_destinations, &out->psp_module.symbols);
    add_imports_to_jumps(&out->jump_destinations, &out->psp_module.imported_modules);
    add_exports_to_jumps(&out->jump_destinations, &out->psp_module.exported_modules);
    cleanup_jumps(&out->jump_destinations);
}
