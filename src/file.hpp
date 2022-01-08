
#pragma once

#include <stdio.h>
#include <string>

#define MODE_READ "r"
#define MODE_WRITE "w"
#define MODE_BINARY "b"

class file
{
public:
    using size_type = size_t;
    size_type block_size = 1;

    file(FILE *file);
    file(const char *path, const char *mode = MODE_READ);
    file(const std::string &path, const char *mode = MODE_READ);
    file(const file &other) = delete;
    file(file &&other);

    ~file();

    file &operator=(const file &other) = delete;
    file &operator=(file &&other);

    // operator FILE*() const;
    operator bool() const;

    bool is_open() const;
    size_type size() const;
    FILE *stream() const;

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
    size_type write(const void *in, size_type size);
    size_type write(const void *in, size_type size, size_type nmemb);
    size_type write(const char *size);
    size_type write(const std::string &str);

    template<typename... Ts>
    size_type format(const char *format_string, Ts&&... args)
    {
        return fprintf(m_file, std::forward<Ts>(args)...);
    }

    size_type read_block(void *out);
    size_type read_block(void *out, size_type block);
    size_type read_blocks(void *out, size_type n);
    size_type read_blocks(void *out, size_type block, size_type n);
    size_type write_block(const void *in);
    size_type write_blocks(const void *in, size_type n);
    int flush();

private:
    FILE *m_file = nullptr;
    size_type m_size = 0;
};
