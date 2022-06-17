
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

	ImPlot::GetStyle().AntiAliasedLines = true;
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;
}

void Interface::shutdown() {
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void Interface::draw(sf::RenderWindow& window) {
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

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

	static bool noDelay = false;
	static float oldDelay = 0.f;

	if (ImGui::Checkbox("No delay", &noDelay)) {
		if (noDelay) {
			oldDelay = Manager::delayMs;
			Manager::delayMs = 0.f;
		}
		else
			Manager::delayMs = oldDelay;
	} ImGui::SameLine();
	Custom::HelpMarker("For those extra-slow algorithms."); ImGui::SameLine();

	ImGui::BeginDisabled(noDelay);
	ImGui::PushItemWidth(128);
	float delay = Manager::delayMs;
	if (ImGui::SliderFloat("Delay", &delay, 1.f, 500.f, "%.2f ms", ImGuiSliderFlags_Logarithmic))
		Manager::delayMs = delay;
	ImGui::PopItemWidth(); 
	ImGui::EndDisabled(); ImGui::SameLine();

	ImGui::BeginDisabled(isRunning);
	if (ImGui::Button("Shuffle", { 64, 0 })) {
		Manager::shuffle();
		Settings::CURSOR_LINE_WIDTH = Settings::calculateCursorLineWidth();
	}
	ImGui::SameLine();
	ImGui::PushItemWidth(128);
	ImGui::SliderInt("##nOfElements", &Settings::SHUFFLE_CURRENT_COUNT, 8, Settings::SHUFFLE_MAX_COUNT, "%d elements", ImGuiSliderFlags_Logarithmic);
	ImGui::PopItemWidth();
	ImGui::EndDisabled(); ImGui::SameLine();

	ImGui::Checkbox("Audio", &Audio::enabled); ImGui::SameLine();
	ImGui::BeginDisabled(!Audio::enabled);
	ImGui::PushItemWidth(128);
	if (ImGui::SliderFloat("Volume", &Audio::volume, 0, 100, "%.f"))
		Audio::volumeChanged();
	ImGui::PopItemWidth(); ImGui::SameLine();

	if(ImGui::Button("SFX", { 48, 0 }))
		ImGui::OpenPopup("AudioOptions");

	if (ImGui::BeginPopup("AudioOptions"))
	{
		static const char* waveNames[] = {"Sine", "Square"};
		ImGui::SliderInt("Wave", &Settings::AUDIO_WAVE_TYPE, 0, 1, waveNames[Settings::AUDIO_WAVE_TYPE]);
		ImGui::Text("Pitch");
		ImGui::SliderFloat("Min##Pitch", &Settings::AUDIO_MIN_PITCH, 0.5f, 8.f);
		ImGui::SliderFloat("Max##Pitch", &Settings::AUDIO_MAX_PITCH, 0.5f, 8.f);
		ImGui::Text("Amp");
		ImGui::SliderFloat("Min##Amp", &Settings::AUDIO_MIN_AMP, 0.4f, 1.6f);
		ImGui::SliderFloat("Max##Amp", &Settings::AUDIO_MAX_AMP, 0.4f, 1.6f);
		ImGui::Text("Frequency");
		ImGui::SliderFloat("Min##Frequency", &Settings::AUDIO_MIN_FREQUENCY, 100.f, 1000.f);
		ImGui::SliderFloat("Max##Frequency", &Settings::AUDIO_MAX_FREQUENCY, 100.f, 1000.f);

		ImGui::EndPopup();
	}
	ImGui::EndDisabled(); ImGui::SameLine();

	if (ImGui::Button("Styling", { 64, 0 }))
		ImGui::OpenPopup("StylingPopup");

	static bool showImGuiStyling = false, showImPlotStyling = false;

	if (ImGui::BeginPopup("StylingPopup"))
	{
		if (ImGui::Button("Plot", { 64, 0 }))
			ImGui::OpenPopup("PlotStyling");

		if (ImGui::BeginPopup("PlotStyling"))
		{
			ImGui::Checkbox("Bars", &Settings::PLOT_BARS);
			ImGui::Checkbox("Lines", &Settings::PLOT_LINES);
			ImGui::BeginDisabled(!Settings::PLOT_LINES);
			ImGui::Checkbox("Filled lines", &Settings::PLOT_FILLED_LINES);
			ImGui::EndDisabled();
			ImGui::Checkbox("Cursor", &Settings::PLOT_CURSOR_SHOW);
			ImGui::BeginDisabled(!Settings::PLOT_CURSOR_SHOW);
			ImGui::Checkbox("Dot cursor", &Settings::PLOT_CURSOR_DOT);
			ImGui::EndDisabled();
			ImGui::EndPopup();
		}

		if (ImGui::Button("ImGui", { 64, 0 }))
			ImGui::OpenPopup("ImGuiStyling");

		if (ImGui::BeginPopup("ImGuiStyling"))
		{
			ImGui::ShowStyleEditor();
			ImGui::EndPopup();
		}

		if (ImGui::Button("ImPlot", { 64, 0 }))
			ImGui::OpenPopup("ImPlotStyling");

		if (ImGui::BeginPopup("ImPlotStyling"))
		{
			ImPlot::ShowStyleEditor();
			ImGui::EndPopup();
		}

		ImGui::EndPopup();
	}
	
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
		Custom::HelpMarker("(An approximation, in actual\nreal time use its faster)");

		ImGui::EndTable();
	}

	ImGui::Separator();

	ImVec2 plotSize = { ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40 };
	if (ImPlot::BeginPlot("##Histogram", plotSize, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
		const std::vector<float>& numbers = Manager::Sorter->getNumbers(); int numbersSize = numbers.size();

		ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoGridLines, ImPlotAxisFlags_NoGridLines);
		ImPlot::SetupAxesLimits(0, numbersSize, 0, Settings::SHUFFLE_MAX_VALUE, ImPlotCond_Always);

		if(Settings::PLOT_BARS)
			ImPlot::PlotBars("##Numbers_bars", &numbers[0], numbersSize);
		if (Settings::PLOT_LINES) {
			ImPlot::PlotLine("##Numbers2", &numbers[0], numbersSize);

			if (Settings::PLOT_FILLED_LINES) {
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				ImPlot::PlotShaded("##Numbers2", &numbers[0], numbersSize);
				ImPlot::PopStyleVar();
			}
		}

		if (Settings::PLOT_CURSOR_SHOW) {
			ImPlot::PushStyleColor(ImPlotCol_Fill, { 255, 0, 0, 255 });
			
			if (Settings::PLOT_CURSOR_DOT) {
				ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
				ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, Settings::CURSOR_LINE_WIDTH);
				ImPlot::PlotLine("##Cursor", &currentData.cursorPosition, &currentData.cursorValue, 1);
				ImPlot::PopStyleVar();
			}
			else
				ImPlot::PlotBars("##Cursor", &currentData.cursorPosition, &currentData.cursorValue, 1, Settings::CURSOR_LINE_WIDTH);

			ImPlot::PopStyleColor();
		}

		ImPlot::EndPlot();
	}

	ImPlot::ShowDemoWindow();

	ImGui::End();

	ImGui::SFML::Render(window);
}

void Interface::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);
}

void Interface::update(sf::RenderWindow& window, sf::Time diffTime) {
	ImGui::SFML::Update(window, diffTime);

	auto& stats = Manager::Sorter->getStatistics();

	static int oldVal = 0, oldPos = 0;
	if (Manager::isRunning() && (oldVal != stats.cursorValue || oldPos != stats.cursorPosition)) {
		oldVal = stats.cursorValue;
		oldPos = stats.cursorPosition;
		Audio::play(oldVal);
	}
}