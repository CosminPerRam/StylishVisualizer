
#pragma once

#include "SortingAlgorithm.h"

class RadixSortLSD : public SortingAlgorithm
{
private:
	void sorter();

public:
	RadixSortLSD(unsigned count);
};
