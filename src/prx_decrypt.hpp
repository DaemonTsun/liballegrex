
#pragma once

#include "number_types.hpp"
#include "number_swap.hpp"

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif
typedef struct
{
	u32_le      signature;       // 0
	u16_le      attribute;       // 4  modinfo
	u16_le      comp_attribute;  // 6
	u8          module_ver_lo;   // 8
	u8          module_ver_hi;   // 9
	char        modname[28];     // 0A
	u8          version;         // 26
	u8          nsegments;       // 27
	u32_le      elf_size;        // 28
	u32_le      psp_size;        // 2C
	u32_le      entry;           // 30
	u32_le      modinfo_offset;  // 34
	s32_le      bss_size;        // 38
	u16_le      seg_align[4];    // 3C
	u32_le      seg_address[4];  // 44
	s32_le      seg_size[4];     // 54
	u32_le      reserved[5];     // 64
	u32_le      devkitversion;   // 78
	u32_le      decrypt_mode;    // 7C 
	u8          key_data0[0x30]; // 80
	s32_le      comp_size;       // B0
	s32_le      _80;             // B4
	s32_le      reserved2[2];    // B8
	u8          key_data1[0x10]; // C0
	u32_le      tag;             // D0
	u8          scheck[0x58];    // D4
	u32_le      key_data2;       // 12C
	u32_le      oe_tag;          // 130
	u8          key_data3[0x1C]; // 134
#ifdef _MSC_VER
} PSP_Header;
#else
} __attribute__((packed)) PSP_Header;
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

int pspDecryptPRX(const u8 *inbuf, u8 *outbuf, u32 size, const u8 *seed = nullptr);

