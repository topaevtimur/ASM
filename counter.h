//
// Created by topayevtimur on 27.10.18.
//

#ifndef ASM_COUNTER_H
#define ASM_COUNTER_H

#include <emmintrin.h>

const char ws = ' ';


size_t naive_count(const char * s, size_t size) {
    size_t result = 0;
    bool space = false;
    for (size_t i = 0; i < size; ++i) {
        if (space && s[i] != ws) {
            ++result;
        }
        space = s[i] == ws;
    }
    return result;
}


size_t naive_count(std::string input) {
    return naive_count(input.c_str(), input.size()) + ((input.size() == 0 || input[0] == ws) ? 0 : 1);
}

size_t count(std::string input) {

    const char *s = input.c_str();
    size_t size = input.size();
    const size_t BLOCK = 16;
    int result = (size == 0 || s[0] == ws) ? 0 : 1;
    size_t offset = (size_t)s % BLOCK;
    if (offset != 0) {
        offset = BLOCK - offset;
        result += naive_count(s, offset);
        s += offset;
        size -= offset;
    }

    __m128i spaces = _mm_set_epi8(ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws, ws);
    __m128i curr, next, tmp;
    __asm__ volatile(
    "movdqa     (%0), %1\n"
            "pcmpeqb    %2, %1\n"
    : "=r" (s),"=x" (next), "=x" (spaces)
    : "0" (s), "1" (next), "2" (spaces)
    : "memory", "cc"
    );


    for (size; size >= 32; size -= 16) {
        int32_t a;
        __asm__ volatile(
        "add        $16,  %0\n"
                "movdqa     %3, %1\n"
                "movdqa     (%0), %2\n"

                "pcmpeqb    %4, %2\n"
                "movdqa     %2, %3\n"

                "palignr    $1, %1, %2\n"
                "pandn      %1, %2\n"
                "pmovmskb   %2, %5\n"
        : "=r" (s), "=x" (curr), "=x" (tmp), "=x" (next), "=x" (spaces), "=r" (a)
        : "0" (s), "1" (curr), "2" (tmp), "3" (next), "4" (spaces), "5" (a)
        : "memory", "cc"
        );

        while (a) {
            a &= a - 1;
            ++result;
        }
    }

    return result + naive_count(s, size);
}

#endif //ASM_COUNTER_H
