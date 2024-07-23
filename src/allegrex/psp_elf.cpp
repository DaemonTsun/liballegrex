
#include <assert.h>
#include <string.h>

#include "shl/compare.hpp"
#include "shl/streams.hpp"
#include "shl/fixed_array.hpp"
#include "shl/error.hpp"
#include "shl/print.hpp"
#include "shl/defer.hpp"
#include "shl/platform.hpp"

#include "allegrex/psp_modules.hpp"
#include "allegrex/internal/psp_module_function_argument_defs.hpp"
#include "allegrex/internal/psp_module_function_pspdev_headers.hpp"
#include "allegrex/psp_prx.hpp"
#include "allegrex/prx_decrypt.hpp"
#include "allegrex/psp_elf.hpp"


#if Windows
#define EI_NIDENT 16

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;
typedef uint16_t Elf32_Section;
typedef uint16_t Elf32_Versym;
typedef unsigned char Elf_Byte;
typedef uint16_t Elf32_Half;
typedef int32_t  Elf32_Sword;
typedef uint32_t Elf32_Word;
typedef int64_t  Elf32_Sxword;
typedef uint64_t Elf32_Xword;

typedef struct
{
    unsigned char e_ident[EI_NIDENT];
    uint16_t      e_type;
    uint16_t      e_machine;
    uint32_t      e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    uint32_t      e_flags;
    uint16_t      e_ehsize;
    uint16_t      e_phentsize;
    uint16_t      e_phnum;
    uint16_t      e_shentsize;
    uint16_t      e_shnum;
    uint16_t      e_shstrndx;
} Elf32_Ehdr;

typedef struct
{
    uint32_t   p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    uint32_t   p_filesz;
    uint32_t   p_memsz;
    uint32_t   p_flags;
    uint32_t   p_align;
} Elf32_Phdr;

typedef struct
{
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint32_t   sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    uint32_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint32_t   sh_addralign;
    uint32_t   sh_entsize;
} Elf32_Shdr;

typedef struct
{
    uint32_t      st_name;
    Elf32_Addr    st_value;
    uint32_t      st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
} Elf32_Sym;

typedef struct {
    Elf32_Addr r_offset;
    uint32_t   r_info;
} Elf32_Rel;

#define ELF32_R_SYM(x) ((x) >> 8)
#define ELF32_R_TYPE(x) ((x) & 0xff)

#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_HASH     5
#define SHT_DYNAMIC  6
#define SHT_NOTE     7
#define SHT_NOBITS   8
#define SHT_REL      9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11
#define SHT_NUM      12
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff

#define EI_MAG0    0
#define EI_MAG1    1
#define EI_MAG2    2
#define EI_MAG3    3
#define EI_CLASS   4
#define EI_DATA    5
#define EI_VERSION 6
#define EI_OSABI   7
#define EI_PAD     8

#define ELFCLASSNONE 0
#define ELFCLASS32   1
#define ELFCLASS64   2
#define ELFCLASSNUM  3

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define EV_NONE     0
#define EV_CURRENT  1
#define EV_NUM      2

#define SHF_WRITE          0x1
#define SHF_ALLOC          0x2
#define SHF_EXECINSTR      0x4
#define SHF_RELA_LIVEPATCH 0x00100000
#define SHF_RO_AFTER_INIT  0x00200000
#define SHF_MASKPROC       0xf0000000

#define SHN_UNDEF     0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_LIVEPATCH 0xff20
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_HIRESERVE 0xffff

#define EM_MIPS		8	
#else
#include <elf.h>
#endif

/*
#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6
*/

constexpr fixed_array syslib_functions
{
    psp_function{ 0xd632acdb, "module_start",
                  RET(ARG_S32), ARGS(ARG_SceSize, ARG_VOID_PTR),
                  no_header, 0, 0 },
    psp_function{ 0xcee8593c, "module_stop",
                  RET(ARG_S32), ARGS(ARG_SceSize, ARG_VOID_PTR),
                  no_header, 0, 1 }
};

constexpr fixed_array syslib_variables
{
    psp_variable{ 0x0f7c276c, "module_start_thread_parameter" },
    psp_variable{ 0xcf0cc697, "module_stop_thread_parameter" },
    psp_variable{ 0xf01d73a7, "module_info" },
    psp_variable{ 0x11b97506, "module_sdk_version" }
};

