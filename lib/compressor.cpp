#include <cstring>
#include <cassert>
#include <set>
#include "compressor.h"

compressor::compressor() {
    children = std::vector <std::pair<int, int>> (2 * SIZE, std::make_pair(-1, -1));
    count = std::vector <uint32_t> (2 * SIZE, 0);
    codes = std::vector<std::vector <bool>> (SIZE);
}
void compressor::count_freq(std::vector <unsigned char> const &data) {
    for (unsigned char c : data) {
        count[(size_t) c]++;
    }
}

void compressor::codes_generate(int cur, std::vector <bool> &code) {
    if (children[cur] == std::make_pair(-1, -1)) {
        if (code.empty())
            code.push_back(0);
        codes[cur] = code;
        return;
    }
    code.push_back(0);
    codes_generate(children[cur].first, code);
    code[code.size() - 1] = 1;
    codes_generate(children[cur].second, code);
    code.pop_back();
}

void compressor::make_tree() {
    std::set <std::pair<uint32_t, int>> queue;

    for (size_t c = 0; c < SIZE; ++c) {
        if (count[c] > 0)
            queue.insert(std::make_pair(count[c], c));
    }

    int p = SIZE;

    while (queue.size() > 1) {
        int first, second;
        first = (*queue.begin()).second;
        queue.erase(*queue.begin());
        second = (*queue.begin()).second;
        queue.erase(*queue.begin());
        int par = p++;
        children[par] = std::make_pair(first, second);
        count[par] = count[first] + count[second];
        queue.insert(std::make_pair(count[par], par));
    }

    if (!queue.empty())
        root = (*queue.begin()).second;
    queue.clear();
    std::vector <bool> code;
    codes_generate(root, code);
}

void compressor::compress(std::vector<unsigned char> const &data, std::vector<unsigned char> &new_data) {
    size_t len = 0;
    uint8_t new_char = 0;

    for (unsigned char c : data) {
        for (bool b : codes[(uint32_t)c]) {
            new_char = (new_char << 1u) + b;
            len++;
            if (len == 8) {
                new_data.push_back((unsigned char)new_char);
                len = 0;
                new_char = 0;
            }
        }
    }

    if (len > 0) {
        new_char <<= (8u - len);
        new_data.push_back(new_char);
    }
}

std::vector <uint32_t> compressor::get_count() {
    return count;
}