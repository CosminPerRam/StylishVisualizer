
#include "Manager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "BubbleSort.h"
#include "ShellSort.h"
#include "QuickSort.h"

void Manager::initialize() {
	Sorter = new BubbleSort(numberOfElements);
}

void Manager::update(sf::RenderWindow& window, sf::Time diffTime) {
	static sf::Time timeFlow = sf::Time::Zero;
	timeFlow += diffTime;

	unsigned steps = static_cast<unsigned>(timeFlow.asMilliseconds() / delay);
	timeFlow -= sf::milliseconds(static_cast<sf::Int32>(steps * delay));
	
	if (m_isRunning && !m_isPaused) {
		for (unsigned i = 0; i < steps; i++) {
			if (Sorter->step())
				m_isRunning = false;
		}
	}

	if(m_isRunning && !m_isPaused)
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
		Sorter->reset();
		visualTime = sf::Time::Zero;
	}

	m_isRunning = true;
	m_isPaused = false;

	visualClock.restart();
}

void Manager::step() {
	visualClock.restart();
	Sorter->step();
	visualTime += visualClock.restart();
}

void Manager::pause() {
	visualTime += visualClock.restart();
	m_isPaused = true;
}

void Manager::stop() {
	visualTime += visualClock.restart();
	m_isRunning = m_isPaused = false;
}

void Manager::shuffle() {
	Sorter->shuffle(numberOfElements);
}

void Manager::changedAlgorithm() {
	if (lastSelectedAlgorithm == selectedAlgorithm)
		return;

	delete Sorter;

	switch (selectedAlgorithm) {
	case 0:
		Sorter = new BubbleSort(numberOfElements);
		break;
	case 1:
		Sorter = new ShellSort(numberOfElements);
		break;
	case 2:
		Sorter = new QuickSort(numberOfElements);
		break;
	default:
		break;
	}

	lastSelectedAlgorithm = selectedAlgorithm;
}