const psp_function *_get_syslib_function(u32 nid)
{
    for_array(fn, &syslib_functions)
        if (fn->nid == nid)
            return fn;

    return nullptr;
}

const psp_variable *_get_syslib_variable(u32 nid)
{
    for_array(vr, &syslib_variables)
        if (vr->nid == nid)
            return vr;

    return nullptr;
}

#define log(CONF, ...) \
    { if (CONF != nullptr && CONF->verbose && CONF->log != nullptr) { tprint(CONF->log->handle, __VA_ARGS__); }};

template<typename T>
void read_section(memory_stream *in, const Elf32_Ehdr *ehdr, int index, T *out)
{
    read_at(in, out, ehdr->e_shoff + (index) * ehdr->e_shentsize);
}

struct elf_read_ctx
{
    memory_stream *in;
    const psp_parse_elf_config *conf;
    const Elf32_Ehdr *elf_header;
    const char *string_table_data;
    u32 min_vaddr;
    u32 max_vaddr;
    u32 min_offset;
    u32 max_offset;
};

#define file_offset_from_vaddr(ctx, vaddr) ((vaddr - ctx->min_vaddr) + ctx->min_offset)

void _add_section_to_symbols(elf_read_ctx *ctx, int section_index, hash_table<u32, elf_symbol> *symbols)
{
    // there's a good chance symbols don't exist, but we add them anyway
    for (int i = 0; i < ctx->elf_header->e_shnum; i++)
    {
        Elf32_Shdr sec_header;
        read_section(ctx->in, ctx->elf_header, i, &sec_header);
        const char *section_name = ctx->string_table_data + sec_header.sh_name;

        if (sec_header.sh_type != SHT_SYMTAB)
            continue;

        assert(sec_header.sh_entsize == sizeof(Elf32_Sym));

        if (sec_header.sh_size == 0)
            // log empty tables maybe?
            continue;

        log(ctx->conf, "found symtab %s\n", section_name);

        Elf32_Shdr strtab_header;
        read_section(ctx->in, ctx->elf_header, sec_header.sh_link, &strtab_header);

        const char *sec_string_table = ctx->in->data + strtab_header.sh_offset;

        for (u32 j = 0; j < sec_header.sh_size; j += sizeof(Elf32_Sym))
        {
            Elf32_Sym sym;
            read_at(ctx->in, &sym, sec_header.sh_offset + j);

            const char *name = sec_string_table + sym.st_name;

            if (strlen(name) == 0)
                continue;

            if (sym.st_shndx != section_index) //|| name[0] == '.')
                continue;

            log(ctx->conf, "  symbol at %08x: '%s'\n", sym.st_value, name);

            (*symbols)[sym.st_value] = elf_symbol{sym.st_value, name};
        }
    }
}

// TODO: actually add relocation information
// currently only logs relocations
// do games have relocations...?
void _add_relocations(elf_read_ctx *ctx, array<elf_relocation> *out)
{
    for (int i = 0; i < ctx->elf_header->e_shnum; ++i)
    {
        Elf32_Shdr sec_header;
        read_section(ctx->in, ctx->elf_header, i, &sec_header);

        if (sec_header.sh_type != SHT_REL
        // || sec_header.sh_info != (u32)section_index
         )
            continue;

        const char *section_name = ctx->string_table_data + sec_header.sh_name;

        assert(sec_header.sh_entsize == sizeof(Elf32_Rel));

        if (sec_header.sh_size == 0)
            // log empty tables maybe?
            continue;

        log(ctx->conf, "got relocation table %s\n", section_name);

        for (u32 j = 0; j < sec_header.sh_size; j += sizeof(Elf32_Rel))
        {
            Elf32_Rel rel;
            read_at(ctx->in, &rel, sec_header.sh_offset + j);
            u32 index = ELF32_R_SYM(rel.r_info);
            u32 type = ELF32_R_TYPE(rel.r_info);

            log(ctx->conf, "  relocation %08x, %d %d\n", rel.r_offset, index, type);
        }
    }
}

bool _get_section_header_by_name(elf_read_ctx *ctx, const char *name, Elf32_Shdr *out)
{
    if (out == nullptr)
        return false;

    for (int i = 0; i < ctx->elf_header->e_shnum; i++)
    {
        read_section(ctx->in, ctx->elf_header, i, out);

        const char *section_name = ctx->string_table_data + out->sh_name;

        if (strcmp(section_name, name) == 0)
            return true;
    }

    return false;
}

