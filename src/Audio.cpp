
#include "Audio.h"

#include <math.h>

#include "Utilities.h"
#include "Settings.h"

constexpr auto TWOPI = 6.283185307f;

sf::Sound& Audio::sound() {
	static sf::Sound theSound;
	return theSound;
}

sf::SoundBuffer& Audio::buffer() {
	static sf::SoundBuffer theBuffer;
	return theBuffer;
}

void Audio::initialize() {
	sound().setBuffer(buffer());
	volumeChanged();
}

void Audio::volumeChanged() {
	sound().setVolume(volume);
}

short SineWave(unsigned time, float freq, float amplitude) {
	float tpc = 44100.f / freq;
	float cycles = time / tpc;
	float rad = TWOPI * cycles;
	return short(sin(rad) * (32767 * amplitude));
}

short SquareWave(unsigned time, float freq, float amplitude) {
	int tpc = int(44100 / freq); // ticks per cycle
	int cyclepart = time % tpc;
	int halfcycle = tpc / 2;
	if (cyclepart < halfcycle)
		return short(32767 * amplitude);

	return 0;
}

void Audio::play(unsigned value) {
	if (!enabled)
		return;

	float freq = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_COUNT, Settings::AUDIO_MIN_FREQUENCY, Settings::AUDIO_MAX_FREQUENCY);
	float amp = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_AMP, Settings::AUDIO_MAX_AMP);
	float pitch = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_PITCH, Settings::AUDIO_MAX_PITCH);

	for (unsigned i = 0; i < 44100; i++) {
		if(Settings::AUDIO_WAVE_TYPE == 0)
			samples[i] = SineWave(i, freq, amp);
		else
			samples[i] = SquareWave(i, freq, amp);
	}

	sound().stop();
	buffer().loadFromSamples(&samples[0], 44100, 1, 44100);
	sound().setPitch(pitch);
	sound().play();
}
