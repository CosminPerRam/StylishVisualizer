
#include "SortingAlgorithm.h"

#include <math.h>

#include <SFML/System/Sleep.hpp>

#include "Utilities.h"
#include "Manager.h"
#include "Settings.h"
#include "Audio.h"

SortingAlgorithm::SortingAlgorithm() {
	if(Settings::PLOT_SHUFFLE_ON_ALGO_CHANGE)
		this->shuffle();
}

void SortingAlgorithm::doFinisherLoop() {
	if (!Settings::PLOT_DO_AFTERCHECK)
		return;

	float finisherSleep = Utilities::Math::map(numbers.size(), 0, Settings::SHUFFLE_MAX_COUNT, 50, 1) * (1 / log(numbers.size()));
	for (unsigned i = 0; i < numbers.size(); i++) {
		this->putCursorAt(i);
		sf::sleep(sf::seconds(finisherSleep / 1000));
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

	sf::sleep(sf::microseconds(Manager::delayMs * 1000));
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
		theThread = std::thread(&SortingAlgorithm::sorter, this);
		theThread.detach();
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

const std::vector<unsigned>& SortingAlgorithm::getNumbers() {
	return numbers; 
}

const SortingStatistics& SortingAlgorithm::getStatistics() {
	return stats; 
}

void SortingAlgorithm::shuffle() {
	this->reset();

	numbers.resize(Settings::SHUFFLE_CURRENT_COUNT);

	for (int i = 0; i < Settings::SHUFFLE_CURRENT_COUNT; i++)
		numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
}
