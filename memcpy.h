//
// Created by topayevtimur on 06.10.17.
//

#ifndef ASM_MEMCPY_H
#define ASM_MEMCPY_H


#include <emmintrin.h>

void naive_memcpy(char* dst, char const* src, size_t size) {
    for (size_t i = 0; i < size; i++) {
        *(dst + i) = *(src + i);
    }
}


void my_memcpy(char* dst, char const* src, size_t size) {
    const size_t BLOCK = 16;
    size_t offset = (size_t)dst % BLOCK;
    if (offset != 0) {
        offset = BLOCK - offset;
        naive_memcpy(dst, src, offset);
        size -= offset;
    }


    char* srcc = (char *) (src + offset);
    char* dstt = (char *) (dst + offset);



//    for (size_t i = offset; i < size - (size - offset) % BLOCK; i += BLOCK)
//    {
//        __m128i reg;
//
//        __asm__ volatile (
//            "movdqu\t (%1), %0\n"
//            "movntdq\t %0, (%2)\n"
//        : "=x"(reg)
//        : "r"(srcc), "r"(dstt)
//        :"memory");
//
//        srcc += BLOCK;
//        dstt += BLOCK;
//    }
    int i = size - (size - offset) % BLOCK;
    __m128i reg;
    __asm__ volatile (
            "l:\n"
            "cmp  $16, %2\n"
            "jb ex\n"
            "movdqu  (%1), %3\n"
            "movntdq %3, (%0)\n"
            "add     $16,  %0\n"
            "add     $16,  %1\n"
            "sub     $16,  %2\n"
            "jmp     l\n"
            "ex:\n"
    :"=r"(dstt), "=r"(srcc), "=r"(i), "=x"(reg)
    :"0"(dstt), "1"(srcc), "2"(i)
    :"memory"
    );


    naive_memcpy(dstt, srcc, (size - offset) % BLOCK);

    _mm_sfence();
}

void my_memcpy(void* dst, void const* src, size_t size) {
    my_memcpy(static_cast<char*>(dst), static_cast<char const*>(src), size);
}

#endif //ASM_MEMCPY_H
