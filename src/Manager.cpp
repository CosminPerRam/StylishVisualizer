
#include "Manager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "BubbleSort.h"

void Manager::initialize() {
	Sorter = new BubbleSort(numberOfElements);
}

void Manager::update(sf::RenderWindow& window, sf::Time diffTime) {
	static sf::Time timeFlow = sf::Time::Zero;
	timeFlow += diffTime;

	unsigned steps = timeFlow.asMilliseconds() / delay;
	timeFlow -= sf::milliseconds(steps * delay);
	
	if (m_isRunning && !m_isPaused) {
		for (unsigned i = 0; i < steps; i++) {
			if (Sorter->step(diffTime))
				m_isRunning = false;
		}
	}
}

bool Manager::isRunning() {
	return m_isRunning;
}

bool Manager::isPaused() {
	return m_isPaused;
}

void Manager::start() {
	if (!m_isPaused)
		Sorter->reset();

	m_isRunning = true;
	m_isPaused = false;
}

void Manager::step() {
	Sorter->step(sf::Time::Zero);
}

void Manager::pause() {
	m_isPaused = true;
}

void Manager::stop() {
	m_isRunning = m_isPaused = false;
}

void Manager::shuffle() {
	Sorter->shuffle(numberOfElements);
}

void Manager::changedAlgorithm() {
	if (lastSelectedAlgorithm != selectedAlgorithm) {
		lastSelectedAlgorithm = selectedAlgorithm;
		std::cout << "Changed to " << algorithmsNames[selectedAlgorithm] << std::endl;
	}
}