
#include "Program.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Interface.h"
#include "Manager.h"

void Program::draw(sf::RenderWindow& window) {
	Interface::draw(window);
}

void Program::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	Interface::pollEvent(window, theEvent);
}

void Program::update(sf::RenderWindow& window) {
	sf::Time diffTime = deltaClock.restart();

	Interface::update(window, diffTime);
	Manager::update(window, diffTime);
}

int Program::start() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ImGui-Visualizer");
	window.setVerticalSyncEnabled(true);

	Interface::initialize(window);
	Manager::initialize();

	while (window.isOpen()) {
		sf::Event theEvent;
		while (window.pollEvent(theEvent)) {
			if (theEvent.type == sf::Event::Closed) {
				Interface::shutdown();
				window.close();
				return 0;
			}

			Program::pollEvent(window, theEvent);
		}

		Program::update(window);

		window.clear();
		Program::draw(window);
		window.display();
	}

	return 0;
}
