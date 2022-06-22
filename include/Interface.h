
#pragma once

#include "imgui-SFML.h"

class Interface
{
private:
	struct Custom
	{
		static void HelpMarker(const char* firstLine, const char* secondLine = nullptr);
	};

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time diffTime);
};