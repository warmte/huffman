
#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include <string>
#include <vector>
#include <cstring>

struct decompressor {

    static const size_t SIZE = 256;

    decompressor();

    explicit decompressor(std::vector <uint32_t> _count);

    void decompress(std::vector <unsigned char> const &data, std::vector <unsigned char> &new_data);
    void make_tree();

private:
    uint32_t sum;
    std::vector <uint32_t> count;
    std::vector <std::pair <int, int>> children;
    int root;
};

#endif //HUFFMAN_DECOMPRESSOR_H