void _read_prx_sce_module_info_section_header(elf_read_ctx *ctx, prx_sce_module_info *out)
{
    assert(out != nullptr);

    Elf32_Shdr sceModuleInfo_section_header;

    log(ctx->conf, "\n");

    if (!_get_section_header_by_name(ctx, ELF_SECTION_PRX_MODULE_INFO, &sceModuleInfo_section_header))
    {
        log(ctx->conf, "could not find section '%s'\n", ELF_SECTION_PRX_MODULE_INFO);
        return;
    }

    log(ctx->conf, "found .rodata.sceModuleInfo section at %08x (size %08x):\n", sceModuleInfo_section_header.sh_offset, sceModuleInfo_section_header.sh_size);

    read_at(ctx->in, out, sceModuleInfo_section_header.sh_offset);

    log(ctx->conf, "  attribute: %04x\n", out->attribute);
    log(ctx->conf, "  versions:  %02x %02x\n", out->version[0], out->version[1]);
    log(ctx->conf, "  name:      %s\n", out->name);
    log(ctx->conf, "  gp:        %08x\n", out->gp);
    log(ctx->conf, "  export:    %08x - %08x\n", out->export_offset_start, out->export_offset_end);
    log(ctx->conf, "  import:    %08x - %08x\n", out->import_offset_start, out->import_offset_end);
    log(ctx->conf, "\n");
}

void _add_prx_exports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info, elf_psp_module *out)
{
    u32 sz = mod_info->export_offset_end - mod_info->export_offset_start;
    assert((sz % sizeof(prx_module_export)) == 0);

    u32 count = sz / sizeof(prx_module_export);
    ::reserve(&out->exported_modules, count);

    for (u32 i = 0; i < sz; i += sizeof(prx_module_export))
    {
        prx_module_export exp;
        read_at(ctx->in, &exp, file_offset_from_vaddr(ctx, mod_info->export_offset_start) + i);

        const char *module_name;

        if (exp.name_vaddr == 0)
            module_name = PRX_SYSTEM_EXPORT;
        else
            module_name = ctx->in->data + file_offset_from_vaddr(ctx, exp.name_vaddr);

        log(ctx->conf, "export module %s: %08x %08x %02x %02x %04x %08x\n", module_name, exp.name_vaddr, exp.flags, exp.entry_size, exp.variable_count, exp.function_count, exp.exports_vaddr);
        log(ctx->conf, "  %08x\n", file_offset_from_vaddr(ctx, exp.exports_vaddr));

        module_export *me = ::add_at_end(&out->exported_modules);
        ::init(&me->functions);
        ::init(&me->variables);

        me->module_name = module_name;

        for (u32 _j = 0; _j < exp.function_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 f_vaddr_vaddr = exp.exports_vaddr + j + sizeof(u32) * (exp.function_count + exp.variable_count);
            u32 f_vaddr;
            u32 nid;

            read_at(ctx->in, &nid, file_offset_from_vaddr(ctx, exp.exports_vaddr) + j);
            read_at(ctx->in, &f_vaddr, file_offset_from_vaddr(ctx, f_vaddr_vaddr));

            const psp_function *pf = _get_syslib_function(nid);

            if (pf == nullptr)
            {
                // TODO: maybe dont ignore these
                log(ctx->conf, "  export unknown function nid %08x at %08x\n", nid, f_vaddr);
                continue;
            }

            log(ctx->conf, "  export function nid %08x at %08x: %s\n", nid, f_vaddr, pf->name);

            ::add_at_end(&me->functions, function_export{f_vaddr, pf});
        }

        // variables
        u32 v_offset = exp.exports_vaddr + exp.function_count * sizeof(u32);
        for (u32 _j = 0; _j < exp.variable_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 v_vaddr_vaddr = v_offset + j + sizeof(u32) * (exp.function_count + exp.variable_count);
            u32 v_vaddr;
            u32 nid;

            read_at(ctx->in, &nid, file_offset_from_vaddr(ctx, v_offset) + j);
            read_at(ctx->in, &v_vaddr, file_offset_from_vaddr(ctx, v_vaddr_vaddr));

            const psp_variable *pv = _get_syslib_variable(nid);

            if (pv == nullptr)
            {
                // TODO: maybe dont ignore these
                log(ctx->conf, "  export unknown variable nid %08x at %08x\n", nid, v_vaddr);
                continue;
            }

            log(ctx->conf, "  export variable nid %08x at %08x: %s\n", nid, v_vaddr, pv->name);

            ::add_at_end(&me->variables, variable_export{v_vaddr, pv});
        }
    }

    log(ctx->conf, "\n");
}

