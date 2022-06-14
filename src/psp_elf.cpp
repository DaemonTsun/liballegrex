
#include <stdexcept>
#include <vector>

#include <elf.h>
#include <assert.h>
#include <string.h>

#include "string.hpp"
#include "psp_prx.hpp"
#include "prx_decrypt.hpp"
#include "psp_elf.hpp"

/*
#define R_MIPS_26    4
#define R_MIPS_HI16  5
#define R_MIPS_LO16  6
*/
#define ELF_SECTION_PRX_MODULE_INFO ".rodata.sceModuleInfo"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};
// #define read_section(in, ehdr, index, out) in->read_at(out, ehdr.e_shoff + (index) * ehdr.e_shentsize);

// TODO: simplify this to only use memory stream
// i mean really do we ever need file streams
template<typename T>
void read_section(memory_stream *in, const Elf32_Ehdr *ehdr, int index, T *out)
{
    in->read_at(out, ehdr->e_shoff + (index) * ehdr->e_shentsize);
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
    // there's a good chance symbols don't exist
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
        ctx->in->read_at(sec_string_table.data(), strtab_header.sh_offset, strtab_header.sh_size);

        for (u32 i = 0; i < sec_header.sh_size; i += sizeof(Elf32_Sym))
        {
            Elf32_Sym sym;
            ctx->in->read_at(&sym, sec_header.sh_offset + i);

            const char *name = sec_string_table.data() + sym.st_name;

            if (strlen(name) == 0)
                continue;

            if (sym.st_shndx != section_index) //|| name[0] == '.')
                continue;

            log(ctx->conf, "  symbol at %08x: '%s'\n", sym.st_value, name);
            symbols[sym.st_value] = elf_symbol{sym.st_value, std::string(name)};
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
            ctx->in->read_at(&rel, sec_header.sh_offset + j);
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

    ctx->in->read_at(out, sceModuleInfo_section_header.sh_offset);

    log(ctx->conf, "  flags:  %08x\n", out->flags);
    log(ctx->conf, "  name:   %s\n", out->name);
    log(ctx->conf, "  gp:     %08x\n", out->gp);
    log(ctx->conf, "  export: %08x - %08x\n", out->export_offset_start, out->export_offset_end);
    log(ctx->conf, "  import: %08x - %08x\n", out->import_offset_start, out->import_offset_end);
}

void add_prx_exports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info /* TODO: output */)
{
    u32 sz = mod_info->export_offset_end - mod_info->export_offset_start;
    assert((sz % sizeof(prx_module_export)) == 0);

    for (u32 i = 0; i < sz; i += sizeof(prx_module_export))
    {
        prx_module_export exp;
        ctx->in->read_at(&exp, file_offset_from_vaddr(ctx, mod_info->export_offset_start) + i);

        log(ctx->conf, "export %08x %08x %08x %08x %08x %08x\n", exp.name_vaddr, exp.flags, exp.entry_size, exp.variable_count, exp.function_count, exp.exports_vaddr);
    }

    log(ctx->conf, "\n");
    // TODO: exports
}

void add_prx_imports(elf_read_ctx *ctx, const prx_sce_module_info *mod_info, import_map *out)
{
    u32 sz = mod_info->import_offset_end - mod_info->import_offset_start;
    assert((sz % sizeof(prx_module_import)) == 0);
    assert(out != nullptr);

    for (u32 i = 0; i < sz; i += sizeof(prx_module_import))
    {
        prx_module_import imp;
        ctx->in->read_at(&imp, file_offset_from_vaddr(ctx, mod_info->import_offset_start) + i);

        const char *name = ctx->in->data() + file_offset_from_vaddr(ctx, imp.name_vaddr);

        log(ctx->conf, "import %s: %08x %08x %02x %02x %04x %08x %08x\n", name, imp.name_vaddr, imp.flags, imp.entry_size, imp.variable_count, imp.function_count, imp.nids_vaddr, imp.functions_vaddr);

        for (u32 _j = 0; _j < imp.function_count; ++_j)
        {
            u32 j = _j * sizeof(u32);
            u32 f_vaddr = imp.functions_vaddr + j * 2;
            u32 nid;

            ctx->in->read_at(&nid, file_offset_from_vaddr(ctx, imp.nids_vaddr) + j);

            const psp_function *pf = get_psp_function_by_nid(name, nid);

            if (pf == nullptr)
            {
                log(ctx->conf, "  could not find function %08x in module %s\n", nid, name);
            }
            else
            {
                log(ctx->conf, "  import %08x at vaddr %08x: %s\n", nid, f_vaddr, pf->name);
                out->emplace(f_vaddr, prx_function_import{f_vaddr, pf});
            }
        }

        log(ctx->conf, "\n");
    }
}

void add_prx_imports_exports(elf_read_ctx *ctx, /* TODO: exports */ import_map *imports)
{
    prx_sce_module_info mod_info;
    read_prx_sce_module_info_section_header(ctx, &mod_info);

    add_prx_exports(ctx, &mod_info);
    add_prx_imports(ctx, &mod_info, imports);
}

