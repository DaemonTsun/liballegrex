
#pragma once

#include "number_types.hpp"

// prx structures

#define PRX_MODULE_NAME_LEN 28

struct prx_sce_module_info
{
	u32 flags;
	char name[PRX_MODULE_NAME_LEN];
	u32 gp; // ?
	u32 export_offset_start;
	u32 export_offset_end;
	u32 import_offset_start;
	u32 import_offset_end;
};

struct prx_module_export
{
	u32 name_vaddr;
	u32 flags;
    u8  entry_size;
    u8  variable_count;
    u16 function_count;
	u32 exports_vaddr;
};

struct prx_module_import
{
    u32 name_vaddr;
    u32 flags;
    u8  entry_size;
    u8  variable_count;
    u16 function_count;
    u32 nids_vaddr;
    u32 functions_vaddr;
};

