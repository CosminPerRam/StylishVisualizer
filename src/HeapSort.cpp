
#include "HeapSort.h"

void HeapSort::heapify(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    stats.addComparison();
    if (l < n && numbers[l] > numbers[largest])
        largest = l;

    stats.addComparison();
    if (r < n && numbers[r] > numbers[largest])
        largest = r;

    if (largest != i) {
        stats.addSwap();
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
        stats.addSwap();
        std::swap(numbers[0], numbers[i]);

        DO_PUT_CURSOR_AT(i);
        DO_CHECKSTEP;

        heapify(i, 0);
    }

    DO_FINISHED;
}
