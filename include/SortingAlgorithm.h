
#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "SortingStatistics.h"

#define DO_STARTED this->reset();
#define DO_FINISHED if(!m_exit) { this->doFinisherLoop(); m_isFinished = true; }
#define DO_CHECKEXIT if (m_exit) \
						return;
#define DO_CHECKSTEP do { bool goContinue = false; \
					while (!goContinue) { \
						DO_CHECKEXIT; \
						stepState state = this->checkStep(); \
						if (state == stepState::NONE || state == stepState::STEP) \
							goContinue = true; \
					} } while (false);
#define DO_SHUFFLE_CHECKEXIT if(m_stopShuffling) return;
#define DO_SHUFFLE_UPDATE_CURSOR(i) Settings::updateCursorLineWidthDynamically(i);
#define DO_PUT_CURSOR_AT(position) this->stats.putCursorAt(position);
#define DO_PUT_CURSOR_AT_WITH_BACKWARDS(position) this->stats.putCursorAt(position, -1);
#define DO_PUT_CURSOR_AT_WITH_FORWARDS(position) this->stats.putCursorAt(position, +1);

class SortingAlgorithm
{
protected:
	SortingStatistics stats;

	inline static std::mutex numbersMutex;
	inline static std::vector<unsigned> numbers;

	sf::Clock theClock;

	std::thread theThread;
	enum class stepState { NONE, PAUSED, EXITED, STEP };
	std::atomic<bool> m_pause = false, m_exit = false, m_isFinished = false, m_doStep = false, m_shuffling = false, m_stopShuffling = false;

	virtual void sorter() = 0;

	void animatedShuffle();
	void doFinisherLoop();
	void reset();
	stepState checkStep();

public:
	virtual ~SortingAlgorithm() = default;

	void start();
	void stop();
	void pause();
	void resume();
	bool doStep();

	void shuffle();
	void stopShuffling();

	bool isFinished();
	bool isShuffling();

	std::vector<unsigned>* getNumbers();
	void lockNumbers();
	void unlockNumbers();
	
	SortingStatistics* getStatistics();
	virtual const char* getDescription() = 0;
};
