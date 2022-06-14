
#pragma once

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class SortingAlgorithm
{
public:
	struct statistics
	{
		sf::Time sortTime;
		unsigned comparisons = 0, reads = 0, writes = 0, steps = 0;

		void reset();

		void addComparison();
		void addSwap();
	};

protected:
	bool m_isFinished = false;
	statistics stats;

	std::vector<float> numbers;

	sf::Clock theClock;

public:

	virtual void reset() = 0;
	virtual bool step() = 0;

	void shuffle(unsigned count);

	bool isFinished();
	const std::vector<float>& getNumbers();
	const statistics& getStatistics();
};
