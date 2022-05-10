# liballegrex

A library for parsing PSP Allegrex MIPS instructions, comes with the psp-elfdump tool to dump (E)BOOT.BIN files.

## psp-elfdump
PSP (E)BOOT.BIN Elf MIPS dumper tool loosely based on https://github.com/simonlindholm/sm64tools/tree/disasm-objfile

psp-elfdump recognizes encrypted EBOOT.BIN files and automatically decrypts them if necessary.

### Usage
Disassembly of a PSP object file (e.g. an exectuable):

    $ psp-elfdump BOOT.BIN
    /* 0025b4 08804000 27bdffd0 */  addiu     $sp, $sp, -0x30
    /* 0025b8 08804004 00a06821 */  move      $t5, $a1
    /* 0025bc 08804008 30a30003 */  andi      $v1, $a1, 0x3
    ...

Disassembly of an encrypted PSP object file (e.g. EBOOT.BIN):

    $ psp-elfdump EBOOT.BIN
    /* 0025b4 08804000 27bdffd0 */  addiu     $sp, $sp, -0x30
    /* 0025b8 08804004 00a06821 */  move      $t5, $a1
    /* 0025bc 08804008 30a30003 */  andi      $v1, $a1, 0x3
    ...

Verbose output with more information:

    $ psp-elfdump -v EBOOT.BIN
    ELF is encrypted and has been decrypted.
    got little-endian mips
                  name                : offset   - size
    found section .text               : 000025b4 - 00109e38
    /* 0025b4 08804000 27bdffd0 */  addiu     $sp, $sp, -0x30
    /* 0025b8 08804004 00a06821 */  move      $t5, $a1
    /* 0025bc 08804008 30a30003 */  andi      $v1, $a1, 0x3
    ...
    
Dumping an encrypted PSP executable to an unencrypted one:

    $ psp-elfdump --dump-decrypt out.bin EBOOT.BIN
    
See `psp-elfdump -h` for formatting options, disassembly of ranges, setting of the vaddr, etc..

## Tests
The tests cover the parsing of all (known) Allegrex instructions, with multiple tests per instruction if an instruction has arguments.
Tests are optional and automatically detected if [t1](https://github.com/DaemonTsun/t1/) is installed.

To run tests, type `make runtests` in the binary directory.
