
#pragma once

#include "SortingAlgorithm.h"

class PancakeSort : public SortingAlgorithm
{
private:
    void flip(unsigned i);

	void sorter();

public:
	const char* getDescription();
};
