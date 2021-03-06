
#include "SortingAlgorithms/StalinSort.h"

#include "Settings.h"

void StalinSort::sorter() {
    DO_STARTED;

    for (unsigned i = 0; i < numbers.size() - 1; ) {
        DO_PUT_CURSOR_AT(i);

        stats.addComparisons();
        if (numbers[i] < numbers[i + 1])
            i++;
        else {
            numbers.erase(numbers.begin() + i + 1);
            stats.addReads();
            Settings::updateCursorLineWidthDynamically(unsigned(numbers.size()));
        }

        DO_CHECKSTEP;
    }

    DO_FINISHED;
}

const char* StalinSort::getDescription() {
    return "Stalin sort is a nonsensical 'sorting' algorithm in which each element that is not in the correct order is simply eliminated from the list.";
}
