
#pragma once

#include "SortingAlgorithm.h"

class SelectionSort : public SortingAlgorithm
{
private:
	void sorter();

public:
	const char* getDescription();
};
