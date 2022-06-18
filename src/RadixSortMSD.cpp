
#include "RadixSortMSD.h"

#include <unordered_map>
#include <algorithm>

#include "Utilities.h"

#define RADIX 256

int digit_at(int x, int d)
{
    return (x / Utilities::Math::pow(10, d - 1)) % 10;
}

short int getByte(unsigned int elem, unsigned int i) {
    if (sizeof(elem) > i) { return (elem >> ((3 - i) * 8) & (255)); }
    else return -1;
}

void RadixSortMSD::MSDRadixSort(int low, int high, int digit) {
    std::vector<unsigned> counter(RADIX + 2);

    for (int i = low; i < high; ++i) {
        counter[getByte(numbers[i], digit) + 2]++;
        ++stats.reads;
        DO_PUT_CURSOR_AT(i);
    }

    for (int r = 0; r < RADIX + 1; ++r)
        counter[r + 1] += counter[r];

    for (int i = low; i < high; ++i) {
        tabAux[counter[getByte(numbers[i], digit) + 1]++] = numbers[i];
        ++stats.reads; ++stats.reads;
        DO_PUT_CURSOR_AT(i);
    }

    for (int i = low; i < high; ++i) {
        numbers[i] = tabAux[i - low];
        stats.addAssigment();
        DO_CHECKSTEP; DO_PUT_CURSOR_AT(i);
    }

    for (int r = 0; r < RADIX + 1; ++r) {
        if (counter[r] < counter[r + 1])
            MSDRadixSort(low + counter[r], low + counter[r + 1], digit + 1);
    }

    DO_PROGRESSIVE_CHECKSTEP;
}

void RadixSortMSD::sorter() {
    DO_STARTED;

    tabAux.resize(numbers.size());
    MSDRadixSort(0, numbers.size(), 0);

    DO_FINISHED;
}

const char* RadixSortMSD::getDescription() {
    return "Radix sort MSD does digit by digit sort starting from most significant digit to least significant digit. Radix sort uses counting sort as a subroutine to sort.";
}
