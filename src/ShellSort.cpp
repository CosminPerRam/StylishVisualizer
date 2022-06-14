
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
                ++stats.steps;

                bool goContinue = false;
                while (!goContinue) {
                    stepState state = this->checkStep();
                    if (state == stepState::EXITED)
                        return;
                    else if (state != stepState::PAUSED)
                        goContinue = true;
                }
            }

            numbers[j] = temp;
            stats.addAssigment();
        }
    }

    m_isFinished = true;
}
