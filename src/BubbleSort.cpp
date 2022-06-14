
#include "BubbleSort.h"

BubbleSort::BubbleSort(unsigned count) {
	shuffle(count);
	reset();
}

void BubbleSort::reset() {
	i = j = 0;
	n = numbers.size();

	stats.reset();
}

bool BubbleSort::step() {
	theClock.restart();
	for (; i < n - 1; i++) {
		for (; j < n - i - 1; j++) {
			stats.addComparison();
			if (numbers[j] > numbers[j + 1]) {
				std::swap(numbers[j], numbers[j + 1]);
				stats.sortTime += theClock.restart();
				stats.addSwap();
				stats.steps++;
				return false;
			}
		}

		j = 0;
	}
	
	return true;
}
