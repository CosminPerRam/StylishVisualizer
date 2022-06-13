
#include "BubbleSort.h"

#include "Utilities.h"

#include <iostream>

BubbleSort::BubbleSort(unsigned count) {
	shuffle(count);
}

void BubbleSort::reset() {
	i = j = 0;
	n = numbers.size();
}

bool BubbleSort::step(sf::Time diff) {
	for (; i < n - 1; i++) {
		for (; j < n - i - 1; j++) {
			if (numbers[j] > numbers[j + 1]) {
				std::swap(numbers[j], numbers[j + 1]);
				return false;
			}
		}

		j = 0;
	}
	
	return true;
}

void BubbleSort::shuffle(unsigned count) {
	numbers.resize(count);

	for (unsigned i = 0; i < count; i++)
		numbers[i] = Utilities::Random::getNumberInBetween(0, 8192);
}
