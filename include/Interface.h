
#pragma once

#include "imgui-SFML.h"
#include "implot.h"

class Interface
{
private:
	struct Custom
	{
		static void HelpMarker(const char* firstLine, const char* secondLine = nullptr);
		static void ChooseStemMarker(const char* id, int &index, ImPlotMarker &marker);
	};

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time diffTime);
};