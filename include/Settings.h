
#pragma once

#include "Utilities.h"

struct Settings
{
	inline static const int SHUFFLE_MAX_VALUE = 8192;
	inline static const int SHUFFLE_MAX_COUNT = 4096;

	inline static int SHUFFLE_CURRENT_COUNT = 128;

	inline static const float CURSOR_LINE_MIN_WIDTH = 0.25f;
	inline static const float CURSOR_LINE_MAX_WIDTH = 8.f;
	static float calculateCursorLineWidth() {
		return Utilities::Math::map(static_cast<float>(SHUFFLE_CURRENT_COUNT), 0, SHUFFLE_MAX_COUNT, CURSOR_LINE_MIN_WIDTH, CURSOR_LINE_MAX_WIDTH);
	}
	inline static float CURSOR_LINE_WIDTH = calculateCursorLineWidth();

	inline static float AUDIO_MIN_FREQUENCY = 200.f;
	inline static float AUDIO_MAX_FREQUENCY = 400.f;
	inline static float AUDIO_MIN_AMP = 0.5f;
	inline static float AUDIO_MAX_AMP = 1.f;
	inline static float AUDIO_MIN_PITCH = 2.f;
	inline static float AUDIO_MAX_PITCH = 4.f;
	inline static int AUDIO_WAVE_TYPE = 0;

	inline static bool PLOT_BARS = true;
	inline static bool PLOT_LINES = false;
	inline static bool PLOT_STEMS = false;
	inline static bool PLOT_FILLED_LINES = false;
	inline static bool PLOT_CURSOR_SHOW = true;
	inline static bool PLOT_CURSOR_DOT = false;
	inline static bool PLOT_SHOW_SCALE = true;

	inline static bool PLOT_DO_AFTERCHECK = true;
	inline static bool PLOT_SHUFFLE_ON_ALGO_CHANGE = false;

	inline static const int PAUSE_SLEEPms = 8;
};
