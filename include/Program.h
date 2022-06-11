
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#define VERSION 1
#define VERSION_NAME "1.0.0"

class Program
{
private:
	inline static sf::Clock deltaClock;
	inline static sf::Time lastTime;

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	static void update(sf::RenderWindow& window);

public:
	static int start();
	
};