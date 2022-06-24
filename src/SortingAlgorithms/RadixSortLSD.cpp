
#include "SortingAlgorithms/RadixSortLSD.h"

#include <list>

#include "Utilities.h"
#include "Settings.h"

void RadixSortLSD::sorter() {
    DO_STARTED;

    unsigned maxDigits = 0, n = unsigned(numbers.size());
    for(unsigned maxValue = Settings::SHUFFLE_MAX_VALUE; maxValue != 0; maxValue /= 10)
        ++maxDigits;

    std::list<unsigned> pocket[10];

    for (unsigned i = 0; i < maxDigits; i++) {
        unsigned m = Utilities::Math::pow(10, i + 1), p = m / 10;

        for (unsigned j = 0; j < n; j++) {
            DO_PUT_CURSOR_AT(j);
            unsigned temp = numbers[j] % m;
            unsigned index = temp / p;
            pocket[index].push_back(numbers[j]);
        }
        stats.addAssigments(n);

        unsigned count = 0;
        for (unsigned j = 0; j < 10; j++) {
            while (!pocket[j].empty()) {
                numbers[count] = *(pocket[j].begin());
                DO_PUT_CURSOR_AT(count);
                stats.addAssigments();
                pocket[j].erase(pocket[j].begin());
                count++;

                DO_CHECKSTEP;
            }
        }
    }

    DO_FINISHED;
}

const char* RadixSortLSD::getDescription() {
    return "Radix sort LSD does digit by digit sort starting from least significant digit to most significant digit. Radix sort uses counting sort as a subroutine to sort.";
}
