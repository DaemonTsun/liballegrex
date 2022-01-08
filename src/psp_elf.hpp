
#pragma once

#include "file.hpp"

struct psp_elf_read_config
{
    file *in;

    bool verbose;
    file *log;
};
