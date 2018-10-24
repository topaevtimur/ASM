//
// Created by topayevtimur on 06.10.17.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

#include "memcpy.h"


//#define memcpy
//#define debug

void printTime(std::string name, clock_t begin, clock_t end, int divisor) {
    printf("> %s done in %f <\n", name.c_str(), double(end - begin) / CLOCKS_PER_SEC / divisor);
}

clock_t begin, end;
std::string start = "Started %s testing...\n";
std::string finish = "Finished %s testing.\n";

int main(int argc, char* argv[])
{
    size_t const N = 100000000;
    size_t const M = 100;
    std::vector<char> a(N), b(N);

    printf(start.c_str(), "memcpy");

    begin = clock();
    for (size_t i = 0; i != M; ++i)
        my_memcpy(b.data(), a.data(), N);
    end = clock();
    printTime("memcpy", begin, end, M);

    begin = clock();
    for (size_t i = 0; i != 10; ++i) {
        naive_memcpy(b.data(), a.data(), N);
    }
    end = clock();
    printTime("naive", begin, end, 10);

    printf(finish.c_str(), "memcpy");



    return 0;
}
