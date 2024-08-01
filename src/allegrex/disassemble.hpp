
#pragma once

#include "allegrex/psp_elf.hpp"
#include "allegrex/parse_instructions.hpp"

/*
DISASSEMBLY STRUCTURE:
    psp_disassembly
      - psp_module
          - raw data
          - prx module info
          - symbols
              - address and name
          - function imports
              - address and function info
          - module imports
              - name
              - array of function imports
          - module exports
              - name
              - array of function imports
          - relocations
          - sections
              - name
              - offset in elf
              - size
              - vaddr
      - instructions, array of all instructions, sorted by vaddr
      - jumps, array of all jumps, sorted by vaddr
      - disasm sections
          - pointer to elf section
          - instruction start & end: indices into instructions array within section
          - jumps start & end: indices into jumps array within section
    
 */

struct psp_disassembly_section
{
    elf_section *section;
    instruction *instructions;
    s32 instruction_start_index; // index into all_instructions array
    s32 instruction_count;
    jump_destination *jumps; // jumps that target _inside the section_
    s32 jump_count;
};

struct psp_disassembly
{
    /* contains info about the psp module inside the parsed file,
       e.g. name, type, and holds the information about the
       sections, imported / exported modules, and symbols.
       also stores all the data (binary sections, strings, ...). */
    elf_psp_module psp_module;

    /* Array of all instructions in the disassembly, sorted by ascending address. */
    array<instruction> all_instructions;

    /* Set of all jump destinations (e.g. section starts,
       functions, branches, etc.) in the disassembled binary, storing
       addresses and jump types, sorted by ascending address. */
    set<jump_destination> all_jumps;

    /* Sections with additional information */ 
    array<psp_disassembly_section> disassembly_sections;
};

void init(psp_disassembly *disasm);
void free(psp_disassembly *disasm);

bool disassemble_psp_elf(const char *path, psp_disassembly *out, error *err);
bool disassemble_psp_elf(char *data, u64 size, psp_disassembly *out, error *err);
bool disassemble_psp_elf(memory_stream *in, psp_disassembly *out, error *err);
