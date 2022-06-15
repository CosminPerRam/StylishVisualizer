
#pragma once

#include "Utilities.h"

namespace Settings
{
	inline static const int SHUFFLE_MAX_VALUE = 8192;
	inline static const int SHUFFLE_MAX_COUNT = 4096;

	inline extern int SHUFFLE_CURRENT_COUNT = 128;

	inline static const float CURSOR_LINE_MIN_WIDTH = 0.25f;
	inline static const float CURSOR_LINE_MAX_WIDTH = 8.f;
	static float calculateCursorLineWidth() {
		return Utilities::Math::map(static_cast<float>(SHUFFLE_CURRENT_COUNT), 0, SHUFFLE_MAX_COUNT, CURSOR_LINE_MIN_WIDTH, CURSOR_LINE_MAX_WIDTH);
	}
	inline extern float CURSOR_LINE_WIDTH = calculateCursorLineWidth();

	inline static const float AUDIO_MIN_FREQUENCY = 200.f;
	inline static const float AUDIO_MAX_FREQUENCY = 400.f;
	inline static const float AUDIO_MIN_AMP = 0.5f;
	inline static const float AUDIO_MAX_AMP = 1.5f;
	inline static const float AUDIO_MIN_PITCH = 2.f;
	inline static const float AUDIO_MAX_PITCH = 4.f;
	
	inline static const int PAUSE_SLEEPms = 10;
}