
#include "SelectionSort.h"

void SelectionSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            stats.addComparison();
            if (numbers[j] < numbers[min_idx]) {
                min_idx = j;
                DO_PUT_CURSOR_AT(j);
                DO_CHECKSTEP;
            }
        }
        
        std::swap(numbers[min_idx], numbers[i]);
        DO_PUT_CURSOR_AT(min_idx);
        DO_PROGRESSIVE_CHECKSTEP;
    }

    DO_FINISHED;
}
