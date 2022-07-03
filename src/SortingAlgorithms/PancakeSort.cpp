
#include "SortingAlgorithms/PancakeSort.h"

void PancakeSort::flip(unsigned i)
{
    DO_CHECKEXIT;

    unsigned temp;
    for(unsigned start = 0; start < i; start++, i--) {
        temp = numbers[start];
        numbers[start] = numbers[i];
        numbers[i] = temp;
        stats.addAssigments(3);
        DO_PUT_CURSOR_AT(start);
        DO_CHECKSTEP;
    }
}

void PancakeSort::sorter() {
    DO_STARTED;

    unsigned n = (unsigned)numbers.size();
    for (unsigned curr_size = n; curr_size > 1; --curr_size) {
        unsigned mi = 0;
        for(unsigned i = 0; i < curr_size; ++i) {
            if(numbers[i] > numbers[mi]) {
                stats.addAssigments();
                mi = i;
            } 
        }
        stats.addComparisons(curr_size);
        DO_CHECKEXIT;
  
        if (mi != curr_size - 1) {
            flip(mi);
            flip(curr_size - 1);
        }
    }

    DO_FINISHED;
}

const char* PancakeSort::getDescription() {
    return "The only allowed operation is flipping the array between two points.";
}
