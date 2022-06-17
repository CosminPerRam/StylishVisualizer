
#include "Manager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AllSorts.h"

void Manager::initialize() {
	Sorter = new BubbleSort();
	Sorter->shuffle();
}

void Manager::update(sf::RenderWindow& window, sf::Time diffTime) {
	bool sorterFinished = Sorter->isFinished();
	if(sorterFinished)
		m_isRunning = m_isPaused = false;

	if (m_isRunning && !m_isPaused)
		visualTime += visualClock.restart();
}

bool Manager::isRunning() {
	return m_isRunning;
}

bool Manager::isPaused() {
	return m_isPaused;
}

void Manager::start() {
	if (!m_isPaused) {
		visualTime = sf::Time::Zero;
		Sorter->start();
	}
	else
		Sorter->resume();

	m_isRunning = true;
	m_isPaused = false;

	visualClock.restart();
}

void Manager::step() {
	visualClock.restart();
	Sorter->doStep();
	visualTime += visualClock.restart();
}

void Manager::pause() {
	visualTime += visualClock.restart();
	Sorter->pause();
	m_isPaused = true;
}

void Manager::stop() {
	visualTime += visualClock.restart();
	m_isRunning = m_isPaused = false;
	Sorter->stop();
}

void Manager::shuffle() {
	Sorter->shuffle();
}

void Manager::changedAlgorithm() {
	if (lastSelectedAlgorithm == selectedAlgorithm)
		return;

	Manager::stop();
	delete Sorter;

	switch (selectedAlgorithm) {
	case 0:
		Sorter = new BubbleSort();
		break;
	case 1:
		Sorter = new QuickSort();
		break;
	case 2:
		Sorter = new ShellSort();
		break;
	case 3:
		Sorter = new MergeSort();
		break;
	case 4:
		Sorter = new RadixSortLSD();
		break;
	case 5:
		Sorter = new RadixSortMSD();
		break;
	case 6:
		Sorter = new CocktailSort();
		break;
	default:
		break;
	}

	lastSelectedAlgorithm = selectedAlgorithm;
}