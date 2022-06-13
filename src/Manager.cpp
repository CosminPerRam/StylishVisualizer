
#include "Manager.h"

#include "BubbleSort.h"

#include <iostream>

void Manager::initialize() {
	Sorter = new BubbleSort();
}

bool Manager::isRunning() {
	return m_isRunning;
}

bool Manager::isPaused() {
	return m_isPaused;
}

void Manager::start() {
	std::cout << "Start!" << std::endl;
	m_isRunning = true;
	m_isPaused = false;
}

void Manager::pause() {
	std::cout << "Pause!" << std::endl;
	m_isPaused = true;
}

void Manager::stop() {
	std::cout << "Stop!" << std::endl;
	m_isRunning = m_isPaused = false;
}

void Manager::shuffle() {
	std::cout << "Shuffled!" << std::endl;
}

void Manager::changedAlgorithm() {
	std::cout << "Changed to " << algorithmsNames[selectedAlgorithm] << std::endl;
	lastSelectedAlgorithm = selectedAlgorithm;
}