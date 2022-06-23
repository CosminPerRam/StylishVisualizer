
#include "Interface.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include "implot.h"

#include "Manager.h"
#include "Audio.h"
#include "Settings.h"
#include "Utilities.h"

void Interface::Custom::HelpMarker(const char* firstLine, const char* secondLine) {
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(firstLine);
		if (secondLine != nullptr)
			ImGui::TextUnformatted(secondLine);
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

	ImGui::PushItemWidth(130);
	if (ImGui::Combo("##Algorithm", &Manager::selectedAlgorithm, Manager::algorithmsNames, IM_ARRAYSIZE(Manager::algorithmsNames)))
		Manager::changedAlgorithm();
	ImGui::PopItemWidth(); ImGui::SameLine();
	Custom::HelpMarker(Manager::Sorter->getDescription()); ImGui::SameLine();

	bool isRunning = Manager::isRunning();
	bool isPaused = Manager::isPaused();
	bool isShuffling = Manager::isShuffling();

	if (ImGui::Button(isRunning || isShuffling ? "Stop" : "Start", {48, 0})) {
		if (isRunning)
			Manager::stop();
		else {
			if (isShuffling)
				Manager::stopShuffling();
			else
				Manager::start();
		}
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
	static float oldDelay = 0.f, delay = Manager::delayMs;

	ImGui::BeginDisabled(noDelay);
	ImGui::Text("Delay"); ImGui::SameLine();
	ImGui::PushItemWidth(128);
	if (ImGui::SliderFloat("##Delay", &delay, Settings::PLOT_MIN_DELAY, Settings::PLOT_MAX_DELAY, "%.2f ms", ImGuiSliderFlags_Logarithmic))
		Manager::delayMs = delay;
	ImGui::PopItemWidth(); 
	ImGui::EndDisabled(); ImGui::SameLine();

	if (ImGui::Checkbox("No delay", &noDelay)) {
		if (noDelay) {
			oldDelay = Manager::delayMs;
			Manager::delayMs = 0.f;
		}
		else
			Manager::delayMs = oldDelay;
	} ImGui::SameLine();
	Custom::HelpMarker("For those extra-slow algorithms."); ImGui::SameLine();

	ImGui::BeginDisabled(isRunning|| isShuffling);
	ImGui::PushItemWidth(128);
	ImGui::SliderInt("##nOfElements", &Settings::SHUFFLE_CURRENT_COUNT, 8, Settings::SHUFFLE_MAX_COUNT, "%d elements", ImGuiSliderFlags_Logarithmic);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (ImGui::Button("Shuffle", { 64, 0 }))
		Manager::shuffle();
	ImGui::EndDisabled(); ImGui::SameLine();

	ImGui::Checkbox("Audio", &Audio::enabled); ImGui::SameLine();
	ImGui::BeginDisabled(!Audio::enabled);
	ImGui::PushItemWidth(128);
	if (ImGui::SliderFloat("Volume", &Audio::volume, 0, 100, "%.f", ImGuiSliderFlags_NoInput))
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

	if (ImGui::BeginPopup("StylingPopup"))
	{
		if (ImGui::Button("Plot", { 64, 0 }))
			ImGui::OpenPopup("PlotStyling");

		if (ImGui::BeginPopup("PlotStyling"))
		{
			static bool idxWarning = sizeof(ImDrawIdx) * 8 == 16 && (ImGui::GetIO().BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset) == false;
			if (idxWarning) {
				ImGui::TextColored({1, 0, 0, 1}, "Warning! (hover over me)");
				if (ImGui::IsItemHovered()) {
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
					ImGui::SetTooltip("ImDrawIdx is 16-bits and ImGuiBackendFlags_RendererHasVtxOffset is false.\nEnabling too many plot types at high element counts might end up in a crash\ndue to producing too many vertices, see the README for more informations.");
					ImGui::PopStyleColor();
				}
			}

			ImGui::Checkbox("Show scale", &Settings::PLOT_SHOW_SCALE);

			static const char* typeNames[] = {"Lines", "Heatmap"};
			static int typeChoosed = 0;
			ImGui::PushItemWidth(96);
			if(ImGui::SliderInt("Type", &typeChoosed, 0, 1, typeNames[typeChoosed])) {
				if(typeChoosed == 0)
					Settings::PLOT_TYPE = Settings::PLOT_TYPES::LINES;
				else if(typeChoosed == 1)
					Settings::PLOT_TYPE = Settings::PLOT_TYPES::HEATMAP;
			}
			ImGui::PopItemWidth();

			ImGui::Separator();

			if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
				static const std::pair<const char*, ImPlotColormap> colors[] = { {"Heat", ImPlotColormap_Hot}, {"Cool", ImPlotColormap_Cool}, {"Plasma", ImPlotColormap_Plasma},
					{"Spectral", ImPlotColormap_Spectral}, {"Jet", ImPlotColormap_Jet} };
				static int colorIndex = 0;

				ImGui::PushItemWidth(80);
				if(ImGui::BeginCombo("Colors", colors[colorIndex].first)) {
					for(unsigned i = 0; i < IM_ARRAYSIZE(colors); i++) {
						const bool is_selected = (colorIndex == i);
						if(ImGui::Selectable(colors[i].first, is_selected)) {
							colorIndex = i;
							Settings::PLOT_HEATMAP_COLORS = colors[i].second;
						}

						if(is_selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::PopItemWidth();
			}
			else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES) {
				ImGui::Checkbox("Bars", &Settings::PLOT_BARS);
				ImGui::Checkbox("Stems", &Settings::PLOT_STEMS);
				ImGui::Checkbox("Lines", &Settings::PLOT_LINES);

				ImGui::BeginDisabled(!Settings::PLOT_LINES);
				ImGui::Checkbox("Filled lines", &Settings::PLOT_FILLED_LINES);
				ImGui::EndDisabled();

				ImGui::Checkbox("Cursor", &Settings::PLOT_CURSOR_SHOW);
				ImGui::BeginDisabled(!Settings::PLOT_CURSOR_SHOW);

				ImGui::ColorEdit4("Cursor color", &Settings::PLOT_CURSOR_COLOR.x, ImGuiColorEditFlags_NoInputs);

				ImGui::PushItemWidth(80);
				static int cursorIsMarker = 0;
				static const char* cursorsNames[] = {"Bar", "Marker"};
				if(ImGui::SliderInt("Cursor style", &cursorIsMarker, 0, 1, cursorsNames[cursorIsMarker]))
					Settings::PLOT_CURSOR_ISBAR = (cursorIsMarker == 0);
				ImGui::PopItemWidth();

				if(!Settings::PLOT_CURSOR_ISBAR) {
					static const std::pair<const char*, ImPlotMarker> markers[] = { {"Circle", ImPlotMarker_Circle}, {"Square", ImPlotMarker_Square}, {"Diamond", ImPlotMarker_Diamond},
						{"Asterisk", ImPlotMarker_Asterisk}, {"Cross", ImPlotMarker_Cross} };
					static int markerIndex = 0;

					ImGui::PushItemWidth(80);
					if(ImGui::BeginCombo("Cursor marker", markers[markerIndex].first)) {
						for(unsigned i = 0; i < IM_ARRAYSIZE(markers); i++) {
							const bool is_selected = (markerIndex == i);
							if(ImGui::Selectable(markers[i].first, is_selected)) {
								markerIndex = i;
								Settings::PLOT_CURSOR_MARKER = markers[i].second;
							}

							if(is_selected)
								ImGui::SetItemDefaultFocus();
						}

						ImGui::EndCombo();
					}
					ImGui::PopItemWidth();
				}

				ImGui::EndDisabled();
			}

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

	ImGui::SameLine();
	if (ImGui::Button("Options", { 64, 0 }))
		ImGui::OpenPopup("OptionsPopup");

	if (ImGui::BeginPopup("OptionsPopup"))
	{
		ImGui::Checkbox("Animated shuffle", &Settings::PLOT_SHUFFLE_ANIMATED);
		ImGui::SameLine(); Custom::HelpMarker("Beeps and boops each time you hit shuffle.", IF_PLATFORM_WINDOWS("Shuffling at over 2000 elements makes the delay not visible.", nullptr));
		ImGui::Checkbox("Shuffle on change", &Settings::PLOT_SHUFFLE_ON_ALGO_CHANGE);
		ImGui::SameLine(); Custom::HelpMarker("Shuffle the numbers when\nchanging the algorithm.");
		ImGui::Checkbox("Reiterate when done", &Settings::PLOT_DO_AFTERCHECK);
		ImGui::SameLine(); Custom::HelpMarker("Iterates the data one more time\nafter the algorithm finishes.");

		ImGui::EndPopup();
	}
	
	ImGui::Separator();

	const SortingStatistics& currentData = Manager::Sorter->getStatistics();

	if (ImGui::BeginTable("table", 6, ImGuiTableFlags_BordersInnerV)) {
		ImGui::TableNextColumn();
		ImGui::Text("Comparisons: %llu", currentData.comparisons.load());

		ImGui::TableNextColumn();
		ImGui::Text("Reads: %llu", currentData.reads.load());

		ImGui::TableNextColumn();
		ImGui::Text("Writes: %llu", currentData.writes.load());

		ImGui::TableNextColumn();
		ImGui::Text("Steps: %llu", currentData.steps.load());

		ImGui::TableNextColumn();
		ImGui::Text("Visual time: %.2f s", Manager::visualTime.asSeconds());

		ImGui::TableNextColumn();
		ImGui::Text("Real time: %.f ms", currentData.sortTimeMs.load()); ImGui::SameLine();
		Custom::HelpMarker("(This is an approximation, in real use its faster)");

		ImGui::EndTable();
	}

	ImGui::Separator();

	const std::vector<unsigned>& numbers = Manager::Sorter->getNumbers(); unsigned numbersSize = unsigned(numbers.size());
	ImVec2 plotSize = { ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40 };
	if (ImPlot::BeginPlot("##MainPlotLines", plotSize, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
		ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines;
		if (!Settings::PLOT_SHOW_SCALE)
			axisFlags += ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;
		ImPlot::SetupAxes(NULL, NULL, axisFlags, axisFlags);

		if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
			ImPlot::SetupAxesLimits(0, 1, 0, 1, ImPlotCond_Always);

			auto gridSize = Utilities::Math::multipliedPairs(numbersSize).back();

			ImPlot::PushColormap(Settings::PLOT_HEATMAP_COLORS);
			ImPlot::PlotHeatmap("##NumbersHeatmap", &numbers[0], gridSize.first, gridSize.second, 0, Settings::SHUFFLE_MAX_VALUE, NULL);
			ImPlot::PopColormap();
		}
		else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES) {
			ImPlot::SetupAxesLimits(-0.5, numbersSize - 0.5, 0, Settings::SHUFFLE_MAX_VALUE, ImPlotCond_Always);

			if(Settings::PLOT_BARS)
				ImPlot::PlotBars("##NumbersBars", &numbers[0], numbersSize);
			if(Settings::PLOT_LINES) {
				ImPlot::PlotLine("##NumbersLines", &numbers[0], numbersSize);

				if (Settings::PLOT_FILLED_LINES) {
					ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
					ImPlot::PlotShaded("##NumbersLinesFilled", &numbers[0], numbersSize);
					ImPlot::PopStyleVar();
				}
			}
			if(Settings::PLOT_STEMS)
				ImPlot::PlotStems("##NumbersStems", &numbers[0], numbersSize);

			if (Settings::PLOT_CURSOR_SHOW) {
				unsigned cursorPos = currentData.cursorPosition, cursorVal = currentData.cursorValue;

				if (Settings::PLOT_CURSOR_ISBAR) {
					ImPlot::PushStyleColor(ImPlotCol_Fill, Settings::PLOT_CURSOR_COLOR);
					ImPlot::PlotBars("##Cursor", &cursorPos, &cursorVal, 1, Settings::CURSOR_LINE_WIDTH);
					ImPlot::PopStyleColor();
				}
				else {
					ImPlot::PushStyleColor(ImPlotCol_MarkerFill, Settings::PLOT_CURSOR_COLOR);
					ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, Settings::PLOT_CURSOR_COLOR);
					ImPlot::SetNextMarkerStyle(Settings::PLOT_CURSOR_MARKER);
					ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, Settings::CURSOR_LINE_WIDTH);
					ImPlot::PlotLine("##Cursor", &cursorPos, &cursorVal, 1);
					ImPlot::PopStyleVar();
					ImPlot::PopStyleColor();
					ImPlot::PopStyleColor();
				}
			}
		}

		ImPlot::EndPlot();
	}

	ImGui::End();

	ImGui::SFML::Render(window);
}

void Interface::pollEvent(sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);
}

void Interface::update(sf::RenderWindow& window, sf::Time diffTime) {
	ImGui::SFML::Update(window, diffTime);
}