
#pragma once

#include "SortingAlgorithm.h"

class MergeSort : public SortingAlgorithm
{
private:
	void mergeSort(int l, int r);
	void merge(int l, int m, int r);

	void sorter();

public:
	const char* getDescription();
};
