
#include "CocktailSort.h"

void CocktailSort::sorter() {
    DO_STARTED;

    int n = numbers.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        DO_PROGRESSIVE_CHECKSTEP;

        swapped = false;

        for (int i = start; i < end; ++i)
        {
            DO_PUT_CURSOR_AT_WITH_BACKWARDS(i + 1);
            stats.addComparisons();
            if (numbers[i] > numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
                stats.addSwaps();
                swapped = true;
            }

            DO_CHECKSTEP;
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            DO_PUT_CURSOR_AT_WITH_FORWARDS(i);
            stats.addComparisons();
            if (numbers[i] > numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
                stats.addSwaps();
                swapped = true;
            }

            DO_CHECKSTEP;
        }

        ++start;
    }

    DO_FINISHED;
}

const char* CocktailSort::getDescription() {
    return "Traverses elements from left to right until they are placed in the last viable position.";
}
