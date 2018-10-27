#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

#include "memcpy.h"
#include "counter.h"

void printTime(std::string name, clock_t begin, clock_t end, int divisor) {
    printf("> %s done in %f <\n", name.c_str(), double(end - begin) / CLOCKS_PER_SEC / divisor);
}

clock_t begin, end;
std::string start = "Started %s testing...\n";
std::string finish = "Finished %s testing.\n";

int main(int argc, char* argv[])
{

  srand(time(NULL));

//    for (int i = 0; i < 1000; i++)
//    {
//        int n = rand() % 10000 + 1;
//        int a[n];
//        int b[n];
//        for (size_t j = 0; j < n; j++)
//        {
//            a[j] = rand();
//        }
//        my_memcpy(b, a, sizeof(a));
//        for (int j = 0; j < n; j++)
//        {
//            if (a[j] != b[j])
//            {
//                std::cout << ":(\n";
//                return 0;
//            }
//        }
//        std::cout << "OK\n";
//    }
//

    std::srand((uint)std::time(nullptr));
    int n = std::rand() % 1000000 + 10000000;
    std::string text = "";
    text.append(std::string((uint)std::rand() % 5, ' '));
    for (int i = 1; i <= n; i++) {
        text.append(std::to_string(i));
        text.append(std::string((uint)std::rand() % 10 + 1, ' '));
    }
   printf(start.c_str(), "word counter");

    printf("Counting %d words\n", n);
    int m;

    begin = clock();
    m = count(text);
    end = clock();
    if (m != n) {
        printf("error counting, expected %d, found %d", n, m);
        return 1;
    }
    printTime("count", begin, end, 1);

    begin = clock();
    m = naive_count(text);
    end = clock();
    if (m != n) {
        printf("error counting, expected %d, found %d", n, m);
        return 1;
    }
    printTime("naive", begin, end, 1);

    printf(finish.c_str(), "word counter");


    return 0;
}