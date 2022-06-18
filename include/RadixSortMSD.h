
#pragma once

#include "SortingAlgorithm.h"

class RadixSortMSD : public SortingAlgorithm
{
private:
	std::vector<unsigned> tabAux;
	void MSDRadixSort(int low, int high, int digit);

	void sorter();

public:
	const char* getDescription();
};
