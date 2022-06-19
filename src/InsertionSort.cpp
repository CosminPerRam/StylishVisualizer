
#include "InsertionSort.h"

void InsertionSort::sorter() {
    DO_STARTED;

    int n = numbers.size(), j;
    unsigned key;
    for (int i = 1; i < n; i++)
    {
        key = numbers[i];
        j = i - 1;

        stats.addReads(2);
        while (j >= 0 && numbers[j] > key)
        {
            stats.addAssigments();
            numbers[j + 1] = numbers[j];
            DO_PUT_CURSOR_AT(j + 1);
            DO_PROGRESSIVE_CHECKSTEP;
            j = j - 1;
        }
        stats.addAssigments();
        numbers[j + 1] = key;
    }

    DO_FINISHED;
}

const char* InsertionSort::getDescription() {
    return "The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.";
}
