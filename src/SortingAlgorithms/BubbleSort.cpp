
#include "SortingAlgorithms/BubbleSort.h"

void BubbleSort::sorter() {
    DO_STARTED;

    const int n = int(numbers.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            DO_PUT_CURSOR_AT_WITH_BACKWARDS(j + 1);

            stats.addComparisons();
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);

                stats.addSwaps();
            }

            DO_CHECKSTEP;
        }
    }

    DO_FINISHED;
}

const char* BubbleSort::getDescription() {
    return "Compares two adjacent elements and swaps them until they are not in the intended order. Be careful, don't pop the bubble.";
}
