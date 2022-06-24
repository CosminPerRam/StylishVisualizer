
#include "SortingAlgorithm.h"

#include <math.h>

#include <SFML/System/Sleep.hpp>

#include "Utilities.h"
#include "Manager.h"
#include "Settings.h"
#include "Audio.h"

void SortingAlgorithm::doFinisherLoop() {
	if (!Settings::PLOT_DO_AFTERCHECK)
		return;

	sf::Time delayUs = sf::microseconds(Settings::PLOT_SINGULAR_LOOP_TIMEus / numbers.size());
	for (unsigned i = 0; i < numbers.size(); i++) {
		this->putCursorAt(i);
		sf::sleep(delayUs);
	}
}

void SortingAlgorithm::putCursorAt(unsigned position, int withOffset) {
	stats.cursorPosition = position;

	if(withOffset)
		stats.cursorValue = numbers[position + withOffset];
	else
		stats.cursorValue = numbers[position];
}

void SortingAlgorithm::reset() {
	stats.reset();
	m_pause = false; m_exit = false; m_isFinished = false; m_doStep = false;
	theClock.restart();
}

SortingAlgorithm::stepState SortingAlgorithm::checkStep() {
	if (m_exit)
		return stepState::EXITED;
	else if (m_doStep)
		m_pause = true;
	else if (m_pause) {
		sf::sleep(sf::milliseconds(Settings::PAUSE_SLEEPms));
		theClock.restart();
		return stepState::PAUSED;
	}
	//else
	stats.sortTimeMs = stats.sortTimeMs + theClock.getElapsedTime().asSeconds() * 1000;

	sf::sleep(sf::microseconds(sf::Int64(Manager::delayMs * 1000)));
	theClock.restart();

	if (m_doStep) {
		m_doStep = false;
		return stepState::STEP;
	}

	return stepState::NONE;
}

void SortingAlgorithm::start() {
	if (m_pause)
		this->resume();
	else {
		this->stop();
		theThread = std::thread(&SortingAlgorithm::sorter, this);
	}
}

void SortingAlgorithm::stop() {
	m_exit = true;
	m_pause = false;

	if (theThread.joinable())
		theThread.join();
}

void SortingAlgorithm::pause() {
	m_pause = true;
	//wait???
}

void SortingAlgorithm::resume() {
	m_pause = false;
	m_exit = false;
	//wait???
}

bool SortingAlgorithm::doStep() {
	m_doStep = true;
	//wait???
	return isFinished();
}

bool SortingAlgorithm::isFinished() { 
	return m_isFinished; 
}

bool SortingAlgorithm::isShuffling() { 
	return m_shuffling; 
}

const std::vector<unsigned>& SortingAlgorithm::getNumbers() {
	return numbers; 
}

const SortingStatistics& SortingAlgorithm::getStatistics() {
	return stats; 
}

void SortingAlgorithm::animatedShuffle() {
	const int oldSize = int(numbers.size());

	sf::Time delayUs = sf::microseconds(Settings::PLOT_SINGULAR_LOOP_TIMEus / Settings::SHUFFLE_CURRENT_COUNT);

	if(oldSize > Settings::SHUFFLE_CURRENT_COUNT) {
		delayUs = sf::microseconds(Settings::PLOT_SINGULAR_LOOP_TIMEus / oldSize);

		for(int i = oldSize; i > Settings::SHUFFLE_CURRENT_COUNT; i--) {
			numbers.pop_back();
			sf::sleep(delayUs);
			DO_SHUFFLE_CHECKEXIT;
		}

		Settings::updateCursorLineWidth();
		for (int i = Settings::SHUFFLE_CURRENT_COUNT; i > 0; i--) {
			numbers[i - 1] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
			putCursorAt(i - 1);
			sf::sleep(delayUs);
			DO_SHUFFLE_CHECKEXIT; DO_SHUFFLE_UPDATE_CURSOR(i - 1);
		}
	}
	else if(oldSize < Settings::SHUFFLE_CURRENT_COUNT) {
		for(int i = 0 ; i < oldSize; i++) {
			numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
			putCursorAt(i);
			sf::sleep(delayUs);
			DO_SHUFFLE_CHECKEXIT; DO_SHUFFLE_UPDATE_CURSOR(i);
		}

		for (int i = oldSize; i < Settings::SHUFFLE_CURRENT_COUNT; i++) {
			numbers.emplace_back(Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE));
			putCursorAt(i);
			sf::sleep(delayUs);
			DO_SHUFFLE_CHECKEXIT; DO_SHUFFLE_UPDATE_CURSOR(i);
		}
	}
	else {
		for (int i = 0; i < Settings::SHUFFLE_CURRENT_COUNT; i++) {
			numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
			putCursorAt(i);
			sf::sleep(delayUs);
			DO_SHUFFLE_CHECKEXIT;
		}
	}

	m_shuffling = false;
}

void SortingAlgorithm::shuffle() {
	this->reset();
	this->stopShuffling();
	m_shuffling = true;

	if(Settings::PLOT_SHUFFLE_ANIMATED)
		theThread = std::thread(&SortingAlgorithm::animatedShuffle, this);
	else {
		numbers.resize(Settings::SHUFFLE_CURRENT_COUNT);

		for (int i = 0; i < Settings::SHUFFLE_CURRENT_COUNT; i++)
			numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);

		m_shuffling = false;
	}
}

void SortingAlgorithm::stopShuffling() {
	m_stopShuffling = true;

	if(theThread.joinable())
		theThread.join();

	m_stopShuffling = false;
	m_shuffling = false;
}