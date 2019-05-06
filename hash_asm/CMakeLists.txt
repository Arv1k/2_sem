cmake_minimum_required(VERSION 3.13)
project(hash_asm)

set(CMAKE_CXX_STANDARD 14)

add_executable(hash_asm main.cpp hash_asm.cpp hash_asm.h
                                 list/list.h list/list.cpp
                                 ../../1_sem/make_enc/enc.h ../../1_sem/make_enc/enc.cpp)