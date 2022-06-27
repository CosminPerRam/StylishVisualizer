
#include "SortingAlgorithms/InsertionSort.h"

void InsertionSort::sorter() {
    DO_STARTED;

    const int n = int(numbers.size());
    int j;
    unsigned key;
    
    for (int i = 1; i < n; i++)
    {
        key = numbers[i];
        stats.addAssigments();
        j = i - 1;

        stats.addComparisons();
        while (j >= 0 && numbers[j] > key)
        {
            stats.addAssigments();
            numbers[j + 1] = numbers[j];
            DO_PUT_CURSOR_AT(j + 1);
            DO_CHECKSTEP;
            j = j - 1;
        }
        stats.addAssigments();
        numbers[j + 1] = key;
        DO_CHECKSTEP;
    }

    DO_FINISHED;
}

const char* InsertionSort::getDescription() {
    return "The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.";
}
