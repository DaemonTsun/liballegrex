
#pragma once

#include "file_buffer.hpp"
#include "number_types.hpp"

#define INFER_VADDR UINT32_MAX

struct psp_elf_read_config
{
    file_buffer *in;

    u32 vaddr;
    bool verbose;
    file_buffer *log;
};

void read_elf(psp_elf_read_config *conf, void *out);
