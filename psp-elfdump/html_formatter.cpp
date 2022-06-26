
#include <assert.h>

#include "string.hpp"
#include "instruction.hpp"
#include "psp-elfdump/html_formatter.hpp"

void html_format(const dump_config *conf, file_stream *out)
{
    assert(conf != nullptr);
    assert(out != nullptr);

    // TODO: implement
    /*
    for (const dump_section &dsec : conf->dump_sections)
        html_format_section(conf, &dsec, out);
    */
}
