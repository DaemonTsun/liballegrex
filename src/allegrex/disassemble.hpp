
#pragma once

#include "allegrex/psp_elf.hpp"
#include "allegrex/parse_instructions.hpp"

struct psp_disassembly
{
    // contains info about the psp module inside the parsed file,
    // e.g. name, type, and holds the information about the
    // sections, imported / exported modules, and symbols.
    // also stores all the data (binary sections, strings, ...).
    elf_psp_module psp_module;

    // holds the information about all parsed instructions, split by
    // section. each instruction_parse_data holds a section_index
    // member indicating which section they belong to.
    array<instruction_parse_data> instruction_datas;

    // an array of all jump destinations (e.g. section starts,
    // functions, branches, etc.) in the disassembled binary, storing
    // addresses and types, sorted by ascending address.
    jump_destinations jumps;
};

void init(psp_disassembly *disasm);
void free(psp_disassembly *disasm);

bool disassemble_psp_elf(const char *path, psp_disassembly *out, error *err);
bool disassemble_psp_elf(char *data, u64 size, psp_disassembly *out, error *err);
bool disassemble_psp_elf(memory_stream *in, psp_disassembly *out, error *err);
