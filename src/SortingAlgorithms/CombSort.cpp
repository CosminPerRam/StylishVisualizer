
#include "SortingAlgorithms/CombSort.h"

void CombSort::sorter() {
    DO_STARTED;

    const int n = int(numbers.size());
    int gap = n;

    bool swapped = true;

    while (gap != 1 || swapped == true)
    {
        gap = (gap * 10) / 13;

        if (gap < 1)
            gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; i++)
        {
            stats.addComparisons();
            if (numbers[i] > numbers[i + gap])
            {
                stats.addSwaps();
                std::swap(numbers[i], numbers[i + gap]);
                swapped = true;

                DO_PUT_CURSOR_AT(i);
            }
            else
                DO_PUT_CURSOR_AT_WITH_BACKWARDS(i + 1);

            DO_CHECKSTEP;
        }
    }

    DO_FINISHED;
}

const char* CombSort::getDescription() {
    return "Comb sort improves the bubble sort by using a gap of size more than 1. The gap in the comb sort starts with the larger value and then shrinks by a factor of 1.3. It means that after the completion of each phase, the gap is divided by the shrink factor 1.3. The iteration continues until the gap is 1.";
}
