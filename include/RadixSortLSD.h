
#pragma once

#include "SortingAlgorithm.h"

class RadixSortLSD : public SortingAlgorithm
{
private:
	void sorter();

public:
	const char* getDescription();
};
