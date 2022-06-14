
#include "RadixSortLSD.h"

#include <list>

RadixSortLSD::RadixSortLSD(unsigned count) {
    shuffle(count);
}

void RadixSortLSD::sorter() {
    int maxDigits = 4, n = numbers.size();
    std::list<int> pocket[10];

    for (int i = 0; i < maxDigits; i++) {
        int m = pow(10, i + 1), p = m / 10;

        for (int j = 0; j < n; j++) {
            int temp = (int)numbers[j] % m;
            stats.addAssigment();
            int index = temp / p;
            pocket[index].push_back(numbers[j]);
        }

        int count = 0;
        for (int j = 0; j < 10; j++) {
            while (!pocket[j].empty()) {
                numbers[count] = *(pocket[j].begin());
                stats.addAssigment();
                pocket[j].erase(pocket[j].begin());
                count++;

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
        }
    }

    m_isFinished = true;
}
