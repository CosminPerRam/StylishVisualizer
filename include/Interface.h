
#pragma once

#include <vector>

#include "imgui-SFML.h"
#include "implot.h"

#include "SortingStatistics.h"

class Interface
{
private:
	struct Custom
	{
		static void HelpMarker(const char* firstLine, const char* secondLine = nullptr);
		static void ChooseStemMarker(const char* id, int &index, ImPlotMarker &marker);
	};

	//caching/temporary variables
	inline static std::vector<unsigned> downsampledNumbers;
	inline static unsigned downsamplingFactor = 1;
	inline static std::vector<unsigned>* sorterNumbers = nullptr;

	inline static SortingStatistics* sortingStatistics = nullptr;
	inline static unsigned cursorPosition = 0, cursorValue = 0;

	static void changedAntialiasing();
	static void changedAlgorithm();

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time diffTime);
};