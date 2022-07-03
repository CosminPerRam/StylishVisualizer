
#pragma once

#include "SortingAlgorithm.h"

#include <atomic>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Manager
{
private:
	inline static bool m_isRunning = false, m_isPaused = false, m_isShuffling = false;
	inline static int lastSelectedAlgorithm = 3;

	inline static sf::Clock visualClock;
	
public:
	inline static SortingAlgorithm *Sorter = nullptr;

	inline static const char* algorithmsNames[] = { "BitonicSort", "BogoSort", "BubbleSort", "CocktailSort", "CombSort", "GnomeSort", "HeapSort", "InsertionSort", 
		"MergeSort", "PancakeSort", "QuickSort", "RadixSort (LSD)", "RadixSort (MSD)", "SelectionSort", "ShellSort", "StalinSort" };
	inline static int selectedAlgorithm = 3;

	inline static std::atomic<float> delayMs = 10.f;

	inline static sf::Time visualTime;

	static void initialize();

	static void update();

	static bool isRunning();
	static bool isPaused();
	static bool isShuffling();

	static void start();
	static void step();
	static void stop();
	static void pause();
	static void shuffle();
	static void stopShuffling();

	static void changedAlgorithm();
};