void _read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    Elf32_Ehdr elf_header;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    in->read(&elf_header);

    if (strncmp((const char*)elf_header.e_ident, "\x7f" "ELF", 4))
        throw std::runtime_error("input is not an ELF file");

    // we want little endian
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB
     || elf_header.e_machine != EM_MIPS)
        throw std::runtime_error("input is not little-endian MIPS");

    log(conf, "%s\n", "got little-endian mips");

    if (elf_header.e_shstrndx == SHN_UNDEF)
    {
        // while we could look at program headers, PSP games
        // can have strange sections (e.g. MHFU has ~600 sections, a lot of them empty)
        // so we usually rely on the name given by command line args, or disassemble
        // all executable sections instead.
        throw std::runtime_error("no section header table index found");
    }

    Elf32_Shdr string_table_header;
    read_section(in, &elf_header, elf_header.e_shstrndx, &string_table_header);

    std::vector<char> string_table;
    string_table.resize(string_table_header.sh_size);
    in->read_at(string_table.data(), string_table_header.sh_offset, string_table_header.sh_size);
    
    Elf32_Shdr section_header;

    log(conf, "              %-20s: offset   - size\n", "name");

    std::vector<int> section_indices;

    for (int i = 0; i < elf_header.e_shnum; ++i)
    {
        read_section(in, &elf_header, i, &section_header);
        const char *section_name = string_table.data() + section_header.sh_name;

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
            throw std::runtime_error(str("no executable sections found in input file"));
        else
            throw std::runtime_error(str("section '", conf->section, "' not found in input file"));
    }

    elf_read_ctx ctx;
    ctx.in = in;
    ctx.conf = conf;
    ctx.elf_header = &elf_header;
    ctx.string_table_data = string_table.data();
    ctx.min_vaddr = 0xFFFFFFFF;
    ctx.max_vaddr = 0;
    ctx.min_offset = 0xFFFFFFFF;
    ctx.max_offset = 0;

    // find elf section offsets (need the values for address calculations)
    for (int i = 0; i < elf_header.e_shnum; ++i)
    {
        read_section(in, &elf_header, i, &section_header);

        if ((section_header.sh_type & SHT_NOBITS) == SHT_NOBITS)
            continue;

        if (section_header.sh_addr == 0 || section_header.sh_offset == 0)
            continue;

        if (section_header.sh_addr < ctx.min_vaddr)
            ctx.min_vaddr = section_header.sh_addr;

        if (section_header.sh_addr + section_header.sh_size > ctx.max_offset)
            ctx.max_vaddr = section_header.sh_addr + section_header.sh_size;

        if (section_header.sh_offset < ctx.min_offset)
            ctx.min_offset = section_header.sh_offset;

        if (section_header.sh_offset + section_header.sh_size > ctx.max_offset)
            ctx.max_offset = section_header.sh_offset + section_header.sh_size;
    }
    
    log(conf, "min section vaddr:  %08x, max section vaddr:  %08x\n", ctx.min_vaddr,  ctx.max_vaddr);
    log(conf, "min section offset: %08x, max section offset: %08x\n", ctx.min_offset, ctx.max_offset);

    add_relocations(&ctx, out->relocations);

    for (int i : section_indices)
    {
        read_section(in, &elf_header, i, &section_header);
        const char *section_name = string_table.data() + section_header.sh_name;

        elf_section &esec = out->sections.emplace_back();
        esec.name = std::string(section_name);

        u32 vaddr = conf->vaddr;

        if (conf->vaddr == INFER_VADDR)
            vaddr = section_header.sh_addr;

        esec.vaddr = vaddr;

        add_symbols(&ctx, i, out->symbols);

        esec.content = memory_stream(section_header.sh_size);
        esec.content_offset = section_header.sh_offset;
        in->read_at(esec.content.data(), section_header.sh_offset, section_header.sh_size);
    }

    add_prx_imports_exports(&ctx, &out->imports);
}

void read_elf(file_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    memory_stream memstr = memory_stream(in->size());
    in->read_at(memstr.data(), 0, in->size());

    read_elf(&memstr, conf, out);
}

void read_elf(memory_stream *in, const psp_elf_read_config *conf, elf_parse_data *out)
{
    std::vector<u8> decrypted_elf;

    if (decrypt_elf(in, &decrypted_elf))
    {
        log(conf, "ELF is encrypted and has been decrypted.\n");
        memory_stream delf = memory_stream(reinterpret_cast<char*>(decrypted_elf.data()),
                                           decrypted_elf.size());
        _read_elf(&delf, conf, out);
        return;
    }

    in->seek(0);

    // simply parse from memory if not encrypted
    _read_elf(in, conf, out);
}

size_t decrypt_elf(file_stream *in, std::vector<u8> *out)
{
    memory_stream memstr = memory_stream(in->size());
    in->read_at(memstr.data(), 0, in->size());

    return decrypt_elf(&memstr, out);
}

size_t decrypt_elf(memory_stream *in, std::vector<u8> *out)
{
    Elf32_Ehdr elf_header;

    if (in->size() < sizeof(Elf32_Ehdr))
        throw std::runtime_error("input is not an ELF file");

    char magic[4];
    in->read(magic, 4);

    if (strncmp(magic, "\x7f" "ELF", 4))
    {
        // not an ELF
        
        if (strncmp(magic, "~PSP", 4))
            // not encrypted either
            throw std::runtime_error("input is not an ELF file and is not encrypted");

        // ok its encrypted, attempt decrypt
        PSP_Header phead;
        in->read_at(&phead, 0);

        size_t nsize = std::max(phead.elf_size, phead.psp_size);
        out->resize(nsize);

        int decrypted_size = pspDecryptPRX(reinterpret_cast<const u8*>(in->data()),
                                           out->data(),
                                           phead.psp_size);

        if (decrypted_size < 0)
            throw std::runtime_error("could not decrypt input file");

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
