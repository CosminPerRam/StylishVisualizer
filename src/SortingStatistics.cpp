
#include "SortingStatistics.h"

void SortingStatistics::reset() {
	sortTimeMs = 0.f;
	comparisons = 0; reads = 0; writes = 0; steps = 0;

	cursorPosition = 0; cursorValue = 0;
}

void SortingStatistics::addComparisons(const unsigned count) {
	comparisons += count;
	addReads(count * 2);
}

void SortingStatistics::addAssigments(const unsigned count) {
	addReads(count);
	addWrites(count);
}

void SortingStatistics::addSwaps(const unsigned count) {
	addReads(count * 3);
	addWrites(count * 3);
}

void SortingStatistics::addReads(const unsigned count) {
	reads += count;
}

void SortingStatistics::addWrites(const unsigned count) {
	writes += count;
}

void SortingStatistics::addStep() {
	++steps;
}