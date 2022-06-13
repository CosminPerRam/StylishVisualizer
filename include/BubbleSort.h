
#pragma once

#include "SortingAlgorithm.h"

class BubbleSort : public SortingAlgorithm
{
private:
	int i = 0, j = 0, n = 0;

public:
	BubbleSort(unsigned count);

	void reset();
	bool step();
	void shuffle(unsigned count);
};
