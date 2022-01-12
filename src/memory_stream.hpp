
#pragma once

class memory_stream
{
public:
    using size_type = size_t;
    using data_type = char;

    size_type block_size = 1;

    memory_stream();
    memory_stream(data_type *ptr, size_type size);
    memory_stream(size_type n);
    memory_stream(const memory_stream &other) = delete;
    memory_stream(memory_stream &&other);

    ~memory_stream();

    memory_stream &operator=(const memory_stream &other) = delete;
    memory_stream &operator=(memory_stream &&other);

    operator data_type*() const; // always yields current()
    operator bool() const;

    data_type *data() const;
    data_type *begin() const; // same as data()
    data_type *current() const;
    data_type *end() const;
    size_type size() const;

    int seek(long offset, int whence = 0);
    int seek_block(long n, int whence = 0);
    int setpos(size_type offset);
    size_type tell();
    size_type getpos();
    void rewind();
    size_type block_count() const;

    // read & write perform memcpy
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

    size_type read_block(void *out);
    size_type read_block(void *out, size_type block);
    size_type read_blocks(void *out, size_type n);
    size_type read_blocks(void *out, size_type block, size_type n);
    size_type write_block(const void *in);
    size_type write_blocks(const void *in, size_type n);

    // get does not perform memcpy
    template<typename T>
    void get(T **out)
    {
        *out = reinterpret_cast<T*>(this->current());
    }

    template<typename T>
    void get_aligned(T **out)
    {
        size_type pos = (this->tell() / sizeof(T)) * sizeof(T)
        *out = reinterpret_cast<T*>(this->data() + pos);
    }

    template<typename T>
    void get_at(T **out, size_type offset)
    {
        *out = reinterpret_cast<T*>(this->data() + offset);
    }

private:
    data_type *m_data = nullptr;
    bool m_owns_data = false;
    size_type m_size = 0;
    size_type m_position = 0;

    void free();
};
