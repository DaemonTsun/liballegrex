
#include "file_stream.hpp"

file_stream::file_stream()
{
}

file_stream::file_stream(FILE *file_stream, bool owns)
{
    this->handle = file_stream;
    this->owns_handle = owns;
}

file_stream::file_stream(const char *path, const char *mode)
{
    this->open(path, mode);
}

file_stream::file_stream(const std::string &path, const char *mode)
  : file_stream(path.c_str(), mode)
{
}

file_stream::file_stream(file_stream &&other)
{
    this->handle = other.handle;
    this->owns_handle = other.owns_handle;
    this->m_size = other.m_size;

    other.handle = nullptr;
}

file_stream::~file_stream()
{
    this->close();
}

file_stream &file_stream::operator=(file_stream &&other)
{
    this->close();
    this->handle = other.handle;
    this->owns_handle = other.owns_handle;
    this->m_size = other.m_size;

    other.handle = nullptr;

    return *this;
}

file_stream::operator bool() const
{
    return this->is_open();
}

bool file_stream::is_open() const
{
    return this->handle != nullptr;
}

file_stream::size_type file_stream::size() const
{
    return this->m_size;
}

bool file_stream::open(const char *path, const char *mode)
{
    int e = this->close();

    if (e != 0)
        return false;

    this->handle = fopen(path, mode);

    if (!this->is_open())
        return false;

    return true;
}

bool file_stream::open(const std::string &path, const char *mode)
{
    return this->open(path.c_str(), mode);
}

int file_stream::close()
{
    int ret = 0;

    if (this->owns_handle && this->handle != nullptr)
        ret = fclose(this->handle);

    this->handle = nullptr;
    this->m_size = 0;

    return ret;
}

int file_stream::seek(long offset, int whence)
{
    return fseeko(this->handle, offset, whence);
}

int file_stream::seek_block(long n, int whence)
{
    if (whence != SEEK_CUR)
        return this->seek(n * this->block_size, whence);

    // SEEK_CUR
    size_type cur = (this->tell() / this->block_size) * this->block_size;
    return this->seek(cur + n * this->block_size, SEEK_SET);
}

int file_stream::setpos(file_stream::size_type offset)
{
    return this->seek(offset);
}

file_stream::size_type file_stream::tell()
{
    return ftello(this->handle);
}

file_stream::size_type file_stream::getpos()
{
    return this->tell();
}

int file_stream::rewind()
{
    return this->seek(0L, SEEK_SET);
}

file_stream::size_type file_stream::calculate_size()
{
    if (!this->is_open())
        return 0;

    size_type curpos = this->tell();
    this->seek(0, SEEK_END);
    this->m_size = this->tell();
    this->seek(curpos);

    return this->m_size;
}

file_stream::size_type file_stream::block_count() const
{
    return this->m_size / this->block_size;
}

file_stream::size_type file_stream::read(void *out, size_type size)
{
    return this->read(out, size, 1);
}

file_stream::size_type file_stream::read(void *out, size_type size, size_type nmemb)
{
    return fread(out, size, nmemb, this->handle);
}

file_stream::size_type file_stream::read_at(void *out, size_type offset, size_type size)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, 1);
}

file_stream::size_type file_stream::read_at(void *out, size_type offset, size_type size, size_type nmemb)
{
    this->seek(offset, SEEK_SET);
    return this->read(out, size, nmemb);
}

file_stream::size_type file_stream::write(const void *in, size_type size)
{
    return fwrite(in, size, 1, this->handle);
}

file_stream::size_type file_stream::write(const void *in, size_type size, size_type nmemb)
{
    return fwrite(in, size, nmemb, this->handle);
}

file_stream::size_type file_stream::write(const char *str)
{
    return fputs(str, this->handle);
}

file_stream::size_type file_stream::write(const std::string &str)
{
    return fputs(str.c_str(), this->handle);
}

file_stream::size_type file_stream::read_block(void *out)
{
    return this->read_blocks(out, 1);
}

file_stream::size_type file_stream::read_block(void *out, size_type block)
{
    this->seek_block(block);
    return this->read_blocks(out, 1);
}

file_stream::size_type file_stream::read_blocks(void *out, size_type n)
{
    return this->read(out, this->block_size, n);
}

file_stream::size_type file_stream::read_blocks(void *out, size_type block, size_type n)
{
    this->seek_block(block);
    return this->read(out, this->block_size, n);
}

file_stream::size_type file_stream::write_block(const void *in)
{
    return this->write_blocks(in, 1);
}

file_stream::size_type file_stream::write_blocks(const void *in, size_type n)
{
    return this->write(in, this->block_size, n);
}

int file_stream::flush()
{
    return fflush(this->handle);
}