void _add_prx_imports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info, elf_psp_module *out)
{
    u32 sz = mod_info->import_offset_end - mod_info->import_offset_start;
    assert((sz % sizeof(prx_module_import)) == 0);
    assert(out != nullptr);

    u32 count = sz / sizeof(prx_module_import);
    ::reserve(&out->imported_modules, count);

    for (u32 i = 0; i < sz; i += sizeof(prx_module_import))
    {
        prx_module_import imp;
        read_at(ctx->in, &imp, file_offset_from_vaddr(ctx, mod_info->import_offset_start) + i);

        const char *module_name = ctx->in->data + file_offset_from_vaddr(ctx, imp.name_vaddr);

        log(ctx->conf, "import %s: %08x %08x %02x %02x %04x %08x %08x\n",
                       module_name, imp.name_vaddr, imp.flags,
                       imp.entry_size, imp.variable_count, imp.function_count,
                       imp.nids_vaddr, imp.functions_vaddr);

        module_import *mi = ::add_at_end(&out->imported_modules);
        ::init(&mi->functions);
        mi->module_name = module_name;

        for (u32 _j = 0; _j < imp.function_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 f_vaddr = imp.functions_vaddr + j * 2;
            u32 nid;

            read_at(ctx->in, &nid, file_offset_from_vaddr(ctx, imp.nids_vaddr) + j);

            const psp_function *pf = get_psp_function_by_nid(module_name, nid);

            if (pf == nullptr)
            {
                // TODO: maybe dont ignore these
                log(ctx->conf, "  import unknown function nid %08x at %08x\n", nid, f_vaddr);
                continue;
            }

            log(ctx->conf, "  import function nid %08x at %08x: %s\n", nid, f_vaddr, pf->name);

            function_import impf{f_vaddr, pf};
            out->imports[f_vaddr] = impf;
            ::add_at_end(&mi->functions, impf);
        }

        // TODO: import variables

        log(ctx->conf, "\n");
    }
}

void _add_prx_imports_and_exports(elf_read_ctx *ctx, elf_psp_module *out)
{
    prx_sce_module_info *mod_info = &out->module_info;
    _read_prx_sce_module_info_section_header(ctx, mod_info);

    _add_prx_exports(ctx, mod_info, out);
    _add_prx_imports(ctx, mod_info, out);
}

void _get_elf_min_max_offsets_and_vaddrs(memory_stream *in, const Elf32_Ehdr *elf_header, elf_read_ctx *out)
{
    out->min_vaddr = 0xFFFFFFFF;
    out->max_vaddr = 0;
    out->min_offset = 0xFFFFFFFF;
    out->max_offset = 0;

    Elf32_Shdr section_header;

    // find elf section offsets (need the values for address calculations)
    for (int i = 0; i < elf_header->e_shnum; ++i)
    {
        read_section(in, elf_header, i, &section_header);

        if ((section_header.sh_type & SHT_NOBITS) == SHT_NOBITS)
            continue;

        if (section_header.sh_addr == 0 || section_header.sh_offset == 0)
            continue;

        if (section_header.sh_addr < out->min_vaddr)
            out->min_vaddr = section_header.sh_addr;

        if (section_header.sh_addr + section_header.sh_size > out->max_offset)
            out->max_vaddr = section_header.sh_addr + section_header.sh_size;

        if (section_header.sh_offset < out->min_offset)
            out->min_offset = section_header.sh_offset;

        if (section_header.sh_offset + section_header.sh_size > out->max_offset)
            out->max_offset = section_header.sh_offset + section_header.sh_size;
    }
}

// returns the pointer to the start of the string table in the memory stream
const char *_get_string_table(memory_stream *in, const Elf32_Ehdr *elf_header)
{
    Elf32_Shdr string_table_header;
    read_section(in, elf_header, elf_header->e_shstrndx, &string_table_header);

    return in->data + string_table_header.sh_offset;
}

void init(elf_psp_module *mod)
{
    assert(mod != nullptr);

    mod->elf_data = nullptr;
    mod->elf_size = 0;

    ::init(&mod->relocations);
    ::init(&mod->sections);

    ::init(&mod->symbols);
    ::init(&mod->imports);

    ::init(&mod->imported_modules);
    ::init(&mod->exported_modules);
}

