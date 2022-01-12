
#include <assert.h>
#include "parse_allegrex.hpp"

#define log(CONF, ...) {if (CONF->verbose) {CONF->log->format(__VA_ARGS__);}};

void parse_allegrex(memory_stream *in, const parse_config *conf, std::vector<instruction> &out)
{
    size_t sz = in->size();

    assert(sz % sizeof(u32) == 0);
    assert(sz <= UINT32_MAX);

    u32 count = (u32)(sz / sizeof(u32));
    out.resize(count);

    for (u32 i = 0x00000000; i < sz; i += sizeof(u32))
    {
        instruction inst;
        in->read(&inst.opcode); // probably don't need read_at
        inst.address = conf->vaddr + i;

        if ((inst.opcode & 0xfc00003f) == 0x00000020)
            log(conf, "%08x %08x: %s\n", inst.address, inst.opcode, "add");
    }
}
