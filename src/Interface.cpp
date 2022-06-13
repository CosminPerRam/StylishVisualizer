
#include "Interface.h"

#include "imgui-SFML.h"
#include "imgui.h"

#include "Manager.h"
#include "Audio.h"

#include <iostream>

void Interface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void Interface::shutdown() {
	ImGui::SFML::Shutdown();
}

void Interface::draw(sf::RenderWindow& window) {
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("MainWindow", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

	ImGui::PushItemWidth(128);
	if (ImGui::Combo("Algorithm", &Manager::selectedAlgorithm, Manager::algorithmsNames, IM_ARRAYSIZE(Manager::algorithmsNames)))
		Manager::changedAlgorithm();
	ImGui::PopItemWidth();

	ImGui::SameLine();

	bool isRunning = Manager::isRunning();
	bool isPaused = Manager::isPaused();

	if (ImGui::Button(isRunning ? "Stop" : "Start", {48, 0})) {
		if (isRunning)
			Manager::stop();
		else
			Manager::start();
	}

	ImGui::SameLine();

	ImGui::BeginDisabled(!isRunning);
	if (ImGui::Button(isPaused ? "Resume" : "Pause", {48, 0})) {
		if (isPaused)
			Manager::start();
		else
			Manager::pause();
	}
	ImGui::EndDisabled();

	ImGui::SameLine();

	ImGui::PushItemWidth(128);
	ImGui::SliderFloat("Delay", &Manager::delay, 0.01f, 1000.f, "%.02f ms");
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::BeginDisabled(isRunning);
	if (ImGui::Button("Shuffle"))
		Manager::shuffle();
	ImGui::SameLine();
	ImGui::PushItemWidth(128);
	ImGui::SliderInt("##nOfElements", &Manager::numberOfElements, 8, 2048, "%d elements");
	ImGui::PopItemWidth();
	ImGui::EndDisabled();

	ImGui::SameLine();

	ImGui::Checkbox("Audio", &Audio::enabled);
	ImGui::SameLine();
	ImGui::BeginDisabled(!Audio::enabled);
	ImGui::PushItemWidth(128);
	ImGui::SliderFloat("Volume", &Audio::volume, 0, 100, "%.f");
	ImGui::PopItemWidth();
	ImGui::EndDisabled();

	ImGui::Separator();
	ImGui::Text("dsds");
	//ImGui::Text("Statistics: %d comparisons, %d array accesses, %.f visual time (seconds), %.f sort time (milliseconds)", Manager::currentStats.comparisons, Manager::currentStats);

	ImGui::Separator();

	const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
	ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, ImGui::GetWindowContentRegionMax());

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::SFML::Render(window);
}

void Interface::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);
}

void Interface::update(sf::RenderWindow& window, sf::Time diffTime) {
	ImGui::SFML::Update(window, diffTime);
}