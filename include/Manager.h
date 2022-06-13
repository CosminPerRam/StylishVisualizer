
#pragma once

#include "SortingAlgorithm.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Manager
{
private:
	inline static bool m_isRunning = false, m_isPaused = false;

	inline static int lastSelectedAlgorithm = 0;

	inline static sf::Clock visualClock;
	
public:
	inline static SortingAlgorithm *Sorter = nullptr;

	inline static const char* algorithmsNames[] = { "BubbleSort" };
	inline static int selectedAlgorithm = 0;

	inline static int numberOfElements = 128;

	inline static float delay = 0.25f;

	inline static sf::Time visualTime;

	static void initialize();

	static void update(sf::RenderWindow& window, sf::Time diffTime);

	static bool isRunning();
	static bool isPaused();

	static void start();
	static void step();
	static void stop();
	static void pause();
	static void shuffle();

	static void changedAlgorithm();
};
