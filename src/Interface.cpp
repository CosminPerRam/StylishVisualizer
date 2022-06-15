
#include "Interface.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include "implot.h"

#include "Manager.h"
#include "Audio.h"
#include "Settings.h"
#include "Utilities.h"

void Interface::Custom::HelpMarker(const char* desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void Interface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
	ImGui::CreateContext();
	ImPlot::CreateContext();
}

void Interface::shutdown() {
	//ImGui::SFML::Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void Interface::draw(sf::RenderWindow& window) {
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("MainWindow", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);

	ImGui::PushItemWidth(128);
	if (ImGui::Combo("Algorithm", &Manager::selectedAlgorithm, Manager::algorithmsNames, IM_ARRAYSIZE(Manager::algorithmsNames)))
		Manager::changedAlgorithm();
	ImGui::PopItemWidth(); ImGui::SameLine();

	bool isRunning = Manager::isRunning();
	bool isPaused = Manager::isPaused();

	if (ImGui::Button(isRunning ? "Stop" : "Start", {48, 0})) {
		if (isRunning)
			Manager::stop();
		else
			Manager::start();
	} ImGui::SameLine();

	ImGui::BeginDisabled(!isRunning);
	if (ImGui::Button(isPaused ? "Resume" : "Pause", {48, 0})) {
		if (isPaused)
			Manager::start();
		else
			Manager::pause();
	}
	ImGui::EndDisabled(); ImGui::SameLine();

	ImGui::BeginDisabled(!(isRunning && isPaused));
	if (ImGui::Button("Step", { 48, 0 }))
		Manager::step();
	ImGui::EndDisabled(); ImGui::SameLine();

	ImGui::PushItemWidth(128);
	float delay = Manager::delayMs;
	if (ImGui::SliderFloat("Delay", &delay, 0.1f, 250.f, "%.2f ms", ImGuiSliderFlags_Logarithmic))
		Manager::delayMs = delay;
	ImGui::PopItemWidth(); ImGui::SameLine();

	ImGui::BeginDisabled(isRunning);
	if (ImGui::Button("Shuffle"))
		Manager::shuffle();
	ImGui::SameLine();
	ImGui::PushItemWidth(128);
	if (ImGui::SliderInt("##nOfElements", &Settings::SHUFFLE_CURRENT_COUNT, 8, Settings::SHUFFLE_MAX_COUNT, "%d elements", ImGuiSliderFlags_Logarithmic))
		Settings::CURSOR_LINE_WIDTH = Settings::calculateCursorLineWidth();
	ImGui::PopItemWidth();
	ImGui::EndDisabled();
	/*
	ImGui::SameLine();

	ImGui::Checkbox("Audio", &Audio::enabled);
	ImGui::SameLine();
	ImGui::BeginDisabled(!Audio::enabled);
	ImGui::PushItemWidth(128);
	ImGui::SliderFloat("Volume", &Audio::volume, 0, 100, "%.f");
	ImGui::PopItemWidth();
	ImGui::EndDisabled();
	*/
	ImGui::Separator();

	const SortingAlgorithm::statistics& currentData = Manager::Sorter->getStatistics();

	if (ImGui::BeginTable("table", 6, ImGuiTableFlags_BordersInnerV)) {
		ImGui::TableNextColumn();
		ImGui::Text("Comparisons: %u", currentData.comparisons);

		ImGui::TableNextColumn();
		ImGui::Text("Reads: %u", currentData.reads);

		ImGui::TableNextColumn();
		ImGui::Text("Writes: %u", currentData.writes);

		ImGui::TableNextColumn();
		ImGui::Text("Steps: %u", currentData.steps);

		ImGui::TableNextColumn();
		ImGui::Text("Visual time: %.2f s", Manager::visualTime.asSeconds());

		ImGui::TableNextColumn();
		ImGui::Text("Real time: %.f ms", currentData.sortTimeMs); ImGui::SameLine();
		Custom::HelpMarker("(An approximation)");

		ImGui::EndTable();
	}

	ImGui::Separator();

	ImVec2 plotSize = { ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40 };
	if (ImPlot::BeginPlot("##Histogram", plotSize, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
		ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoGridLines, ImPlotAxisFlags_NoGridLines);
		ImPlot::SetupAxesLimits(0, Manager::Sorter->getNumbers().size(), 0, Settings::SHUFFLE_MAX_VALUE, ImPlotCond_Always);

		ImPlot::PlotBars("##Numbers", &Manager::Sorter->getNumbers()[0], Manager::Sorter->getNumbers().size());

		ImPlot::PushStyleColor(ImPlotCol_Fill, { 255, 0, 0, 255 });
		ImPlot::PlotBars("##Cursor", &currentData.cursorPosition, &currentData.cursorValue, 1, Settings::CURSOR_LINE_WIDTH);
		ImPlot::PopStyleColor();

		ImPlot::EndPlot();
	}

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