void free(elf_psp_module *mod)
{
    assert(mod != nullptr);

    if (mod->elf_data != nullptr)
        dealloc(mod->elf_data, mod->elf_size);

    ::free(&mod->relocations);
    ::free(&mod->sections);

    for_array(imp, &mod->imported_modules)
        ::free(&imp->functions);

    ::free(&mod->imported_modules);

    for_array(exp, &mod->exported_modules)
    {
        ::free(&exp->functions);
        ::free(&exp->variables);
    }

    ::free(&mod->exported_modules);

    ::free(&mod->symbols);
    ::free(&mod->imports);
}

bool _read_elf(elf_psp_module *out, const psp_parse_elf_config *conf, error *err)
{
    memory_stream in{};
    in.data = out->elf_data;
    in.size = out->elf_size;

    Elf32_Ehdr elf_header;

    if (in.size < (s64)sizeof(Elf32_Ehdr))
    {
        set_error(err, 1, "input is not an ELF file");
        return false;
    }

    read(&in, &elf_header);

    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
    {
        set_error(err, 1, "input is not an ELF file");
        return false;
    }

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
    {
        set_error(err, 1, "input is not little-endian MIPS");
        return false;
    }

    log(conf, "%s\n", "got little-endian mips");

    if (elf_header.e_shstrndx == SHN_UNDEF)
    {
        // while we could look at program headers, PSP games
        // can have strange sections (e.g. MHFU has ~600 sections, a lot of them empty)
        // so we usually rely on the name given by command line args, or disassemble
        // all executable sections instead.
        set_error(err, 1, "no section header table index found");
        return false;
    }

    const char *string_table_ptr = _get_string_table(&in, &elf_header);

    Elf32_Shdr section_header;

    array<int> section_indices;
    init(&section_indices);
    defer { free(&section_indices); };

    log(conf, "              %-20s: offset   - size\n", "name");

    int section_header_count = elf_header.e_shnum;

    for (int i = 0; i < section_header_count; ++i)
    {
        read_section(&in, &elf_header, i, &section_header);
        const char *section_name = string_table_ptr + section_header.sh_name;

        if (::is_blank(conf->section))
        {
            if ((section_header.sh_flags & SHF_EXECINSTR) == 0) // ignore non-executable sections
                continue;
        }
        else if (compare_strings(conf->section, section_name) != 0)
            continue;

        log(conf, "found executable section %-20s: %08x - %08x\n", section_name, section_header.sh_offset, section_header.sh_size);
        ::add_at_end(&section_indices, i);
    }

    if (section_indices.size == 0)
    {
        if (::is_blank(conf->section))
        {
            set_error(err, 1, "no executable sections found in input file");
            return false;
        }
        else
        {
            format_error(err, 1, "section '%s' not found in input file", conf->section.c_str);
            return false;
        }
    }

    elf_read_ctx ctx;
    ctx.in = &in;
    ctx.conf = conf;
    ctx.elf_header = &elf_header;
    ctx.string_table_data = string_table_ptr;
    _get_elf_min_max_offsets_and_vaddrs(&in, &elf_header, &ctx);
    
    log(conf, "min section vaddr:  %08x, max section vaddr:  %08x\n", ctx.min_vaddr,  ctx.max_vaddr);
    log(conf, "min section offset: %08x, max section offset: %08x\n", ctx.min_offset, ctx.max_offset);

    _add_relocations(&ctx, &out->relocations);

    for_array(_i, &section_indices)
    {
        int i = *_i;
        read_section(&in, &elf_header, i, &section_header);
        const char *section_name = string_table_ptr + section_header.sh_name;

        elf_section *esec = ::add_at_end(&out->sections);
        esec->name = section_name;

        u32 vaddr = conf->vaddr;

        if (conf->vaddr == INFER_VADDR)
            vaddr = section_header.sh_addr;

        esec->vaddr = vaddr;

        out->symbols[vaddr] = elf_symbol{vaddr, section_name};
        _add_section_to_symbols(&ctx, i, &out->symbols);

        esec->content = in.data + section_header.sh_offset;
        esec->content_size = section_header.sh_size;
        esec->content_offset = section_header.sh_offset;
    }

    _add_prx_imports_and_exports(&ctx, out);

    return true;
}

#define DEFAULT_PARSE_ELF_CONFIG(NAME)\
    file_stream log;\
    log.handle = stdout_handle();\
