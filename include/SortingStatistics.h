#pragma once

#include <atomic>

struct SortingStatistics
{
	std::atomic<float> sortTimeMs = 0.f;
	std::atomic<unsigned long long> comparisons = 0, reads = 0, writes = 0;

	std::atomic<unsigned> cursorPosition = 0, cursorValue = 0;

	void reset();

	void addComparisons(const unsigned count = 1u);
	void addAssigments(const unsigned count = 1u);
	void addSwaps(const unsigned count = 1u);

	void addReads(const unsigned count = 1u);
	void addWrites(const unsigned count = 1u);
};
