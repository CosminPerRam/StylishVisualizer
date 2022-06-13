
#pragma once

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

//#include "Manager.h"

class SortingAlgorithm
{
protected:
	bool m_isFinished = false;

	std::vector<float> numbers;

	sf::Clock clock;

	struct stats
	{
		sf::Time sortTime;
		unsigned comparisons = 0, arrayReads = 0, arrayWrites = 0;
	} statistics;

public:
	//SortingAlgorithm() { this->shuffle(Manager::numberOfElements); }

	virtual void run() = 0;
	virtual void shuffle(unsigned count) = 0;

	bool isFinished() { return m_isFinished; }
	const std::vector<float>& getNumbers() { return numbers; }
	const stats& getStatistics() { return statistics; }
};
