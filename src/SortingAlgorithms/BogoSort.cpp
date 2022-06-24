
#include "SortingAlgorithms/BogoSort.h"

#include <algorithm>

#include "Settings.h"
#include "Utilities.h"

void BogoSort::sorter() {
    DO_STARTED;

    const unsigned n = unsigned(numbers.size());
    bool sorted = false;

    do {
        for (unsigned i = 0; i < n; i++)
            std::swap(numbers[i], numbers[Utilities::Random::getNumberInBetween(0, n - 1)]);
        stats.addSwaps(n);

        sorted = true;
        for (unsigned i = 0; i < n - 1 && sorted; i++) {
            if (numbers[i] > numbers[i + 1]) {
                sorted = false;
                stats.addComparisons(i);
            }
        }

        DO_PUT_CURSOR_AT(Utilities::Random::getNumberInBetween(0, n - 1));
        DO_CHECKSTEP;
    } while (!sorted);

    DO_FINISHED;
}

const char* BogoSort::getDescription() {
    return "Randomly generates permutations (possibly one already generated) of its input until it finds one that is sorted.";
}
