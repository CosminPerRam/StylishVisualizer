
#pragma once

#include "SortingAlgorithm.h"

class RadixSortMSD : public SortingAlgorithm
{
private:
	void sorter();

	void MSDRadixSort(std::vector<int>& tabAux, int low, int high, int digit);

public:
	RadixSortMSD(unsigned count);
};
