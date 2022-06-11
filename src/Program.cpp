
#include "Program.h"

#include "Interface.h"
#include <SFML/Graphics/RenderWindow.hpp>

void Program::draw(sf::RenderWindow& window) {
	Interface::draw(window);
}

void Program::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	Interface::pollEvent(window, theEvent);
}

void Program::update(sf::RenderWindow& window) {
	sf::Time diffTime = deltaClock.restart();

	Interface::update(window, diffTime);
}

int Program::start() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ImGui-Visualizer", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Interface::initialize(window);

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
