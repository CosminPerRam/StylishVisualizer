
#include "BubbleSort.h"

void BubbleSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            stats.addComparison();
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);

                stats.addSwap();
                DO_PROGRESSIVE_CHECKSTEP;
            }
        }
    }

    DO_FINISHED;
}
