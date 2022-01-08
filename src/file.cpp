
#include "file.hpp"

file::file(FILE *file)
{
    this->m_file = file;
    this->calculate_size();
}

file::file(const char *path, const char *mode)
{
    this->open(path);
}

file::file(const std::string &path, const char *mode)
  : file(path.c_str(), mode)
{
}

file::file(file &&other)
{
    this->m_file = other.m_file;
    this->m_size = other.m_size;
}

file::~file()
{
    this->close();
}

file &file::operator=(file &&other)
{
    this->m_file = other.m_file;
    this->m_size = other.m_size;

    return *this;
}

file::operator bool() const
{
    return this->is_open();
}

bool file::is_open() const
{
    return this->m_file != nullptr;
}

file::size_type file::size() const
{
    return this->m_size;
}

FILE *file::stream() const
{
    return this->m_file;
}

bool file::open(const char *path, const char *mode)
{
    int e = this->close();

    if (e != 0)
        return e;

    this->m_file = fopen(path, mode);
    this->calculate_size();
    return this->is_open();
}

bool file::open(const std::string &path, const char *mode)
{
    return this->open(path.c_str(), mode);
}

int file::close()
{
    int ret = 0;

    if (this->m_file != nullptr)
        ret = fclose(this->m_file);

    this->m_file = nullptr;
    this->m_size = 0;

    return ret;
}

int file::seek(long offset, int whence)
{
    return fseeko(this->m_file, offset, whence);
}

int file::seek_block(long n, int whence)
{
    if (whence != SEEK_CUR)
        return this->seek(n * this->block_size, whence);

    // SEEK_CUR
    size_type cur = (this->tell() / this->block_size) * this->block_size;
    return this->seek(cur + n * this->block_size, SEEK_SET);
}

int file::setpos(file::size_type offset)
{
    return this->seek(offset);
}

file::size_type file::tell()
{
    return ftello(this->m_file);
}

file::size_type file::getpos()
{
    return this->tell();
}

int file::rewind()
{
    return this->seek(0L, SEEK_SET);
}

file::size_type file::calculate_size()
{
    size_type curpos = this->tell();
    this->seek(0, SEEK_END);
    this->m_size = this->tell();
    this->seek(curpos);

    return this->m_size;
}

file::size_type file::block_count() const
{
    return this->m_size / this->block_size;
}

file::size_type file::read(void *out, size_type size)
{
    return this->read(out, size, 1);
}

file::size_type file::read(void *out, size_type size, size_type nmemb)
{
    return fread(out, size, nmemb, this->m_file);
}

file::size_type file::write(const void *in, size_type size)
{
    return fwrite(in, size, 1, this->m_file);
}

file::size_type file::write(const void *in, size_type size, size_type nmemb)
{
    return fwrite(in, size, nmemb, this->m_file);
}

file::size_type file::write(const char *str)
{
    return fputs(str, this->m_file);
}

file::size_type file::write(const std::string &str)
{
    return fputs(str.c_str(), this->m_file);
}

file::size_type file::read_block(void *out)
{
    return this->read_blocks(out, 1);
}

file::size_type file::read_block(void *out, size_type block)
{
    this->seek_block(block);
    return this->read_blocks(out, 1);
}

file::size_type file::read_blocks(void *out, size_type n)
{
    return this->read(out, this->block_size, n);
}

file::size_type file::read_blocks(void *out, size_type block, size_type n)
{
    this->seek_block(block);
    return this->read(out, this->block_size, n);
}

file::size_type file::write_block(const void *in)
{
    return this->write_blocks(in, 1);
}

file::size_type file::write_blocks(const void *in, size_type n)
{
    return this->write(in, this->block_size, n);
}

int file::flush()
{
    return fflush(this->m_file);
}
