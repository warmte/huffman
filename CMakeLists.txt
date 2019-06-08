cmake_minimum_required(VERSION 3.10)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman main.cpp lib/compressor.h lib/compressor.cpp lib/decompressor.h lib/decompressor.cpp console_util/block_rw.h console_util/block_rw.cpp console_util/utility.h console_util/utility.cpp)
add_executable(huffman_tester huffman_tester.cpp lib/compressor.h lib/compressor.cpp lib/decompressor.h lib/decompressor.cpp console_util/block_rw.h console_util/block_rw.cpp console_util/utility.h console_util/utility.cpp)


