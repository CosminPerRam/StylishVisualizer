
#include "Settings.h"

void Settings::initialize() {
	Settings::updateCursorLineWidth();
}

void Settings::updateCursorLineWidth() { 
	CURSOR_LINE_WIDTH = Utilities::Math::map(static_cast<float>(SHUFFLE_CURRENT_COUNT), 0, SHUFFLE_MAX_COUNT, CURSOR_LINE_MIN_WIDTH, CURSOR_LINE_MAX_WIDTH);
}

void Settings::updateCursorLineWidthDynamically(unsigned count) {
	CURSOR_LINE_WIDTH = Utilities::Math::map(static_cast<float>(count), 0, SHUFFLE_MAX_COUNT, CURSOR_LINE_MIN_WIDTH, CURSOR_LINE_MAX_WIDTH);
}
