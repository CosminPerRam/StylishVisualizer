
#include "HeapSort.h"

void HeapSort::heapify(int n, int i)
{
    DO_CHECKEXIT;

    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < n && numbers[l] > numbers[largest])
        largest = l;

    if (r < n && numbers[r] > numbers[largest])
        largest = r;

    stats.addComparisons(2);

    if (largest != i) {
        stats.addSwaps();
        std::swap(numbers[i], numbers[largest]);

        DO_PUT_CURSOR_AT(i);
        DO_PROGRESSIVE_CHECKSTEP;

        heapify(n, largest);
    }
}

void HeapSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    for (int i = n - 1; i > 0; i--) {
        stats.addSwaps();
        std::swap(numbers[0], numbers[i]);

        DO_PUT_CURSOR_AT(i);
        DO_PROGRESSIVE_CHECKSTEP;

        heapify(i, 0);
    }

    DO_FINISHED;
}

const char* HeapSort::getDescription() {
    return "It is similar to selection sort where we first find the minimum element and place the minimum element at the beginning. We repeat the same process for the remaining elements.";
}
