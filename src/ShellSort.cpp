
#include "ShellSort.h"

ShellSort::ShellSort(unsigned count) {
    shuffle(count);
}

void ShellSort::sorter() {
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

                stats.addComparison();
                stats.addAssigment();

                DO_CHECKSTEP_INSTRUCTIONS; ++stats.steps;
            }

            numbers[j] = temp;
            stats.addAssigment();
        }
    }

    m_isFinished = true;
}
