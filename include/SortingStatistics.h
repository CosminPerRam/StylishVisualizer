#pragma once

struct SortingStatistics
{
	float sortTimeMs = 0.f;
	unsigned long long comparisons = 0, reads = 0, writes = 0, steps = 0;

	unsigned cursorPosition = 0, cursorValue = 0;

	void reset();

	void addComparisons(const unsigned count = 1u);
	void addAssigments(const unsigned count = 1u);
	void addSwaps(const unsigned count = 1u);

	void addReads(const unsigned count = 1u);
	void addWrites(const unsigned count = 1u);

	void addStep();
};