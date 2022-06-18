
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
            numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
            ++stats.writes;
        }

        DO_PUT_CURSOR_AT(0);
        DO_PROGRESSIVE_CHECKSTEP;

        sorted = true;
        for (unsigned i = 0; i < n - 1; i++) {
            stats.addComparison();
            if (numbers[i] > numbers[i + 1]) {
                sorted = false;
                continue;
            }
        }
    } while (!sorted);

    DO_PUT_CURSOR_AT(n - 1);

    DO_FINISHED;
}
