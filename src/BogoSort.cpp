
#include "BogoSort.h"

#include <algorithm>

#include "Settings.h"
#include "Utilities.h"

void BogoSort::sorter() {
    DO_STARTED;

    unsigned n = numbers.size();
    bool sorted = false;

    do {
        for (unsigned i = 0; i < n; i++) {
            std::swap(numbers[i], numbers[Utilities::Random::getNumberInBetween(0, n)]);
            ++stats.writes;
        }

        DO_PUT_CURSOR_AT(0);
        DO_PROGRESSIVE_CHECKSTEP;

        sorted = true;
        for (unsigned i = 0; i < n - 1 && sorted; i++) {
            stats.addComparison();
            if (numbers[i] > numbers[i + 1])
                sorted = false;
        }
    } while (!sorted);

    DO_PUT_CURSOR_AT(n - 1);

    DO_FINISHED;
}

const char* BogoSort::getDescription() {
    return "Randomly generates permutations (possibly one already generated) of its input until it finds one that is sorted.";
}
