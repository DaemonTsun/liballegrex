
#include <vector>

#include <elf.h>
#include <assert.h>
#include <string.h>

#include "shl/error.hpp"

#include "allegrex/psp_modules.hpp"
#include "allegrex/internal/psp_module_function_argument_defs.hpp"
#include "allegrex/internal/psp_module_function_pspdev_headers.hpp"
#include "allegrex/psp_prx.hpp"
#include "allegrex/prx_decrypt.hpp"
#include "allegrex/psp_elf.hpp"

/*
#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6
*/

constexpr std::array syslib_functions
{
    psp_function{ 0xd632acdb, "module_start",
                  RET(ARG_S32), ARGS(ARG_SceSize, ARG_VOID_PTR),
                  no_header, 0, 0 },
    psp_function{ 0xcee8593c, "module_stop",
                  RET(ARG_S32), ARGS(ARG_SceSize, ARG_VOID_PTR),
                  no_header, 0, 1 }
};

constexpr std::array syslib_variables
{
    psp_variable{ 0x0f7c276c, "module_start_thread_parameter" },
    psp_variable{ 0xcf0cc697, "module_stop_thread_parameter" },
    psp_variable{ 0xf01d73a7, "module_info" },
	psp_variable{ 0x11b97506, "module_sdk_version" }
};

const psp_function *get_syslib_function(u32 nid)
{
    for (int i = 0; i < syslib_functions.size(); ++i)
    {
        const psp_function *fn = &syslib_functions.at(i);

        if (fn->nid == nid)
            return fn;
    }

    return nullptr;
}

const psp_variable *get_syslib_variable(u32 nid)
{
    for (int i = 0; i < syslib_variables.size(); ++i)
    {
        const psp_variable *vr = &syslib_variables.at(i);

        if (vr->nid == nid)
            return vr;
    }

    return nullptr;
}

#define log(CONF, ...) {if (CONF->verbose && CONF->log != nullptr) {format(CONF->log,__VA_ARGS__);}};
// #define read_section(in, ehdr, index, out) in->read_at(out, ehdr.e_shoff + (index) * ehdr.e_shentsize);

template<typename T>
void read_section(memory_stream *in, const Elf32_Ehdr *ehdr, int index, T *out)
{
    read_at(in, out, ehdr->e_shoff + (index) * ehdr->e_shentsize);
}

struct elf_read_ctx
{
    memory_stream *in;
    const psp_elf_read_config *conf;
    const Elf32_Ehdr *elf_header;
    const char *string_table_data;
    u32 min_vaddr;
    u32 max_vaddr;
    u32 min_offset;
    u32 max_offset;
};

#define file_offset_from_vaddr(ctx, vaddr) ((vaddr - ctx->min_vaddr) + ctx->min_offset)

void add_symbols(elf_read_ctx *ctx, int section_index, symbol_map &symbols)
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

        std::vector<char> sec_string_table;
        sec_string_table.resize(strtab_header.sh_size);
        read_at(ctx->in, sec_string_table.data(), strtab_header.sh_offset, strtab_header.sh_size);

        for (u32 i = 0; i < sec_header.sh_size; i += sizeof(Elf32_Sym))
        {
            Elf32_Sym sym;
            read_at(ctx->in, &sym, sec_header.sh_offset + i);

            const char *name = sec_string_table.data() + sym.st_name;

            if (strlen(name) == 0)
                continue;

            if (sym.st_shndx != section_index) //|| name[0] == '.')
                continue;

            log(ctx->conf, "  symbol at %08x: '%s'\n", sym.st_value, name);
            symbols.emplace(sym.st_value, elf_symbol{sym.st_value, std::string(name)});
        }
    }
}

// TODO: actually add relocation information
// currently only logs relocations
// do games have relocations...?
void add_relocations(elf_read_ctx *ctx, std::vector<elf_relocation> &out)
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

bool get_section_header_by_name(elf_read_ctx *ctx, const char *name, Elf32_Shdr *out)
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

