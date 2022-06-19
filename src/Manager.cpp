
#include "Manager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AllSorts.h"
#include "Audio.h"

void Manager::initialize() {
	Sorter = new CocktailSort();
	Sorter->shuffle();
}

void Manager::update(sf::RenderWindow& window, sf::Time diffTime) {
	bool sorterFinished = Sorter->isFinished();
	if(sorterFinished)
		m_isRunning = m_isPaused = false;

	if (m_isRunning && !m_isPaused)
		visualTime += visualClock.restart();

	if (!sorterFinished) {
		auto& stats = Manager::Sorter->getStatistics();

		static int oldVal = 0, oldPos = 0;
		if (oldVal != stats.cursorValue || oldPos != stats.cursorPosition) {
			oldVal = stats.cursorValue;
			oldPos = stats.cursorPosition;
			Audio::play(oldVal);
		}
	}

	visualClock.restart();
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

	if (selectedAlgorithm == 0)
		Sorter = new BitonicSort();
	else if (selectedAlgorithm == 1)
		Sorter = new BogoSort();
	else if (selectedAlgorithm == 2)
		Sorter = new BubbleSort();
	else if (selectedAlgorithm == 3)
		Sorter = new CocktailSort();
	else if (selectedAlgorithm == 4)
		Sorter = new CombSort();
	else if (selectedAlgorithm == 5)
		Sorter = new GnomeSort();
	else if (selectedAlgorithm == 6)
		Sorter = new HeapSort();
	else if (selectedAlgorithm == 7)
		Sorter = new InsertionSort();
	else if (selectedAlgorithm == 8)
		Sorter = new MergeSort();
	else if (selectedAlgorithm == 9)
		Sorter = new QuickSort();
	else if (selectedAlgorithm == 10)
		Sorter = new RadixSortLSD();
	else if (selectedAlgorithm == 11)
		Sorter = new RadixSortMSD();
	else if (selectedAlgorithm == 12)
		Sorter = new SelectionSort();
	else if (selectedAlgorithm == 13)
		Sorter = new ShellSort();
	else if (selectedAlgorithm == 14)
		Sorter = new StalinSort();

	lastSelectedAlgorithm = selectedAlgorithm;
}