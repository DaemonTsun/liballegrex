
#pragma once

#include "file_stream.hpp"
#include "memory_stream.hpp"
#include "number_types.hpp"

#define INFER_VADDR UINT32_MAX

struct psp_elf_read_config
{
    std::string section;
    u32 vaddr;
    bool verbose;
    file_stream *log;
};

struct elf_symbol
{
    u32 address;
    std::string name;
};

void read_elf(file_stream *in, const psp_elf_read_config *conf, void *out);
void read_elf(memory_stream *in, const psp_elf_read_config *conf, void *out);

