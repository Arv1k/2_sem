cmake_minimum_required(VERSION 3.12)
project(Language)

set(CMAKE_CXX_STANDARD 14)

add_executable(Language main.cpp language.h language.cpp
                        ../../../1_sem/make_enc/enc.h ../../../1_sem/make_enc/enc.cpp
                        tree/binary_tree.cpp tree/binary_tree.h)