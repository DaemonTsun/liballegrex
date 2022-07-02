
#include <assert.h>

#include "string.hpp"
#include "instruction.hpp"
#include "psp-elfdump/html_formatter.hpp"

void html_format_header(const dump_config *conf, file_stream *out)
{
    const prx_sce_module_info *module_info = conf->module_info;
    const char *module_name = module_info ? module_info->name : "[unknown]";

    out->format(R"=(
<head>
  <title>
    %s
  </title>
)=", module_name);

    out->format(
#include "disasm.css"
    );

    out->format("</head>\n");
}

void html_format_module_info(const dump_config *conf, const prx_sce_module_info *module_info, file_stream *out)
{
    if (module_info == nullptr)
    {
        out->format("  <div class=\"block module_info\">[unknown]</div>");
        return;
    }

    // TODO: anchor, attributes, version, imports, exports
    out->format(R"=(
  <div class="block module_info">
    <span>%s</span><hr/>
  </div><br/>
)=", module_info->name);
}

void html_format_section(const dump_config *conf, const dump_section *dsec, file_stream *out)
{
    out->format("  <div class=\"block section\">\n");

    // TODO: anchor, offset, size, content
    out->format("    <span>%s</span><hr/>\n", dsec->section->name.c_str());

    out->format("  </div><br/>\n");
}

void html_format_body(const dump_config *conf, file_stream *out)
{
    out->format("<body>");

    html_format_module_info(conf, conf->module_info, out);

    for (const dump_section &dsec : conf->dump_sections)
        html_format_section(conf, &dsec, out);

    out->format("</body>\n");
}

void html_format(const dump_config *conf, file_stream *out)
{
    assert(conf != nullptr);
    assert(out != nullptr);

    out->format("<html>");
    html_format_header(conf, out);

    html_format_body(conf, out);

    out->format("</html>");
}
