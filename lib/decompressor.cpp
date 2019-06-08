#include <iostream>
#include "decompressor.h"
#include <set>

decompressor::decompressor() = default;
decompressor::decompressor(std::vector <uint32_t> _count) {
    sum = 0;
    count = std::vector <uint32_t> (2 * SIZE, 0);
    children = std::vector <std::pair<int, int>> (2 * SIZE, std::make_pair(-1, -1));
    count = _count;
    fill(count.begin() + SIZE, count.end(), 0);
    for (size_t i = 0; i < SIZE; ++i) {
        sum += count[i];
    }
}

void decompressor::make_tree() {
    std::set <std::pair<uint32_t, int>> queue;

    for (size_t c = 0; c < SIZE; ++c) {
        if (count[c] > 0)
            queue.insert(std::make_pair(count[c], /*(uint32_t)*/c));
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

    root = (*queue.begin()).second;
    queue.clear();
}

void decompressor::decompress(std::vector <unsigned char> const &data, std::vector <unsigned char> &new_data) {
    int cur = root;
    if (children[cur].first == -1) {
        for (uint32_t i = 0; i < sum; ++i) new_data.push_back((unsigned char)cur);
        return;
    }
    uint32_t symb = 0;
    for (unsigned char c : data) {
        for (int i = 7; i >= 0; --i) {
            bool b = bool(((uint32_t)c >> i) & 1);
            cur = (b ? children[cur].second : children[cur].first);
            if (children[cur].first == -1) {
                new_data.push_back((unsigned char)cur);
                symb++;
                if (symb == sum)
                    break;
                cur = root;
            }
        }
    }
}
