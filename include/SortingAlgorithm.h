
#pragma once

#include <vector>
#include <thread>
#include <atomic>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "SortingStatistics.h"

#define DO_CHECKEXIT if (m_exit) \
						return;
#define DO_CHECKSTEP bool goContinue = false; \
					while (!goContinue) { \
						DO_CHECKEXIT; \
						stepState state = this->checkStep(); \
						if (state == stepState::NONE || state == stepState::STEP) \
							goContinue = true; \
					}
#define DO_PROGRESSIVE_CHECKSTEP ++stats.steps; DO_CHECKSTEP;
#define DO_STARTED this->reset();
#define DO_FINISHED if(!m_exit) { this->doFinisherLoop(); m_isFinished = true; }
#define DO_PUT_CURSOR_AT(position) this->putCursorAt(position);
#define DO_PUT_CURSOR_AT_WITH_BACKWARDS(position) this->putCursorAt(position, -1);
#define DO_PUT_CURSOR_AT_WITH_FORWARDS(position) this->putCursorAt(position, +1);

class SortingAlgorithm
{
protected:
	SortingStatistics stats;

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
	const SortingStatistics& getStatistics();
	virtual const char* getDescription() = 0;
};
