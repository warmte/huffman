#include "utility.h"
#include "block_rw.h"
#include "../lib/compressor.h"
#include "../lib/decompressor.h"
#include <iostream>

void compress_file(char const *in_name, char const *out_name) {
    block_rw input(in_name, "rb");
    block_rw output(out_name, "wb");

    compressor compr;
    std::vector <unsigned char> buf, coded;

    while (!input.eof()) {
        input.read_block(buf, input.SIZE);
        compr.count_freq(buf);
    }

    output.write_freq(compr.get_count());
    compr.make_tree();
    input.rewind();

    while (!input.eof()) {
        input.read_block(buf, input.SIZE);
        coded.clear();
        compr.compress(buf, coded);
        //std::cerr << buf.size() << "!\n";
        output.write_sum((uint32_t)buf.size());
        output.write_sum((uint32_t)coded.size());
        output.write_block(coded, "");
    }
}

void decompress_file(char const *in_name, char const *out_name) {
    block_rw input(in_name, "rb");
    block_rw output(out_name, "wb");

    std::vector <uint32_t> count;
    input.read_freq(count);
    std::vector <unsigned char> buf, decoded;
    decompressor decompr(count);
    decompr.make_tree();

    uint32_t sum, size;

    while (!input.eof()) {
        input.read_sum(sum);
        input.read_sum(size);
        input.read_block(buf, size);
        decoded.clear();
        if (!buf.empty())
            decompr.decompress(buf, decoded, sum);
        output.write_block(decoded, "");
    }
}