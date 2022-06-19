
#include "BitonicSort.h"

void BitonicSort::bitonicMerge(int low, int cnt, int dir)
{
    DO_CHECKEXIT;

    if (cnt > 1)
    {
        const int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            stats.addComparisons();
            if (dir == (numbers[i] > numbers[i + k])) {
                stats.addSwaps();
                std::swap(numbers[i], numbers[i + k]);

                DO_PUT_CURSOR_AT(i + k);
                stats.addStep();
            }
            else
                DO_PUT_CURSOR_AT(i);

            DO_CHECKSTEP;
        }

        bitonicMerge(low, k, dir);
        bitonicMerge(low + k, k, dir);
    }
}

void BitonicSort::bitonicSort(int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        bitonicSort(low, k, 1);
        bitonicSort(low + k, k, 0);

        bitonicMerge(low, cnt, dir);
    }
}

void BitonicSort::sorter() {
    DO_STARTED;

    bitonicSort(0, numbers.size(), 1);

    DO_FINISHED;
}

const char* BitonicSort::getDescription() {
    return "Bitonic sort is a comparison-based sorting algorithm that can be run in parallel. It focuses on converting a random sequence of numbers into a bitonic sequence, one that monotonically increases, then decreases. Not running paralleled.";
}
