#include <iostream>
#include <vector>
#include "console_util/utility.h"
#include <fstream>
#include <ctime>

void run_tests();

int main() {
    run_tests();
    return 0;
}

const size_t S_SZ = 100, B_SZ = 10, SMALL = 1000, BIG = 1000000, ALPHABET = 256;

const char *a = "a.txt", *b = "b.txt", *c = "c.txt";

void test_empty();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();


bool simile() {
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

void work() {
    double time = clock();
    compress_file(a, b);
    decompress_file(b, c);
    if (!simile()) {
        std::cout << "FAILED:   decompressed and initial files are not equal.\n";
        exit(0);
    }
    time = (clock() - time) / CLOCKS_PER_SEC;
    std::cout << "OK:   working time is " << time << " sec." << "\n";
}

void run_tests() {
    // determine tests
    test_empty();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    size_t number = 7;

    // random small tests

    std::cout << "|   TESTSET RANDOM SMALL   |\n";

    for (size_t i = 0; i < S_SZ; ++i) {
        std::cout << "TEST " << number++ << "    |    ";
        std::ofstream fa(a), fc(c);
        size_t size = rand() % SMALL + SMALL;
        for (size_t j = 0; j < size; ++j) {
            auto c = (unsigned char)(rand() % ALPHABET);
            fa << c;
        }
        fa.close();
        work();
    }

    // random big tests

    std::cout << "|   TESTSET RANDOM BIG   |\n";

    for (size_t i = 0; i < B_SZ; ++i) {
        std::cout << "TEST " << number++ << "    |    ";
        std::ofstream fa(a), fc(c);
        size_t size = rand() % BIG + BIG;
        for (size_t j = 0; j < size; ++j) {
            auto c = (unsigned char)(rand() % ALPHABET);
            fa << c;
        }

        fa.close();
        work();
    }

    // random size tests

    std::cout << "|   TESTSET COMPLETELY RANDOM   |\n";

    for (size_t i = 0; i < B_SZ; ++i) {
        std::cout << "TEST " << number++ << "    |    ";
        std::ofstream fa(a), fc(c);
        size_t size = rand() % BIG;
        for (size_t j = 0; j < size; ++j) {
            auto c = (unsigned char)(rand() % ALPHABET);
            fa << c;
        }

        fa.close();
        work();
    }

    std::cout << "ALL TESTS PASSED!\n";
}

void test_empty() {
    std::cout << "TEST EMPTY    |    ";
    std::ofstream fa(a);
    fa.close();
    work();
}

void test1() {
    std::cout << "TEST 1        |    ";
    std::ofstream fa(a);
    fa << "1041074 1 83408 0198 09\n  78173987  3 ";
    fa.close();
    work();
}

void test2() {
    std::cout << "TEST 2        |    ";
    std::ofstream fa(a);
    fa << "jdsjh jhhdsjh  bsbdkjb bsb ksb 198 09\n    d \nc d s ds dd  d s  3 ";
    fa.close();
    work();
}

void test3() {
    std::cout << "TEST 3        |    ";
    std::ofstream fa(a);
    fa << "10410d cd ddd74 1 83408 dcd d  0198 09\n    d \nc d s ds dd  d ss  s s\n ds\0 \0\0\0 \23 \128 \255  3 ";
    fa.close();
    work();
}

void test4() {
    std::cout << "TEST 4        |    ";
    std::ofstream fa(a);
    fa << "Merry Christmas and Happy New 2019 Year! =) ^_^";
    fa.close();
    work();
}

void test5() {
    std::cout << "TEST 5        |    ";
    std::ofstream fa(a);
    fa << "Os iusti meditabitur sapientiam\n"
          "Et lingua eius loquetur iudicium\n"
          "Beatus vir qui suffert tentationem\n"
          "Quonicum cum probatus fuerit accipiet coronam vitae\n"
          "\n"
          "Kyrie, Ignis Divine, Eleison\n"
          "O quam sancta, quam serelena, quam benigna\n"
          "Quam amoena O castitatis lilium";
    fa.close();
    work();
}

void test6() {
    std::cout << "TEST 6        |    ";
    std::ofstream fa(a);
    fa << "DR HORRIBLE\n"
          "Any dolt with half a brain\n"
          "Can see that human-kind has gone insane,\n"
          "To the point where I don't know,\n"
          "If I'll upset the status quo,\n"
          "If I throw poison in the water main.\n"
          "\n"
          "Listen close to everybody's heart,\n"
          "And hear that breaking sound.\n"
          "Hopes and dreams are shattering apart\n"
          "And crashing to the ground!\n"
          "\n"
          "I cannot believe my eyes!\n"
          "How the world's filled with filth and lies!\n"
          "But it's plain to see,\n"
          "Evil inside of me\n"
          "Is on the rise.\n"
          "\n"
          "PENNY\n"
          "Look around,\n"
          "We're living with the lost and found.\n"
          "Just when you feel you've almost drowned,\n"
          "You find yourself on solid ground.\n"
          "\n"
          "And you believe, there's good in everybody's heart,\n"
          "Keep it safe and sound.\n"
          "With hope you can do your part,\n"
          "To turn a life around!\n"
          "\n"
          "I cannot believe my eyes!\n"
          "Is the world finally growing wise?\n"
          "'Cause it seems to me!\n"
          "Some kind of harmony\n"
          "Is on the rise.\n";
    fa.close();
    work();
}