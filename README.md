# psp-elfdump
PSP (E)BOOT.BIN Elf MIPS dumper tool based on https://github.com/simonlindholm/sm64tools/tree/disasm-objfile

Right now psp-elfdump requires unencrypted Elf files as input.
To unencrypt EBOOT.BIN, use e.g. PPSSPP.

Differences from the original N64 tool:
- Endianness of PSP EBOOT.BIN executables are little-endian, not big-endian
- Fixed reading the virtual address of the first instruction
- Add (partial) support for stripped exectuables that don't have symbol/string tables

## Usage:

    $ psp-elfdump EBOOT.BIN -o EBOOT.BIN.s
