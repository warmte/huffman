cmake_minimum_required(VERSION 3.10)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman_tester huffman_tester.cpp lib/compressor.h lib/compressor.cpp lib/decompressor.h lib/decompressor.cpp console_util/block_rw.h console_util/block_rw.cpp console_util/utility.h console_util/utility.cpp)

add_executable(UTILITY UTILITY.cpp lib/compressor.h lib/compressor.cpp lib/decompressor.h lib/decompressor.cpp console_util/block_rw.h console_util/block_rw.cpp console_util/utility.h console_util/utility.cpp)


add_library(huflibrary STATIC
        lib/compressor.h lib/compressor.cpp lib/decompressor.h lib/decompressor.cpp)

add_executable(huflib
        console_util/block_rw.h console_util/block_rw.cpp console_util/utility.h console_util/utility.cpp huffman_tester.cpp)

target_link_libraries(huflib huflibrary)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb -std=c++11 -pedantic -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG  -fsanitize=address,undefined,leak")
endif()