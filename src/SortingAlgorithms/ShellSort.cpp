
#include "SortingAlgorithms/ShellSort.h"

void ShellSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            unsigned temp = numbers[i];
            stats.addAssigments();

            int j;
            for (j = i; j >= gap && numbers[j - gap] > temp; j -= gap) {
                numbers[j] = numbers[j - gap];
                DO_PUT_CURSOR_AT(j);

                stats.addComparisons();
                stats.addAssigments();
                
                DO_PROGRESSIVE_CHECKSTEP;
            }

            numbers[j] = temp;
            stats.addAssigments();
        }
    }

    DO_FINISHED;
}

const char* ShellSort::getDescription() {
    return "First sorts elements that are far apart from each other and successively reduces the interval between the elements to be sorted. The interval between the elements is reduced based on the sequence used.";
}