void read_prx_sce_module_info_section_header(elf_read_ctx *ctx, prx_sce_module_info *out)
{
    assert(out != nullptr);

    Elf32_Shdr sceModuleInfo_section_header;

    log(ctx->conf, "\n");

    if (!get_section_header_by_name(ctx, ELF_SECTION_PRX_MODULE_INFO, &sceModuleInfo_section_header))
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

void add_prx_exports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info, elf_parse_data *out)
{
    u32 sz = mod_info->export_offset_end - mod_info->export_offset_start;
    assert((sz % sizeof(prx_module_export)) == 0);

    u32 count = sz / sizeof(prx_module_export);
    out->exported_modules.reserve(count);

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

        module_export *me = &out->exported_modules.emplace_back();
        me->module_name = module_name;

        for (u32 _j = 0; _j < exp.function_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 f_vaddr_vaddr = exp.exports_vaddr + j + sizeof(u32) * (exp.function_count + exp.variable_count);
            u32 f_vaddr;
            u32 nid;

            read_at(ctx->in, &nid, file_offset_from_vaddr(ctx, exp.exports_vaddr) + j);
            read_at(ctx->in, &f_vaddr, file_offset_from_vaddr(ctx, f_vaddr_vaddr));

            const psp_function *pf = get_syslib_function(nid);

            if (pf == nullptr)
            {
                // TODO: maybe dont ignore these
                log(ctx->conf, "  export unknown function nid %08x at %08x\n", nid, f_vaddr);
                continue;
            }

            log(ctx->conf, "  export function nid %08x at %08x: %s\n", nid, f_vaddr, pf->name);

            me->functions.emplace_back(function_export{f_vaddr, pf});
        }

        u32 v_offset = exp.exports_vaddr + exp.function_count * sizeof(u32);
        for (u32 _j = 0; _j < exp.variable_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 v_vaddr_vaddr = v_offset + j + sizeof(u32) * (exp.function_count + exp.variable_count);
            u32 v_vaddr;
            u32 nid;

            read_at(ctx->in, &nid, file_offset_from_vaddr(ctx, v_offset) + j);
            read_at(ctx->in, &v_vaddr, file_offset_from_vaddr(ctx, v_vaddr_vaddr));

            const psp_variable *pv = get_syslib_variable(nid);

            if (pv == nullptr)
            {
                // TODO: maybe dont ignore these
                log(ctx->conf, "  export unknown variable nid %08x at %08x\n", nid, v_vaddr);
                continue;
            }

            log(ctx->conf, "  export variable nid %08x at %08x: %s\n", nid, v_vaddr, pv->name);

            me->variables.emplace_back(variable_export{v_vaddr, pv});
        }
    }

    log(ctx->conf, "\n");
}

void add_prx_imports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info, elf_parse_data *out)
{
    u32 sz = mod_info->import_offset_end - mod_info->import_offset_start;
    assert((sz % sizeof(prx_module_import)) == 0);
    assert(out != nullptr);

    u32 count = sz / sizeof(prx_module_import);
    out->imported_modules.reserve(count);

    for (u32 i = 0; i < sz; i += sizeof(prx_module_import))
    {
        prx_module_import imp;
        read_at(ctx->in, &imp, file_offset_from_vaddr(ctx, mod_info->import_offset_start) + i);

        const char *module_name = ctx->in->data + file_offset_from_vaddr(ctx, imp.name_vaddr);

        log(ctx->conf, "import %s: %08x %08x %02x %02x %04x %08x %08x\n",
                       module_name, imp.name_vaddr, imp.flags,
                       imp.entry_size, imp.variable_count, imp.function_count,
                       imp.nids_vaddr, imp.functions_vaddr);

        module_import *mi = &out->imported_modules.emplace_back();
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
            out->imports.emplace(f_vaddr, impf);
            mi->functions.emplace_back(impf);
        }

        // TODO: import variables

        log(ctx->conf, "\n");
    }
}

void add_prx_imports_exports(elf_read_ctx *ctx, elf_parse_data *out)
{
    prx_sce_module_info *mod_info = &out->module_info;
    read_prx_sce_module_info_section_header(ctx, mod_info);

    add_prx_exports(ctx, mod_info, out);
    add_prx_imports(ctx, mod_info, out);
}

void get_elf_min_max_offsets_and_vaddrs(memory_stream *in, const Elf32_Ehdr *elf_header, elf_read_ctx *out)
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
const char *get_string_table(memory_stream *in, const Elf32_Ehdr *elf_header)
{
    Elf32_Shdr string_table_header;
    read_section(in, elf_header, elf_header->e_shstrndx, &string_table_header);

    return in->data + string_table_header.sh_offset;
}

