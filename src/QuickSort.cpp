
#include "QuickSort.h"

QuickSort::QuickSort(unsigned count) {
    shuffle(count);
}

void QuickSort::sorter()
{
    int l = 0, h = numbers.size() - 1;
    std::vector<int> stack(numbers.size(), 0);

    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];

        float x = numbers[h];
        stats.addAssigment();
        int i = (l - 1);

        for (int j = l; j <= h - 1; j++) {
            stats.addComparison();
            if (numbers[j] <= x) {
                i++;
                std::swap(numbers[i], numbers[j]);

                stats.addSwap();
                DO_CHECKSTEP_INSTRUCTIONS; ++stats.steps;
            }
        }
        std::swap(numbers[i + 1], numbers[h]);

        stats.addSwap();

        int p = i + 1;

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

    m_isFinished = true;
}
