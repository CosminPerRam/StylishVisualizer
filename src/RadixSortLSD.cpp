
#include "RadixSortLSD.h"

#include <list>

#include "Utilities.h"

RadixSortLSD::RadixSortLSD(unsigned count) {
    shuffle(count);
}

void RadixSortLSD::sorter() {
    int maxDigits = 4, n = numbers.size();
    std::list<int> pocket[10];

    for (int i = 0; i < maxDigits; i++) {
        int m = Utilities::Math::pow(10, i + 1), p = m / 10;

        for (int j = 0; j < n; j++) {
            int temp = (int)numbers[j] % m;
            stats.addAssigment();
            int index = temp / p;
            pocket[index].push_back(numbers[j]);
        }

        int count = 0;
        for (int j = 0; j < 10; j++) {
            while (!pocket[j].empty()) {
                numbers[count] = static_cast<float>(*(pocket[j].begin()));
                stats.addAssigment();
                pocket[j].erase(pocket[j].begin());
                count++;

                DO_CHECKSTEP_INSTRUCTIONS; ++stats.steps;
            }
        }
    }

    m_isFinished = true;
}
