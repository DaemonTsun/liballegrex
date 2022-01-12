
#include <stdio.h>
#include <string.h>
#include "memory_stream.hpp"

memory_stream::memory_stream()
{
}

memory_stream::memory_stream(data_type *ptr, size_type size)
{
    this->m_data = ptr;
    this->m_owns_data = false;
    this->m_size = size;
}

memory_stream::memory_stream(size_type n)
{
    this->m_data = new data_type[n];
    this->m_owns_data = true;
    this->m_size = n;
}

memory_stream::memory_stream(memory_stream &&other)
{
    this->m_data = other.m_data;
    this->m_owns_data = other.m_owns_data;
    this->m_size = other.m_size;

    other.m_data = nullptr;
}

memory_stream::~memory_stream()
{
    this->free();
}

memory_stream &memory_stream::operator=(memory_stream &&other)
{
    this->free();
    this->m_data = other.m_data;
    this->m_owns_data = other.m_owns_data;
    this->m_size = other.m_size;
    other.m_data = nullptr;

    return *this;
}

memory_stream::operator data_type*() const
{
    return this->current();
}

memory_stream::operator bool() const
{
    return this->m_data != nullptr;
}

memory_stream::data_type *memory_stream::data() const
{
    return this->m_data;
}

memory_stream::data_type *memory_stream::begin() const
{
    return this->m_data;
}

memory_stream::data_type *memory_stream::current() const
{
    return this->m_data + this->m_position;
}

memory_stream::data_type *memory_stream::end() const
{
    return this->m_data + this->m_size;
}

memory_stream::size_type memory_stream::size() const
{
    return this->m_size;
}

int memory_stream::seek(long offset, int whence)
{
    if (whence == SEEK_SET)
        this->m_position = offset;
    else if (whence == SEEK_CUR)
        this->m_position = this->m_position + offset;
    else if (whence == SEEK_END)
        this->m_position = this->m_size + offset;
    else
        return 1;

    if (this->m_position >= this->m_size)
        this->m_position = this->m_size - 1;

    return 0;
}

int memory_stream::seek_block(long n, int whence)
{
    if (whence != SEEK_CUR)
        return this->seek(n * this->block_size, whence);

    // SEEK_CUR
    size_type cur = (this->tell() / this->block_size) * this->block_size;
    return this->seek(cur + n * this->block_size, SEEK_SET);
}

int memory_stream::setpos(memory_stream::size_type offset)
{
    return this->seek(offset);
}

memory_stream::size_type memory_stream::tell()
{
    return this->m_position;
}

memory_stream::size_type memory_stream::getpos()
{
    return this->tell();
}

void memory_stream::rewind()
{
    this->m_position = 0;
}

memory_stream::size_type memory_stream::block_count() const
{
    return this->m_size / this->block_size;
}

memory_stream::size_type memory_stream::read(void *out, size_type size)
{
    return this->read(out, size, 1);
}

memory_stream::size_type memory_stream::read(void *out, size_type size, size_type nmemb)
{
    size_type total_size = size * nmemb;
    size_type rest = this->m_size - this->m_position;

    if (total_size > rest)
        total_size = rest;

    if (total_size > 0)
        memcpy(out, this->current(), total_size);

    this->m_position += total_size;

    return total_size;
}

memory_stream::size_type memory_stream::read_at(void *out, size_type offset, size_type size)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, 1);
}

memory_stream::size_type memory_stream::read_at(void *out, size_type offset, size_type size, size_type nmemb)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, nmemb);
}

memory_stream::size_type memory_stream::write(const void *in, size_type size)
{
    return this->write(in, size, 1);
}

memory_stream::size_type memory_stream::write(const void *in, size_type size, size_type nmemb)
{
    size_type total_size = size * nmemb;
    size_type rest = this->m_size - this->m_position;

    if (total_size > rest)
        total_size = rest;

    if (total_size > 0)
        memcpy(this->current(), in, total_size);

    this->m_position += total_size;

    return total_size;
}

memory_stream::size_type memory_stream::read_block(void *out)
{
    return this->read_blocks(out, 1);
}

memory_stream::size_type memory_stream::read_block(void *out, size_type block)
{
    this->seek_block(block);
    return this->read_blocks(out, 1);
}

memory_stream::size_type memory_stream::read_blocks(void *out, size_type n)
{
    return this->read(out, this->block_size, n);
}

memory_stream::size_type memory_stream::read_blocks(void *out, size_type block, size_type n)
{
    this->seek_block(block);
    return this->read(out, this->block_size, n);
}

memory_stream::size_type memory_stream::write_block(const void *in)
{
    return this->write_blocks(in, 1);
}

memory_stream::size_type memory_stream::write_blocks(const void *in, size_type n)
{
    return this->write(in, this->block_size, n);
}

void memory_stream::free()
{
    if (this->m_owns_data && this->m_data != nullptr)
        delete[] this->m_data;

    this->m_data = nullptr;
    this->m_size = 0;
    this->m_owns_data = false;
}
