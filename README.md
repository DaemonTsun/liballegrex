# liballegrex

A library for parsing PSP Allegrex MIPS instructions, comes with the psp-elfdump tool to dump (E)BOOT.BIN files.

## psp-elfdump
PSP (E)BOOT.BIN Elf MIPS dumper tool loosely based on https://github.com/simonlindholm/sm64tools/tree/disasm-objfile

psp-elfdump recognizes encrypted EBOOT.BIN files and automatically decrypts them if necessary.

## Tests
The tests cover the parsing of all (known) Allegrex instructions, with multiple tests per instruction if an instruction has arguments.
Tests are optional and automatically detected if [t1](https://github.com/DaemonTsun/t1/) is installed.

To run tests, type `make runtests` in the binary directory.
