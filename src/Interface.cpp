
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

	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;

	static ImVec4 PlotCursorColormap[] = {{0.f, 0.f, 0.f, 0.f}, {0.f, 0.f, 0.f, 1.f}}; //will remove when ImPlot gets ColormapRemove feature
	ImPlot::AddColormap("HeatmapCursorColormap", PlotCursorColormap, 2);
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

			ImGui::Checkbox("Cursor", &Settings::PLOT_CURSOR_SHOW); ImGui::SameLine();
			ImGui::BeginDisabled(!Settings::PLOT_CURSOR_SHOW || Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP);
			ImGui::ColorEdit4("Color##Cursor", &Settings::PLOT_CURSOR_COLOR.x, ImGuiColorEditFlags_NoInputs);
			ImGui::EndDisabled();

			ImGui::Checkbox("Show scale", &Settings::PLOT_SHOW_SCALE);

			static const std::pair<const char*, Settings::PLOT_TYPES> typeNames[] = { {"Bars", Settings::PLOT_TYPES::BARS}, {"Lines", Settings::PLOT_TYPES::LINES}, 
				{"Heatmap", Settings::PLOT_TYPES::HEATMAP} };
			static int typeChoosed = 0;
			ImGui::PushItemWidth(96);
			if (ImGui::SliderInt("Plot type", &typeChoosed, 0, 2, typeNames[typeChoosed].first))
				Settings::PLOT_TYPE = typeNames[typeChoosed].second;
			ImGui::PopItemWidth();

			ImGui::Separator();

			if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
				static const std::pair<const char*, ImPlotColormap> colors[] = { {"Heat", ImPlotColormap_Hot}, {"Cool", ImPlotColormap_Cool}, {"Plasma", ImPlotColormap_Plasma},
					{"Spectral", ImPlotColormap_Spectral}, {"Jet", ImPlotColormap_Jet} };
				static int colorIndex = 0;

				ImGui::PushItemWidth(80);
				if(ImGui::BeginCombo("Colors", colors[colorIndex].first)) {
					for(int i = 0; i < IM_ARRAYSIZE(colors); i++) {
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

				ImGui::Checkbox("One-liner", &Settings::PLOT_HEATMAP_ONELINER);
				ImGui::SameLine(); Custom::HelpMarker("Display the heatmap with a height of 1.");
			}
			else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::BARS) {
				ImGui::PushItemWidth(96);
				static int barsTypeIndex = 0;
				static const std::pair<const char*, Settings::BARS_TYPES> barsTypesNames[] = { {"Bars", Settings::BARS_TYPES::BARS}, {"Stems", Settings::BARS_TYPES::STEMS}, 
					{"Bars + Stems", Settings::BARS_TYPES::BARS_AND_STEMS} };
				if(ImGui::SliderInt("Style##Bars", &barsTypeIndex, 0, 2, barsTypesNames[barsTypeIndex].first))
					Settings::PLOT_BARS_TYPE = barsTypesNames[barsTypeIndex].second;
				ImGui::PopItemWidth();

				if(Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS || Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS_AND_STEMS)
					ImGui::ColorEdit4("Bars color", &Settings::PLOT_BARS_COLOR.x, ImGuiColorEditFlags_NoInputs);
				if(Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::STEMS || Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS_AND_STEMS) {
					ImGui::ColorEdit4("Stems color", &Settings::PLOT_STEMS_COLOR.x, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Stems lines color", &Settings::PLOT_STEMS_LINE_COLOR.x, ImGuiColorEditFlags_NoInputs);
				}
			}
			else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES) {
				ImGui::ColorEdit4("Line color", &Settings::PLOT_LINES_COLOR.x, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Filled lines", &Settings::PLOT_LINES_FILLED);
				ImGui::BeginDisabled(!Settings::PLOT_LINES_FILLED);
				ImGui::ColorEdit4("Filled lines color", &Settings::PLOT_LINES_FILLED_COLOR.x, ImGuiColorEditFlags_NoInputs);
				ImGui::EndDisabled();
			}

			ImGui::Separator();

			if (Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES || Settings::PLOT_TYPE == Settings::PLOT_TYPES::BARS) {
				ImGui::BeginDisabled(!Settings::PLOT_CURSOR_SHOW);
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
						for(int i = 0; i < IM_ARRAYSIZE(markers); i++) {
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
	float plotSizeHeight = ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40;

	ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines;
	if(Settings::PLOT_SHOW_SCALE && Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
		axisFlags += ImPlotAxisFlags_Invert;

		ImPlot::PushColormap(Settings::PLOT_HEATMAP_COLORS);
		ImPlot::ColormapScale("##ColormapScale", 0, Settings::SHUFFLE_MAX_VALUE, {0, plotSizeHeight});
		ImPlot::PopColormap();
		ImGui::SameLine();
	}

	if (ImPlot::BeginPlot("##MainPlot", {-1, plotSizeHeight}, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
		static std::pair<unsigned, unsigned> gridSize;

		if (!Settings::PLOT_SHOW_SCALE || Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP)
			axisFlags += ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;
			
		ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock);
		ImPlot::SetupAxis(ImAxis_X1, NULL, axisFlags);
		ImPlot::SetupAxis(ImAxis_Y1, NULL, axisFlags);

		if (Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES || Settings::PLOT_TYPE == Settings::PLOT_TYPES::BARS)
			ImPlot::SetupAxesLimits(-0.5, numbersSize - 0.5, 0, Settings::SHUFFLE_MAX_VALUE, ImPlotCond_Always);

		if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
			ImPlot::SetupAxesLimits(0, 1, 0, 1, ImPlotCond_Always);

			gridSize = Settings::PLOT_HEATMAP_ONELINER ? std::make_pair(1u, numbersSize) : Utilities::Math::multipliedPairs(numbersSize).back();

			ImPlot::PushColormap(Settings::PLOT_HEATMAP_COLORS);
			ImPlot::PlotHeatmap("##NumbersHeatmap", &numbers[0], gridSize.first, gridSize.second, 0, Settings::SHUFFLE_MAX_VALUE, NULL);
			ImPlot::PopColormap();
		}
		else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::BARS) {
			if(Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS || Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS_AND_STEMS) {
				ImPlot::PushStyleColor(ImPlotCol_Fill, Settings::PLOT_BARS_COLOR);
				ImPlot::PlotBars("##NumbersBars", &numbers[0], numbersSize);
				ImPlot::PopStyleColor();
			}
			if(Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::STEMS || Settings::PLOT_BARS_TYPE == Settings::BARS_TYPES::BARS_AND_STEMS) {
				ImPlot::PushStyleColor(ImPlotCol_MarkerFill, Settings::PLOT_STEMS_COLOR);
				ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, Settings::PLOT_STEMS_COLOR);
				ImPlot::PushStyleColor(ImPlotCol_Line, Settings::PLOT_STEMS_LINE_COLOR);
				ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Circle);
				ImPlot::PlotStems("##NumbersStems", &numbers[0], numbersSize);
				ImPlot::PopStyleVar(); ImPlot::PopStyleColor(); ImPlot::PopStyleColor(); ImPlot::PopStyleColor();
			}
		}
		else if(Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES) {
			ImPlot::PushStyleColor(ImPlotCol_Line, Settings::PLOT_LINES_COLOR);
			ImPlot::PlotLine("##NumbersLines", &numbers[0], numbersSize);
			ImPlot::PopStyleColor();

			if (Settings::PLOT_LINES_FILLED) {
				ImPlot::PushStyleColor(ImPlotCol_Fill, Settings::PLOT_LINES_FILLED_COLOR);
				ImPlot::PlotShaded("##NumbersLinesFilled", &numbers[0], numbersSize);
				ImPlot::PopStyleColor();
			}
		}

		if(Settings::PLOT_CURSOR_SHOW) {
			unsigned cursorPos = currentData.cursorPosition, cursorVal = currentData.cursorValue;

			if (Settings::PLOT_TYPE == Settings::PLOT_TYPES::LINES || Settings::PLOT_TYPE == Settings::PLOT_TYPES::BARS) {
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
					ImPlot::PopStyleVar(); ImPlot::PopStyleColor(); ImPlot::PopStyleColor();
				}
			}
			else if (Settings::PLOT_TYPE == Settings::PLOT_TYPES::HEATMAP) {
				static unsigned oldNumbersSize = numbersSize;
				static std::vector<unsigned> cursorMap(numbersSize, 0);

				if (cursorPos < numbersSize) { //when not animating
					if (numbersSize != oldNumbersSize) {
						cursorMap.resize(numbersSize, 0);
						oldNumbersSize = numbersSize;
					}

					cursorMap[cursorPos] = 1;

					ImPlot::PushColormap("HeatmapCursorColormap");
					ImPlot::PlotHeatmap("##CursorHeatmap", &cursorMap[0], gridSize.first, gridSize.second, 0, 1, NULL);
					ImPlot::PopColormap();

					cursorMap[cursorPos] = 0;
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
