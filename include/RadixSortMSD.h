
#pragma once

#include "SortingAlgorithm.h"

class RadixSortMSD : public SortingAlgorithm
{
private:
	void sorter();

	void MSDRadixSort(std::vector<unsigned>& tabAux, int low, int high, int digit);
};
