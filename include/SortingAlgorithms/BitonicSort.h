
#pragma once

#include "SortingAlgorithm.h"

class BitonicSort : public SortingAlgorithm
{
private:
	void bitonicMerge(int low, int cnt, int dir);
	void bitonicSort(int low, int cnt, int dir);

	void sorter();

public:
	const char* getDescription();
};
