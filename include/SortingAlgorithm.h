
#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

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
		void addAssigment();
		void addSwap();
	};

protected:
	//std::mutex variablesMutex;

	statistics stats;

	std::vector<float> numbers;

	sf::Clock theClock;

	std::thread theThread;
	enum class stepState { NONE, PAUSED, EXITED, STEP };
	std::atomic<bool> m_pause = false, m_exit = false, m_isFinished = false, m_doStep = false;

	virtual void sorter() = 0;

	void reset();
	stepState checkStep();

public:

	void start();
	void stop();
	void pause();
	void resume();
	bool doStep();

	void shuffle(unsigned count);

	bool isFinished();
	const std::vector<float>& getNumbers();
	const statistics& getStatistics();
};
