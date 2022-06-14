
#include "ShellSort.h"

#include <iostream>

ShellSort::ShellSort(unsigned count) {
	shuffle(count);
	reset();
}

void ShellSort::reset() {
	n = numbers.size();
	gap = n / 2;
	i = gap;
	j = i;

	stats.reset();
}

bool ShellSort::step() {
    while(gap > 0)
    {
        while(i < n)
        {
            float temp = numbers[i];
            ++stats.reads;

            while(j >= gap && numbers[j - gap] > temp)
            {
                numbers[j] = numbers[j - gap];
                stats.reads += 2; ++stats.writes; ++stats.steps;
                j -= gap;
                return false;
            }
            numbers[j] = temp;
            ++stats.writes;

            j = i;
            i++;
        }

        gap /= 2;
        i = gap;
    }

	return true;
}
