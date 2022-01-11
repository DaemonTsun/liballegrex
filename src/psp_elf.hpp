
#pragma once

#include "file_buffer.hpp"
#include "number_types.hpp"

#define INFER_VADDR UINT32_MAX

struct psp_elf_read_config
{
    file_buffer *in;

    std::string section;
    u32 vaddr;
    bool verbose;
    file_buffer *log;
};

struct elf_symbol
{
    u32 address;
    std::string name;
};

void read_elf(const psp_elf_read_config *conf, void *out);
