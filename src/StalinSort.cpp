
#include "StalinSort.h"

#include "Settings.h"

void StalinSort::sorter() {
    DO_STARTED;

    for (unsigned i = 0; i < numbers.size() - 1; ) {
        DO_PUT_CURSOR_AT(i);

        if (numbers[i] < numbers[i + 1])
            i++;
        else {
            numbers.erase(numbers.begin() + i + 1);
            Settings::updateCursorLineWidthDynamically(numbers.size());
        }

        DO_PROGRESSIVE_CHECKSTEP;
    }

    DO_FINISHED;
}
