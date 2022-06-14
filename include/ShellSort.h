
#pragma once

#include "SortingAlgorithm.h"

class ShellSort : public SortingAlgorithm
{
private:
	int i = 0, j = 0, gap = 0, n = 0;

public:
	ShellSort(unsigned count);

	void reset();
	bool step();
};
