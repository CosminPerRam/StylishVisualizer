
#include "Manager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "BubbleSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "MergeSort.h"

void Manager::initialize() {
	Sorter = new BubbleSort(numberOfElements);
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
	Sorter->shuffle(numberOfElements);
}

void Manager::changedAlgorithm() {
	if (lastSelectedAlgorithm == selectedAlgorithm)
		return;

	Manager::stop();
	delete Sorter;

	switch (selectedAlgorithm) {
	case 0:
		Sorter = new BubbleSort(numberOfElements);
		break;
	case 1:
		Sorter = new QuickSort(numberOfElements);
		break;
	case 2:
		Sorter = new ShellSort(numberOfElements);
		break;
	case 3:
		Sorter = new MergeSort(numberOfElements);
		break;
	default:
		break;
	}

	lastSelectedAlgorithm = selectedAlgorithm;
}