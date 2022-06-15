
#include "SortingAlgorithm.h"

#include <SFML/System/Sleep.hpp>

#include "Utilities.h"
#include "Manager.h"

#define PAUSE_SLEEP_TIME 10

void SortingAlgorithm::statistics::reset() {
	sortTimeMs = 0.f;
	comparisons = reads = writes = steps = 0;
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
		std::this_thread::sleep_for(std::chrono::milliseconds(Manager::delay));
		return stepState::STEP;
	}
	else if (m_pause) {
		std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_SLEEP_TIME));
		theClock.restart();
		return stepState::PAUSED;
	}

	//else
	stats.sortTimeMs += theClock.getElapsedTime().asSeconds() * 1000;

	sf::sleep(sf::milliseconds(static_cast<sf::Int32>(Manager::delay)));
	theClock.restart();

	return stepState::NONE;
}

void SortingAlgorithm::start() {
	this->stop();
	this->reset();
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

const std::vector<float>& SortingAlgorithm::getNumbers() {
	return numbers; 
}

const SortingAlgorithm::statistics& SortingAlgorithm::getStatistics() {
	return stats; 
}

void SortingAlgorithm::shuffle(unsigned count) {
	stop();

	numbers.resize(count);

	for (unsigned i = 0; i < count; i++)
		numbers[i] = static_cast<float>(Utilities::Random::getNumberInBetween(0, 4096));
}