# liballegrex

A library for parsing PSP Allegrex MIPS instructions, comes with the psp-elfdump tool to dump (E)BOOT.BIN files.

## How to use
Here's an example program which uses liballegrex to disassemble an entire EBOOT.BIN and prints out information about the module.
View [disassemble.hpp](/src/allegrex/disassemble.hpp) for more details on disassembling.

```cpp
#include <stdio.h>
#include "allegrex/disassemble.hpp"

int main(int argc, const char *argv[])
{
    if (argc < 2)
        return -1;

    psp_disassembly disasm;
    init(&disasm);
    
    // disassemble from path given by first command line argument
    disassemble_psp_elf(argv[1], &disasm);

    elf_psp_module *module = &disasm.psp_module;

    printf("found psp module, total size: %lu\n", module->elf_size);
    printf(" name:       %s\n", module->module_info.name);
    printf(" attributes: %x\n", module->module_info.attribute);

    printf("\n with %lu imports:\n", module->imported_modules.size);

    for_array(import, &module->imported_modules)
    {
        printf("  import %s:\n", import->module_name);

        for_array(func_import, &import->functions)
            printf("    function %#x, nid %#x, %s\n", func_import->address, func_import->function->nid, func_import->function->name);
    }

    for_array(_export, &module->exported_modules)
    {
        printf("  export %s:\n", _export->module_name);

        for_array(func_export, &_export->functions)
            printf("    function %#x, nid %#x, %s\n", func_export->address, func_export->function->nid, func_export->function->name);

        for_array(var_export, &_export->variables)
            printf("    variable %#x, nid %#x, %s\n", var_export->address, var_export->variable->nid, var_export->variable->name);
    }

    printf("\n %lu sections:\n", module->sections.size);

    for_array(section, &module->sections)
        printf("  section %s at offset %#x, size %#lx, vaddr %#x\n", section->name, section->content_offset, section->content_size, section->vaddr);

    free(&disasm);

    return 0;
}
```

## Building

```sh
$ mkdir bin
$ cd bin
$ cmake ..
$ make
```

## How to include
Ideally use CMake, clone the repository or add it to your project as a submodule, then add the following to your CMakeLists.txt (adjust to the liballegrex version youre using):

```cmake
add_subdirectory(path/to/liballegrex)
target_link_libraries(your-target PRIVATE allegrex-1.0.2)
target_include_directories(your-target PRIVATE ${allegrex-1.0.2_SOURCES_DIR} path/to/mg/ext/imgui)
```

OR using [better-cmake](https://github.com/DaemonTsun/better-cmake), add the following to your targets external libs:

```cmake
LIB allegrex 1.0.2 "path/to/liballegrex" INCLUDE LINK
```

## psp-elfdump
PSP (E)BOOT.BIN Elf MIPS dumper tool loosely based on https://github.com/simonlindholm/sm64tools/tree/disasm-objfile .
Usage can be found [here](/psp-elfdump).

## Tests
The tests cover the parsing of all (known) Allegrex instructions, with multiple tests per instruction if an instruction has arguments.
Tests are optional and automatically detected if [t1](https://github.com/DaemonTsun/t1/) is installed.

To run tests, type `make runtests` in the binary directory.
