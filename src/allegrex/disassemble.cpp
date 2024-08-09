
#include "shl/defer.hpp"
#include "shl/streams.hpp"
#include "allegrex/disassemble.hpp"

void init(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    init(&disasm->psp_module);
    ::init(&disasm->all_instructions);
    ::init(&disasm->all_jumps);
    ::init(&disasm->disassembly_sections);
}

void free(psp_disassembly *disasm)
{
    assert(disasm != nullptr);

    ::free(&disasm->disassembly_sections);
    ::free(&disasm->all_jumps);
    ::free(&disasm->all_instructions);
    free(&disasm->psp_module);
}

static void _add_symbols_to_jumps(set<jump_destination> *jumps, hash_table<u32, elf_symbol> *syms)
{
    // this adds symbols as jumps so they appear in the disassembly
    for_hash_table(k, _, syms)
        ::insert_element(jumps, jump_destination{*k, jump_type::Jump});
}

static void _add_imports_to_jumps(set<jump_destination> *jumps, array<module_import> *mods)
{
    for_array(mod, mods)
    {
        for_array(func, &mod->functions)
            ::insert_element(jumps, jump_destination{func->address, jump_type::Jump});
    }
}

static void _add_exports_to_jumps(set<jump_destination> *jumps, array<module_export> *mods)
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

    file_stream log{};
    log.handle = stdout_handle();

    psp_parse_elf_config elfconf{};
    elfconf.section = ""_cs;
    elfconf.vaddr = INFER_VADDR;
    elfconf.verbose = false;
    elfconf.log = &log;

    if (!parse_psp_module_from_elf(in, &out->psp_module, &elfconf, err))
        return false;

    ::resize(&out->disassembly_sections, out->psp_module.sections.size);
    ::fill_memory((void*)out->disassembly_sections.data, 0, out->disassembly_sections.size * sizeof(psp_disassembly_section));
    ::init(&out->all_instructions);
    ::init(&out->all_jumps);
    
    for_array(i, sec, &out->psp_module.sections)
    {
        parse_instructions_config pconf;
        pconf.log = &log;
        pconf.vaddr = sec->vaddr;
        pconf.verbose = false;
        pconf.emit_pseudo = true;

        psp_disassembly_section *dsec = out->disassembly_sections.data + i;
        fill_memory(dsec, 0);
        dsec->section = sec;
        dsec->vaddr_end = sec->vaddr;
        dsec->instruction_start_index = (s32)out->all_instructions.size;

        if (sec->content_size > 0)
            parse_instructions(sec->content, sec->content_size, &out->all_instructions, &out->all_jumps, &pconf);

        assert((s32)out->all_instructions.size >= dsec->instruction_start_index);
        dsec->instruction_count = (s32)out->all_instructions.size - dsec->instruction_start_index;
    }

    _add_symbols_to_jumps(&out->all_jumps, &out->psp_module.symbols);
    _add_imports_to_jumps(&out->all_jumps, &out->psp_module.imported_modules);
    _add_exports_to_jumps(&out->all_jumps, &out->psp_module.exported_modules);

    // set instructions and jumps for sections
    for_array(dsec, &out->disassembly_sections)
    {
        if (dsec->instruction_count == 0)
            continue;

        dsec->instructions = out->all_instructions.data + dsec->instruction_start_index;
        assert(dsec->section->vaddr == dsec->instructions->address);

        u32 last_vaddr = (dsec->instructions + dsec->instruction_count - 1)->address;
        dsec->vaddr_end = last_vaddr;
        auto search_result = ::nearest_index_of(&out->all_jumps, dsec->section->vaddr, compare_ascending_p);
        s64 first_jump_idx = search_result.index;

        if (first_jump_idx < 0)
            first_jump_idx = 0;

        s64 i = first_jump_idx;

        while (i < out->all_jumps.size)
        {
            if (out->all_jumps[i].address > last_vaddr)
                break;

            i += 1;
        }

        dsec->jumps = out->all_jumps.data + first_jump_idx;
        dsec->jump_count = (s32)(i - first_jump_idx);

        for (s32 j = 0; j < dsec->jump_count; ++j)
        {
            if (out->all_jumps.data[j].type == jump_type::Jump)
                dsec->function_count += 1;
            else
                dsec->branch_count += 1;
        }

        assert(dsec->function_count + dsec->branch_count == dsec->jump_count);
    }

    return true;
}