void _read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    Elf32_Ehdr elf_header;

    if (in->size < sizeof(Elf32_Ehdr))
        throw_error("input is not an ELF file");

    read(in, &elf_header);

    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
        throw_error("input is not an ELF file");

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
        throw_error("input is not little-endian MIPS");

    log(conf, "%s\n", "got little-endian mips");

    if (elf_header.e_shstrndx == SHN_UNDEF)
    {
        // while we could look at program headers, PSP games
        // can have strange sections (e.g. MHFU has ~600 sections, a lot of them empty)
        // so we usually rely on the name given by command line args, or disassemble
        // all executable sections instead.
        throw_error("no section header table index found");
    }

    const char *string_table = get_string_table(in, &elf_header);

    Elf32_Shdr section_header;
    std::vector<int> section_indices;

    log(conf, "              %-20s: offset   - size\n", "name");

    for (int i = 0; i < elf_header.e_shnum; ++i)
    {
        read_section(in, &elf_header, i, &section_header);
        const char *section_name = string_table + section_header.sh_name;

        if (conf->section.empty())
        {
            if ((section_header.sh_flags & SHF_EXECINSTR) == 0) // ignore non-executable sections
                continue;
        }
        else if (conf->section != section_name)
            continue;

        log(conf, "found executable section %-20s: %08x - %08x\n", section_name, section_header.sh_offset, section_header.sh_size);
        section_indices.push_back(i);
    }

    if (section_indices.empty())
    {
        if (conf->section.empty())
            throw_error("no executable sections found in input file");
        else
            throw_error("section '%s' not found in input file", conf->section.c_str());
    }

    elf_read_ctx ctx;
    ctx.in = in;
    ctx.conf = conf;
    ctx.elf_header = &elf_header;
    ctx.string_table_data = string_table;
    get_elf_min_max_offsets_and_vaddrs(in, &elf_header, &ctx);
    
    log(conf, "min section vaddr:  %08x, max section vaddr:  %08x\n", ctx.min_vaddr,  ctx.max_vaddr);
    log(conf, "min section offset: %08x, max section offset: %08x\n", ctx.min_offset, ctx.max_offset);

    add_relocations(&ctx, out->relocations);

    for (int i : section_indices)
    {
        read_section(in, &elf_header, i, &section_header);
        const char *section_name = string_table + section_header.sh_name;

        elf_section &esec = out->sections.emplace_back();
        esec.name = std::string(section_name);

        u32 vaddr = conf->vaddr;

        if (conf->vaddr == INFER_VADDR)
            vaddr = section_header.sh_addr;

        esec.vaddr = vaddr;

        out->symbols.emplace(vaddr, elf_symbol{vaddr, section_name});
        add_symbols(&ctx, i, out->symbols);

        esec.content.resize(section_header.sh_size);
        esec.content_offset = section_header.sh_offset;

        if (section_header.sh_size > 0)
            read_at(in, esec.content.data(), section_header.sh_offset, section_header.sh_size);
    }

    add_prx_imports_exports(&ctx, out);
}

void read_elf(file_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    memory_stream memstr;
    open(&memstr, in->size);

    read_at(in, memstr.data, 0, in->size);
    read_elf(&memstr, conf, out);

    close(&memstr);
}

void read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    std::vector<u8> decrypted_elf;

    if (decrypt_elf(in, &decrypted_elf))
    {
        log(conf, "ELF is encrypted and has been decrypted.\n");
        memory_stream delf;
        open(&delf, reinterpret_cast<char*>(decrypted_elf.data()),
                                            decrypted_elf.size());
        _read_elf(&delf, conf, out);
        return;
    }

    seek(in, 0);

    // simply parse from memory if not encrypted
    _read_elf(in, conf, out);
}

size_t decrypt_elf(file_stream *in, std::vector<u8> *out)
{
    memory_stream memstr;
    open(&memstr, in->size);

    read_at(in, memstr.data, 0, in->size);

    size_t ret = decrypt_elf(&memstr, out);

    close(&memstr);

    return ret;
}

size_t decrypt_elf(memory_stream *in, std::vector<u8> *out)
{
    if (in->size < sizeof(Elf32_Ehdr))
        throw_error("input is not an ELF file");

    char magic[4];
    read(in, magic, 4);

    if (strncmp(magic, "\x7f" "ELF", 4))
    {
        // not an ELF, might be incrypted
        
        if (strncmp(magic, "~PSP", 4))
        {
            // nope, not encrypted either
            throw_error("input is not an ELF file and is not encrypted");
        }

        // ok its encrypted, attempt decrypt
        PSP_Header phead;
        read_at(in, &phead, 0);

        size_t nsize = std::max(phead.elf_size, phead.psp_size);
        out->resize(nsize);

        int decrypted_size = pspDecryptPRX(reinterpret_cast<const u8*>(in->data),
                                           out->data(),
                                           phead.psp_size);

        if (decrypted_size < 0)
            throw_error("could not decrypt input file");

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
