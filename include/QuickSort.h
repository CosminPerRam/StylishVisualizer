
#pragma once

#include "SortingAlgorithm.h"

class QuickSort : public SortingAlgorithm
{
private:
	int h = 0, l = 0, j = 0, n = 0, top = 0;
	std::vector<float> stack;

public:
	QuickSort(unsigned count);

	void reset();
	bool step();
};
