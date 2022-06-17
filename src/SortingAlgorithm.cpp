
#include "SortingAlgorithm.h"

#include <SFML/System/Sleep.hpp>

#include "Utilities.h"
#include "Manager.h"
#include "Settings.h"
#include "Audio.h"

void SortingAlgorithm::statistics::reset() {
	sortTimeMs = 0.f;
	comparisons = 0; reads = 0; writes = 0; steps = 0;

	cursorPosition = 0; cursorValue = 0;
}

void SortingAlgorithm::statistics::addComparison() {
	++comparisons;
	reads += 2;
}

void SortingAlgorithm::statistics::addAssigment() {
	++reads;
	++writes;
}

void SortingAlgorithm::statistics::addSwap() {
	reads += 3;
	writes += 3;
}

SortingAlgorithm::SortingAlgorithm() {
	this->shuffle();
}

void SortingAlgorithm::doFinisherLoop() {
	float finisherSleep = Utilities::Math::map(numbers.size(), 0, Settings::SHUFFLE_MAX_COUNT, 50, 1) * (1 / log(numbers.size()));
	for (unsigned i = 0; i < numbers.size(); i++) {
		this->putCursorAt(i);
		sf::sleep(sf::seconds(finisherSleep / 1000));
	}
}

void SortingAlgorithm::putCursorAt(unsigned position, bool withOneBackwards) {
	stats.cursorPosition = position;

	if(withOneBackwards)
		stats.cursorValue = numbers[position - 1];
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
	else if (m_doStep) {
		m_pause = true;
		m_doStep = false;
		sf::sleep(sf::microseconds(Manager::delayMs * 1000));
		return stepState::STEP;
	}
	else if (m_pause) {
		sf::sleep(sf::milliseconds(Settings::PAUSE_SLEEPms));
		theClock.restart();
		return stepState::PAUSED;
	}

	//else
	stats.sortTimeMs += theClock.getElapsedTime().asSeconds() * 1000;

	sf::sleep(sf::microseconds(Manager::delayMs * 1000));
	theClock.restart();

	return stepState::NONE;
}

void SortingAlgorithm::start() {
	this->stop();
	theThread = std::thread(&SortingAlgorithm::sorter, this);
}

void SortingAlgorithm::stop() {
	m_exit = true;

	if(theThread.joinable())
		theThread.join();
}

void SortingAlgorithm::pause() {
	m_pause = true;
	//wait???
}

void SortingAlgorithm::resume() {
	m_pause = false;
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

const SortingAlgorithm::statistics& SortingAlgorithm::getStatistics() {
	return stats; 
}

void SortingAlgorithm::shuffle() {
	this->reset();

	numbers.resize(Settings::SHUFFLE_CURRENT_COUNT);

	for (int i = 0; i < Settings::SHUFFLE_CURRENT_COUNT; i++)
		numbers[i] = Utilities::Random::getNumberInBetween(0, Settings::SHUFFLE_MAX_VALUE);
}
