
#pragma once

#include <vector>
#include <thread>
#include <atomic>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#define DO_CHECKSTEP bool goContinue = false; \
					while (!goContinue) { \
						stepState state = this->checkStep(); \
						if (state == stepState::EXITED) \
							return; \
						else if (state != stepState::PAUSED) \
							goContinue = true; \
					}
#define DO_PROGRESSIVE_CHECKSTEP ++stats.steps; DO_CHECKSTEP;
#define DO_STARTED this->reset();
#define DO_FINISHED this->doFinisherLoop(); m_isFinished = true;
#define DO_PUT_CURSOR_AT(position) this->putCursorAt(position);
#define DO_PUT_CURSOR_AT_WITH_BACKWARDS(position) this->putCursorAt(position, -1);
#define DO_PUT_CURSOR_AT_WITH_FORWARDS(position) this->putCursorAt(position, +1);

class SortingAlgorithm
{
public:
	struct statistics
	{
		float sortTimeMs = 0.f;
		unsigned long long comparisons = 0, reads = 0, writes = 0, steps = 0;

		unsigned cursorPosition = 0, cursorValue = 0;

		void reset();

		void addComparison();
		void addAssigment();
		void addSwap();
	};

protected:
	statistics stats;

	inline static std::vector<unsigned> numbers;

	sf::Clock theClock;

	std::thread theThread;
	enum class stepState { NONE, PAUSED, EXITED, STEP };
	std::atomic<bool> m_pause = false, m_exit = false, m_isFinished = false, m_doStep = false;

	virtual void sorter() = 0;

	void doFinisherLoop();
	void putCursorAt(unsigned position, int withOffset = 0);
	void reset();
	stepState checkStep();

public:
	SortingAlgorithm();

	void start();
	void stop();
	void pause();
	void resume();
	bool doStep();

	void shuffle();

	bool isFinished();
	const std::vector<unsigned>& getNumbers();
	const statistics& getStatistics();
	virtual const char* getDescription() = 0;
};
