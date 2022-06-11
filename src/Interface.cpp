
#include "Interface.h"

#include "imgui-SFML.h"
#include "imgui.h"

void Interface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void Interface::shutdown() {
	ImGui::SFML::Shutdown();
}

void Interface::draw(sf::RenderWindow& window) {
	ImGui::ShowDemoWindow();

	ImGui::SFML::Render(window);
}

void Interface::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);
}

void Interface::update(sf::RenderWindow& window, sf::Time diffTime) {
	ImGui::SFML::Update(window, diffTime);
}