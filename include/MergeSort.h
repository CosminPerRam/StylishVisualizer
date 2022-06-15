
#pragma once

#include "SortingAlgorithm.h"

class MergeSort : public SortingAlgorithm
{
private:
	void sorter();

	void mergeSort(int l, int r);
	void merge(int l, int m, int r);
};
