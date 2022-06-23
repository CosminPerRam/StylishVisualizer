
#pragma once

#include "Utilities.h"

#include "implot.h"

struct Settings
{
	inline static const int SHUFFLE_MAX_VALUE = 32768;
	inline static const int SHUFFLE_MAX_COUNT = 16384;

	inline static int SHUFFLE_CURRENT_COUNT = 128;

	inline static const float CURSOR_LINE_MIN_WIDTH = 0.25f;
	inline static const float CURSOR_LINE_MAX_WIDTH = 8.f;
	inline static float CURSOR_LINE_WIDTH = 0.67f;
	static void updateCursorLineWidth();
	static void updateCursorLineWidthDynamically(unsigned count);

	inline static float AUDIO_MIN_FREQUENCY = 200.f;
	inline static float AUDIO_MAX_FREQUENCY = 400.f;
	inline static float AUDIO_MIN_AMP = 0.5f;
	inline static float AUDIO_MAX_AMP = 1.f;
	inline static float AUDIO_MIN_PITCH = 2.f;
	inline static float AUDIO_MAX_PITCH = 4.f;
	inline static int AUDIO_WAVE_TYPE = 0;

	inline static const float PLOT_MIN_DELAY = IF_PLATFORM_WINDOWS(1.f, 0.01f);
	inline static const float PLOT_MAX_DELAY = 500.f;

	enum class PLOT_TYPES { BARS, LINES, HEATMAP };
	inline static PLOT_TYPES PLOT_TYPE = PLOT_TYPES::BARS;

	inline static bool PLOT_SHOW_SCALE = true;

	inline static ImPlotColormap PLOT_HEATMAP_COLORS = ImPlotColormap_Hot;
	inline static bool PLOT_HEATMAP_ONELINER = false;

	enum class BARS_TYPES { BARS, STEMS, BARS_AND_STEMS };
	inline static BARS_TYPES PLOT_BARS_TYPE = BARS_TYPES::BARS;
	inline static ImVec4 PLOT_BARS_COLOR = {0.2f, 0.41f, 0.69f, 1.f};
	inline static ImVec4 PLOT_STEMS_COLOR = {0.2f, 0.1f, 0.69f, 1.f};
	inline static ImVec4 PLOT_STEMS_LINE_COLOR ={0.4f, 0.1f, 0.69f, 1.f};

	inline static bool PLOT_LINES_FILLED = false;
	inline static ImVec4 PLOT_LINES_COLOR = {0.2f, 0.41f, 0.69f, 1.f};
	inline static ImVec4 PLOT_LINES_FILLED_COLOR = {0.2f, 0.1f, 0.69f, 0.25f};

	inline static bool PLOT_CURSOR_SHOW = true;
	inline static ImVec4 PLOT_CURSOR_COLOR = {1.f, 0.f, 0.f, 1.f};
	inline static bool PLOT_CURSOR_ISBAR = true;
	inline static ImPlotMarker PLOT_CURSOR_MARKER = ImPlotMarker_Circle;

	inline static bool PLOT_DO_AFTERCHECK = true;
	inline static bool PLOT_SHUFFLE_ON_ALGO_CHANGE = true;
	inline static bool PLOT_SHUFFLE_ANIMATED = true;
	inline static const unsigned PLOT_SINGULAR_LOOP_TIMEus = 2000000;

	inline static const int PAUSE_SLEEPms = 8;
};
