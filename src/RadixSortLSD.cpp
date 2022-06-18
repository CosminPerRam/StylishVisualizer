
#include "RadixSortLSD.h"

#include <list>

#include "Utilities.h"

void RadixSortLSD::sorter() {
    DO_STARTED;

    int maxDigits = 4, n = numbers.size();
    std::list<unsigned> pocket[10];

    for (int i = 0; i < maxDigits; i++) {
        int m = Utilities::Math::pow(10, i + 1), p = m / 10;

        for (int j = 0; j < n; j++) {
            DO_PUT_CURSOR_AT(j);
            int temp = (int)numbers[j] % m;
            stats.addAssigment();
            int index = temp / p;
            pocket[index].push_back(numbers[j]);
        }

        int count = 0;
        for (int j = 0; j < 10; j++) {
            while (!pocket[j].empty()) {
                numbers[count] = *(pocket[j].begin());
                DO_PUT_CURSOR_AT(count);
                stats.addAssigment();
                pocket[j].erase(pocket[j].begin());
                count++;

                DO_PROGRESSIVE_CHECKSTEP;
            }
        }
    }

    DO_FINISHED;
}

const char* RadixSortLSD::getDescription() {
    return "Radix sort LSD does digit by digit sort starting from least significant digit to most significant digit. Radix sort uses counting sort as a subroutine to sort.";
}
