
#include "Program.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Interface.h"
#include "Manager.h"
#include "Audio.h"
#include "Settings.h"

void Program::draw(sf::RenderWindow& window) {
	Interface::draw(window);
}

void Program::pollEvent(sf::Event& theEvent) {
	Interface::pollEvent(theEvent);
}

void Program::update(sf::RenderWindow& window) {
	sf::Time diffTime = deltaClock.restart();

	Interface::update(window, diffTime);
	Manager::update();
}

int Program::start() {
	sf::RenderWindow window(sf::VideoMode(1290, 720), "ImGui-Visualizer");
	window.setVerticalSyncEnabled(true);

	Interface::initialize(window);
	Manager::initialize();
	Audio::initialize();

	while (window.isOpen()) {
		sf::Event theEvent;
		while (window.pollEvent(theEvent)) {
			if (theEvent.type == sf::Event::Closed) {
				Interface::shutdown();
				window.close();
				return 0;
			}

			Program::pollEvent(theEvent);
		}

		Program::update(window);

		window.clear();
		Program::draw(window);
		window.display();
	}

	return 0;
}
