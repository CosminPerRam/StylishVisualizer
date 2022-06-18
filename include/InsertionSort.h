
#pragma once

#include "SortingAlgorithm.h"

class InsertionSort : public SortingAlgorithm
{
private:
	void sorter();

public:
	const char* getDescription();
};
