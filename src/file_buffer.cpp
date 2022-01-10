
#include "file_buffer.hpp"

file_buffer::file_buffer()
{
}

file_buffer::file_buffer(FILE *file_buffer, bool owns)
{
    this->handle = file_buffer;
    this->owns_handle = owns;
}

file_buffer::file_buffer(const char *path, const char *mode)
{
    this->open(path, mode);
}

file_buffer::file_buffer(const std::string &path, const char *mode)
  : file_buffer(path.c_str(), mode)
{
}

file_buffer::file_buffer(file_buffer &&other)
{
    this->handle = other.handle;
    this->owns_handle = other.owns_handle;
    this->m_size = other.m_size;
}

file_buffer::~file_buffer()
{
    this->close();
}

file_buffer &file_buffer::operator=(file_buffer &&other)
{
    this->close();
    this->handle = other.handle;
    this->owns_handle = other.owns_handle;
    this->m_size = other.m_size;

    return *this;
}

file_buffer::operator bool() const
{
    return this->is_open();
}

bool file_buffer::is_open() const
{
    return this->handle != nullptr;
}

file_buffer::size_type file_buffer::size() const
{
    return this->m_size;
}

bool file_buffer::open(const char *path, const char *mode)
{
    int e = this->close();

    if (e != 0)
        return false;

    this->handle = fopen(path, mode);

    if (!this->is_open())
        return false;

    return true;
}

bool file_buffer::open(const std::string &path, const char *mode)
{
    return this->open(path.c_str(), mode);
}

int file_buffer::close()
{
    int ret = 0;

    if (this->owns_handle && this->handle != nullptr)
        ret = fclose(this->handle);

    this->handle = nullptr;
    this->m_size = 0;

    return ret;
}

int file_buffer::seek(long offset, int whence)
{
    return fseeko(this->handle, offset, whence);
}

int file_buffer::seek_block(long n, int whence)
{
    if (whence != SEEK_CUR)
        return this->seek(n * this->block_size, whence);

    // SEEK_CUR
    size_type cur = (this->tell() / this->block_size) * this->block_size;
    return this->seek(cur + n * this->block_size, SEEK_SET);
}

int file_buffer::setpos(file_buffer::size_type offset)
{
    return this->seek(offset);
}

file_buffer::size_type file_buffer::tell()
{
    return ftello(this->handle);
}

file_buffer::size_type file_buffer::getpos()
{
    return this->tell();
}

int file_buffer::rewind()
{
    return this->seek(0L, SEEK_SET);
}

file_buffer::size_type file_buffer::calculate_size()
{
    if (!this->is_open())
        return 0;

    size_type curpos = this->tell();
    this->seek(0, SEEK_END);
    this->m_size = this->tell();
    this->seek(curpos);

    return this->m_size;
}

file_buffer::size_type file_buffer::block_count() const
{
    return this->m_size / this->block_size;
}

file_buffer::size_type file_buffer::read(void *out, size_type size)
{
    return this->read(out, size, 1);
}

file_buffer::size_type file_buffer::read(void *out, size_type size, size_type nmemb)
{
    return fread(out, size, nmemb, this->handle);
}

file_buffer::size_type file_buffer::read_at(void *out, size_type offset, size_type size)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, 1);
}

file_buffer::size_type file_buffer::read_at(void *out, size_type offset, size_type size, size_type nmemb)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, nmemb);
}

file_buffer::size_type file_buffer::write(const void *in, size_type size)
{
    return fwrite(in, size, 1, this->handle);
}

file_buffer::size_type file_buffer::write(const void *in, size_type size, size_type nmemb)
{
    return fwrite(in, size, nmemb, this->handle);
}

file_buffer::size_type file_buffer::write(const char *str)
{
    return fputs(str, this->handle);
}

file_buffer::size_type file_buffer::write(const std::string &str)
{
    return fputs(str.c_str(), this->handle);
}

file_buffer::size_type file_buffer::read_block(void *out)
{
    return this->read_blocks(out, 1);
}

file_buffer::size_type file_buffer::read_block(void *out, size_type block)
{
    this->seek_block(block);
    return this->read_blocks(out, 1);
}

file_buffer::size_type file_buffer::read_blocks(void *out, size_type n)
{
    return this->read(out, this->block_size, n);
}

file_buffer::size_type file_buffer::read_blocks(void *out, size_type block, size_type n)
{
    this->seek_block(block);
    return this->read(out, this->block_size, n);
}

file_buffer::size_type file_buffer::write_block(const void *in)
{
    return this->write_blocks(in, 1);
}

file_buffer::size_type file_buffer::write_blocks(const void *in, size_type n)
{
    return this->write(in, this->block_size, n);
}

int file_buffer::flush()
{
    return fflush(this->handle);
}
