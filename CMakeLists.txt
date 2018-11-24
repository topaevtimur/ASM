cmake_minimum_required(VERSION 3.8)
project(ASM)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp memcpy.h counter.h)
set(TRAMP trampoline.cpp)

add_executable(ASM ${SOURCE_FILES} main.cpp)
add_executable(asm3_trampoline ${TRAMP} trampoline.cpp)