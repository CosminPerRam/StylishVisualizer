
#include "CombSort.h"

void CombSort::sorter() {
    DO_STARTED;

    int n = numbers.size(), gap = n;

    bool swapped = true;

    while (gap != 1 || swapped == true)
    {
        gap = (gap * 10) / 13;

        if (gap < 1)
            gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; i++)
        {
            DO_PUT_CURSOR_AT_WITH_BACKWARDS(i + 1);
            stats.addComparison();
            if (numbers[i] > numbers[i + gap])
            {
                stats.addSwap();
                std::swap(numbers[i], numbers[i + gap]);
                swapped = true;

                DO_PROGRESSIVE_CHECKSTEP;
            }
        }
    }

    DO_FINISHED;
}
