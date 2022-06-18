
#include "InsertionSort.h"

void InsertionSort::sorter() {
    DO_STARTED;

    int n = numbers.size(), key, j;
    for (int i = 1; i < n; i++)
    {
        ++stats.reads;
        key = numbers[i];
        j = i - 1;

        ++stats.reads;
        while (j >= 0 && numbers[j] > key)
        {
            stats.addAssigment();
            numbers[j + 1] = numbers[j];
            DO_PUT_CURSOR_AT(j + 1);
            j = j - 1;
            DO_PROGRESSIVE_CHECKSTEP;
        }
        stats.addAssigment();
        numbers[j + 1] = key;
    }

    DO_FINISHED;
}
