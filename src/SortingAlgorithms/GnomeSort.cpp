
#include "SortingAlgorithms/GnomeSort.h"

void GnomeSort::sorter() {
    DO_STARTED;

    int n = numbers.size(), index = 0;
    while (index < n) {
        if (index == 0)
            index++;

        stats.addComparisons();
        if (numbers[index] >= numbers[index - 1])
            index++;
        else {
            stats.addSwaps();
            std::swap(numbers[index], numbers[index - 1]);
            index--;
        }

        DO_PUT_CURSOR_AT(index);
        DO_PROGRESSIVE_CHECKSTEP;
    }

    DO_FINISHED;
}

const char* GnomeSort::getDescription() {
    return "Gnome sort works by building a sorted list one element at a time, getting each item to the proper place in a series of swaps.";
}
