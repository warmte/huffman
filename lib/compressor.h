#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <string>
#include <vector>

struct compressor {

    static const size_t SIZE = 256;

    compressor();

    void compress(std::vector <unsigned char> const &data, std::vector <unsigned char> &new_data);
    void make_tree();
    void count_freq(std::vector <unsigned char> const &data);
    void codes_generate(int cur, std::vector <bool> &code);
    std::vector <uint32_t> get_count();

    ~compressor() = default;
private:
    std::vector<std::vector <bool>> codes;
    std::vector<std::pair<int, int>> children;
    std::vector<uint32_t> count;

    int root;
};

#endif //HUFFMAN_COMPRESSOR_H
