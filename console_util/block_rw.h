#ifndef HUFFMAN_BLOCK_RW_H
#define HUFFMAN_BLOCK_RW_H

#include <cstdio>
#include <vector>
#include <stdexcept>
#include <string>

struct block_rw {
    static const size_t SIZE = (1 << 15), ALPHABET = 256;

    block_rw(const char *name, const char *rw);
    ~block_rw();

    void read_block(std::vector <unsigned char> &buf);
    void write_block(std::vector <unsigned char> const &buf, const char *sep);

    void read_freq(std::vector <uint32_t> &count);
    void write_freq(std::vector <uint32_t> const &count);

    bool eof();

    void rewind();
private:
    FILE *file;
};

#endif //HUFFMAN_BLOCK_RW_H
