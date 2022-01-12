
#pragma once

#include <stdio.h>
#include <string>

#define MODE_READ "r"
#define MODE_WRITE "w"
#define MODE_BINARY "b"

class file_stream
{
public:
    using size_type = size_t;
    size_type block_size = 1;
    FILE *handle = nullptr;
    bool owns_handle = false;

    file_stream();
    file_stream(FILE *file_stream, bool owns = false);
    file_stream(const char *path, const char *mode = MODE_READ);
    file_stream(const std::string &path, const char *mode = MODE_READ);
    file_stream(const file_stream &other) = delete;
    file_stream(file_stream &&other);

    ~file_stream();

    file_stream &operator=(const file_stream &other) = delete;
    file_stream &operator=(file_stream &&other);

    // operator FILE*() const;
    operator bool() const;

    bool is_open() const;
    size_type size() const;

    bool open(const char *path, const char *mode = MODE_READ);
    bool open(const std::string &path, const char *mode = MODE_READ);
    int close();

    int seek(long offset, int whence = SEEK_SET);
    int seek_block(long n, int whence = SEEK_SET);
    int setpos(size_type offset);
    size_type tell();
    size_type getpos();
    int rewind();
    size_type calculate_size();
    size_type block_count() const;

    size_type read(void *out, size_type size);
    size_type read(void *out, size_type size, size_type nmemb);

    template<typename T>
    size_type read(T *out)
    {
        return this->read(out, sizeof(T));
    }

    size_type read_at(void *out, size_type offset, size_type size);
    size_type read_at(void *out, size_type offset, size_type size, size_type nmemb);

    template<typename T>
    size_type read_at(T *out, size_type offset)
    {
        return this->read_at(out, offset, sizeof(T));
    }

    size_type write(const void *in, size_type size);
    size_type write(const void *in, size_type size, size_type nmemb);
    size_type write(const char *size);
    size_type write(const std::string &str);

    template<typename... Ts>
    size_type format(const char *format_string, Ts&&... args)
    {
        return fprintf(this->handle, format_string, std::forward<Ts>(args)...);
    }

    size_type read_block(void *out);
    size_type read_block(void *out, size_type block);
    size_type read_blocks(void *out, size_type n);
    size_type read_blocks(void *out, size_type block, size_type n);
    size_type write_block(const void *in);
    size_type write_blocks(const void *in, size_type n);
    int flush();

private:
    size_type m_size = 0;
};
