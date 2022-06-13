
#pragma once

#include "SortingAlgorithm.h"

class Manager
{
private:
	inline static bool m_isRunning = false;
	inline static bool m_isPaused = false;

	inline static int lastSelectedAlgorithm = 0;

public:
	inline static SortingAlgorithm *Sorter = nullptr;

	inline static const char* algorithmsNames[] = { "Bubble" };
	inline static int selectedAlgorithm = 0;

	inline static int numberOfElements = 128;

	inline static float delay = 0.25f;

	static void initialize();

	static bool isRunning();
	static bool isPaused();

	static void start();
	static void stop();
	static void pause();
	static void shuffle();

	static void changedAlgorithm();
};
