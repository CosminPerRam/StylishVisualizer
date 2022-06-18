
#pragma once

#include "SortingAlgorithm.h"

class HeapSort : public SortingAlgorithm
{
private:
	void heapify(int n, int i);

	void sorter();
};
