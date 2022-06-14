
#include "BubbleSort.h"

BubbleSort::BubbleSort(unsigned count) {
	shuffle(count);
}

void BubbleSort::sorter() {
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            stats.addComparison();
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);

                stats.addSwap();
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
