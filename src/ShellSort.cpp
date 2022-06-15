
#include "ShellSort.h"

void ShellSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            float temp = numbers[i];
            stats.addAssigment();

            int j;
            for (j = i; j >= gap && numbers[j - gap] > temp; j -= gap) {
                numbers[j] = numbers[j - gap];
                DO_PUT_CURSOR_AT(j);

                stats.addComparison();
                stats.addAssigment();
                
                DO_PROGRESSIVE_CHECKSTEP;
            }

            numbers[j] = temp;
            stats.addAssigment();
        }
    }

    DO_FINISHED;
}
