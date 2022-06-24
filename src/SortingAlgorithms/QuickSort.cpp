
#include "SortingAlgorithms/QuickSort.h"

void QuickSort::sorter()
{
    DO_STARTED;

    int l = 0, h = int(numbers.size()) - 1;
    std::vector<int> stack(numbers.size(), 0);

    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];

        DO_PUT_CURSOR_AT(h);
        unsigned x = numbers[h];
        stats.addAssigments();
        int i = (l - 1);

        for (int j = l; j <= h - 1; j++) {
            stats.addComparisons();
            if (numbers[j] <= x) {
                i++;
                std::swap(numbers[i], numbers[j]);

                stats.addSwaps();
            }

            DO_PUT_CURSOR_AT(j);
            DO_CHECKSTEP;
        }
        std::swap(numbers[i + 1], numbers[h]);

        stats.addSwaps();

        const int p = i + 1;

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

    DO_FINISHED;
}

const char* QuickSort::getDescription() {
    return "Picks an element as pivot and partitions the given array around the picked pivot.";
}
