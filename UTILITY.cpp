#include "console_util/utility.h"
#include <iostream>
#include <cstring>
#include <fstream>

bool simile(const char *a, const char *c) {
    bool res = true;
    std::ifstream fa(a);
    std::ifstream fc(c);
    char c1, c2;
    int i = 0;
    while (fa.get(c1) && res) {
        i++;
        if (fc.get(c2)) {
            res = (c1 == c2);
        } else {
            res = false;
        }
        if (!res) std::cerr << i << ' ' << c1 << ' ' << c2 << "\n";
    }
    if (!fa.get(c1) && fc.get(c2)) {
        res = false;
    }
    fa.close();
    fc.close();
    return res;
}

void work(const char *a, const char *b, const char *c) {
    double time = clock();
    compress_file(a, b);
    decompress_file(b, c);
    if (!simile(a, c)) {
        std::cout << "FAILED:   decompressed and initial files are not equal.\n";
        exit(0);
    }
    time = (clock() - time) / CLOCKS_PER_SEC;
    std::cout << "OK:   working time is " << time << " sec." << "\n";
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "wrong arguments number\n";
        EXIT_FAILURE;
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0) {
        compress_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "-d") == 0) {
        decompress_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "-s") == 0) {
        std::cerr << (simile(argv[2], argv[3]) ? "SIMILAR\n" : "NOT SIMILAR\n");
    } else {
        std::cerr << "wrong mode\n";
        EXIT_FAILURE;
        return 0;
    }
    std::cerr << "DONE\n";
    EXIT_SUCCESS;
    return 0;
}