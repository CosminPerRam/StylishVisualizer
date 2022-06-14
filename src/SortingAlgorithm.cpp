
#include "SortingAlgorithm.h"

#include "Utilities.h"

void SortingAlgorithm::statistics::reset() {
	sortTime = sf::Time::Zero;

	comparisons = reads = writes = steps = 0;
}

void SortingAlgorithm::statistics::addComparison() {
	++comparisons;
	++reads;
	++writes;
}

void SortingAlgorithm::statistics::addSwap() {
	reads += 3;
	writes += 3;
}

bool SortingAlgorithm::isFinished() { 
	return m_isFinished; 
}

const std::vector<float>& SortingAlgorithm::getNumbers() {
	return numbers; 
}

const SortingAlgorithm::statistics& SortingAlgorithm::getStatistics() {
	return stats; 
}

void SortingAlgorithm::shuffle(unsigned count) {
	numbers.resize(count);

	for (unsigned i = 0; i < count; i++)
		numbers[i] = static_cast<float>(Utilities::Random::getNumberInBetween(0, 4096));

	reset();
}