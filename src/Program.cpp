
#include "Program.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "Interface.h"
#include "Manager.h"
#include "Audio.h"
#include "Settings.h"

void Program::draw(sf::RenderWindow& window) {
	Interface::draw(window);
}

void Program::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	Interface::pollEvent(window, theEvent);
}

void Program::update(sf::RenderWindow& window) {
	sf::Time diffTime = deltaClock.restart();

	Interface::update(window, diffTime);
	Manager::update();
}

int Program::start() {
	sf::ContextSettings contextSettings;
	contextSettings.antiAliasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1290, 720)), "ImGui-Visualizer", sf::Style::Default, sf::State::Windowed, contextSettings);
	window.setVerticalSyncEnabled(true);

	Manager::initialize();
	Interface::initialize(window);
	Audio::initialize();

	while (window.isOpen()) {
		while (const std::optional mightEvent = window.pollEvent()) {
			if (mightEvent) {
				sf::Event theEvent = mightEvent.value();
				if (theEvent.is<sf::Event::Closed>()) {
					Interface::shutdown();
					window.close();
					return 0;
				}

				Program::pollEvent(window, theEvent);
			}
		}

		Program::update(window);

		window.clear();
		Program::draw(window);
		window.display();
	}

	return 0;
}
