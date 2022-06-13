
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

		void reset() {
			sortTime = sf::Time::Zero;

			comparisons = reads = writes = steps = 0;
		}

		void addComparison() {
			++comparisons;
			++reads;
			++writes;
		}

		void addSwap() {
			reads += 3;
			writes += 3;
		}
	};

protected:
	bool m_isFinished = false;
	statistics stats;

	std::vector<float> numbers;

	sf::Clock theClock;

public:

	virtual void reset() = 0;
	virtual bool step() = 0;
	virtual void shuffle(unsigned count) = 0;

	bool isFinished() { return m_isFinished; }
	const std::vector<float>& getNumbers() { return numbers; }
	const statistics& getStatistics() { return stats; }
};
