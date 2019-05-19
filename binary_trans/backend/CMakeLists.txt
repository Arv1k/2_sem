cmake_minimum_required(VERSION 3.14)
project(backend)

set(CMAKE_CXX_STANDARD 14)

add_executable(backend main.cpp backend.h backend.cpp
               tree/binary_tree.h tree/binary_tree.cpp
               ../../../1_sem/make_enc/enc.h ../../../1_sem/make_enc/enc.cpp)