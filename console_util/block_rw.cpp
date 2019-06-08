#include "block_rw.h"
#include <cstdio>
#include <iostream>

block_rw::block_rw(const char *name, const char *_rw) {
    file = std::fopen(name, _rw);
    if (file == nullptr) {
        std::cerr << "ERROR: cannot open the file.\n";
        exit(0);
    }
}

void block_rw::read_block(std::vector<unsigned char> &buf, size_t size) {
    buf = std::vector <unsigned char> (size);
    size_t cnt = fread(buf.data(), 1, size, file);
    if (cnt != size) {
        buf.erase(buf.begin() + cnt, buf.end());
        if (ferror(file)) {
            std::cerr << "ERROR: cannot read data from the file.\n";
            exit(0);
        }
    }
}

bool block_rw::eof() {
    return (bool)feof(file);
}

void block_rw::write_block(std::vector<unsigned char> const &buf, const char *sep) {
    for (unsigned char c : buf) {
        std::fprintf(file, "%c%s", c, sep);
    }
    if (ferror(file)) {
        std::cerr << "ERROR: cannot write data to the file.\n";
        exit(0);
    }
}

block_rw::~block_rw() {
    std::fclose(file);
}

void block_rw::rewind() {
    std::rewind(file);
}

void block_rw::write_freq(std::vector<uint32_t> const &count) {
    for (uint32_t i = 0; i < ALPHABET; ++i) {
        std::fprintf(file, "%u%c", count[i], ' ');
        if (ferror(file)) {
            std::cerr << "ERROR: cannot find service information.\n";
            exit(0);
        }
    }
}

void block_rw::read_freq(std::vector<uint32_t> &count) {
    count.resize(2 * ALPHABET);
    char c;
    for (uint32_t i = 0; i < ALPHABET; ++i) {
        std::fscanf(file, "%u%c", &count[i], &c);
        if (ferror(file)) {
            std::cerr << "ERROR: cannot write service information.\n";
            exit(0);
        }
    }
}

void block_rw::read_sum(uint32_t &sum) {
    char c;
    std::fscanf(file, "%u%c", &sum, &c);
}

void block_rw::write_sum(uint32_t const sum) {
    std::fprintf(file, "%u%c", sum, ' ');
}