\
    psp_parse_elf_config NAME;\
    NAME.section = ""_cs;\
    NAME.vaddr = INFER_VADDR;\
    NAME.verbose = false;\
    NAME.log = &log;

bool parse_psp_module_from_elf(const char *path, elf_psp_module *out, error *err)
{
    assert(path != nullptr);
    assert(out != nullptr);

    DEFAULT_PARSE_ELF_CONFIG(conf);

    return parse_psp_module_from_elf(path, out, &conf, err);
}

bool parse_psp_module_from_elf(const char *path, elf_psp_module *out, const psp_parse_elf_config *conf, error *err)
{
    assert(path != nullptr);
    assert(out != nullptr);

    memory_stream elf_stream{};

    if (!read_entire_file(path, &elf_stream, err))
        return false;

    defer { ::free(&elf_stream); };

    return parse_psp_module_from_elf(&elf_stream, out, conf, err);
}

bool parse_psp_module_from_elf(char *elf_data, u64 elf_size, elf_psp_module *out, error *err)
{
    assert(elf_data != nullptr);
    assert(out != nullptr);

    DEFAULT_PARSE_ELF_CONFIG(conf);

    return parse_psp_module_from_elf(elf_data, elf_size, out, &conf, err);
}

bool parse_psp_module_from_elf(char *elf_data, u64 elf_size, elf_psp_module *out, const psp_parse_elf_config *conf, error *err)
{
    assert(elf_data != nullptr);
    assert(out != nullptr);

    memory_stream in;
    in.data = elf_data;
    in.size = elf_size;
    in.position = 0;

    return parse_psp_module_from_elf(&in, out, conf, err);
}

bool parse_psp_module_from_elf(memory_stream *elf_stream, elf_psp_module *out, error *err)
{
    assert(elf_stream != nullptr);
    assert(out != nullptr);

    DEFAULT_PARSE_ELF_CONFIG(conf);

    return parse_psp_module_from_elf(elf_stream, out, &conf, err);
}

bool parse_psp_module_from_elf(memory_stream *elf_stream, elf_psp_module *out, const psp_parse_elf_config *conf, error *err)
{
    assert(elf_stream != nullptr);
    assert(out != nullptr);

    array<u8> decrypted_elf{};

    s64 sz = decrypt_elf(elf_stream, &decrypted_elf, err);

    if (sz < 0)
        return false;

    if (sz > 0)
    {
        log(conf, "ELF is encrypted and has been decrypted.\n");

        out->elf_data = (char*)decrypted_elf.data;
        out->elf_size = decrypted_elf.size;

        return _read_elf(out, conf, err);
    }

    free(&decrypted_elf);

    // elf is not encrypted, copy it to the module
    out->elf_data = alloc<char>(elf_stream->size);
    out->elf_size = elf_stream->size;
    copy_memory(elf_stream->data, out->elf_data, elf_stream->size);

    return _read_elf(out, conf, err);
}

s64 decrypt_elf(file_stream *in, array<u8> *out, error *err)
{
    memory_stream memstr;
    init(&memstr, get_file_size(in));
    defer { free(&memstr); };

    read_at(in, memstr.data, 0, in->cached_size);

    return decrypt_elf(&memstr, out, err);
}

s64 decrypt_elf(memory_stream *in, array<u8> *out, error *err)
{
    if (in->size < (s64)sizeof(Elf32_Ehdr))
    {
        set_error(err, 1, "input is not an ELF file");
        return -1;
    }

    char magic[4];
    read(in, magic, 4);

    if (strncmp(magic, "\x7f" "ELF", 4))
    {
        // not an ELF, might be encrypted
        if (strncmp(magic, "~PSP", 4))
        {
            // nope, not encrypted either
            set_error(err, 1, "input is not an ELF file and is not encrypted");
            return -1;
        }

        // ok its encrypted, attempt decrypt
        PSP_Header phead;
        read_at(in, &phead, 0);

        u64 nsize = Max(phead.elf_size, phead.psp_size);
        resize(out, nsize);

        int decrypted_size = pspDecryptPRX(reinterpret_cast<const u8*>(in->data),
                                           out->data,
                                           phead.psp_size);

        if (decrypted_size < 0)
        {
            set_error(err, 1, "could not decrypt input file");
            return -1;
        }

        /* TODO: implement gzip
        const auto isGzip = phead.comp_attribute & 1;
        if (isGzip)
            ...
        */

        return decrypted_size;
    }

    // nothing to decrypt
    return 0;
}
