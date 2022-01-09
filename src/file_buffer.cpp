
#include "file_buffer.hpp"

file_buffer::file_buffer(FILE *file_buffer, bool calc_size)
{
    this->m_file = file_buffer;

    if (calc_size)
        this->calculate_size();
}

file_buffer::file_buffer(const char *path, const char *mode, bool calc_size)
{
    this->open(path, mode, calc_size);
}

file_buffer::file_buffer(const std::string &path, const char *mode, bool calc_size)
  : file_buffer(path.c_str(), mode, calc_size)
{
}

file_buffer::file_buffer(file_buffer &&other)
{
    this->m_file = other.m_file;
    this->m_size = other.m_size;
}

file_buffer::~file_buffer()
{
    this->close();
}

file_buffer &file_buffer::operator=(file_buffer &&other)
{
    this->close();
    this->m_file = other.m_file;
    this->m_size = other.m_size;

    return *this;
}

file_buffer::operator bool() const
{
    return this->is_open();
}

bool file_buffer::is_open() const
{
    return this->m_file != nullptr;
}

file_buffer::size_type file_buffer::size() const
{
    return this->m_size;
}

FILE *file_buffer::stream() const
{
    return this->m_file;
}

bool file_buffer::open(const char *path, const char *mode, bool calc_size)
{
    int e = this->close();

    if (e != 0)
        return e;

    this->m_file = fopen(path, mode);

    if (!this->is_open())
        return false;

    if (calc_size)
        this->calculate_size();

    return true;
}

bool file_buffer::open(const std::string &path, const char *mode, bool calc_size)
{
    return this->open(path.c_str(), mode, calc_size);
}

int file_buffer::close()
{
    int ret = 0;

    if (this->m_file != nullptr)
        if (!((this->m_file == stdout) || (this->m_file == stdin) || (this->m_file == stderr)))
            ret = fclose(this->m_file);

    this->m_file = nullptr;
    this->m_size = 0;

    return ret;
}

int file_buffer::seek(long offset, int whence)
{
    return fseeko(this->m_file, offset, whence);
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
    return ftello(this->m_file);
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
    return fread(out, size, nmemb, this->m_file);
}

file_buffer::size_type file_buffer::write(const void *in, size_type size)
{
    return fwrite(in, size, 1, this->m_file);
}

file_buffer::size_type file_buffer::write(const void *in, size_type size, size_type nmemb)
{
    return fwrite(in, size, nmemb, this->m_file);
}

file_buffer::size_type file_buffer::write(const char *str)
{
    return fputs(str, this->m_file);
}

file_buffer::size_type file_buffer::write(const std::string &str)
{
    return fputs(str.c_str(), this->m_file);
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
    return fflush(this->m_file);
}
