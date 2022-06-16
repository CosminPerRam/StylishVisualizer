
#include "Audio.h"

#include "Utilities.h"
#include "Settings.h"

#define TWOPI 6.283185307

sf::Sound& Audio::sound() {
	static sf::Sound theSound;
	return theSound;
}

sf::SoundBuffer& Audio::buffer() {
	static sf::SoundBuffer theBuffer;
	return theBuffer;
}

short Audio::SineWave(double time, double freq, double amp) {
	double tpc = 44100 / freq;
	double cycles = time / tpc;
	double rad = TWOPI * cycles;

	short amplitude = 32767 * amp;
	return amplitude * sin(rad);
}

void Audio::initialize() {
	sound().setBuffer(buffer());
	volumeChanged();
}

void Audio::volumeChanged() {
	sound().setVolume(volume);
}

void Audio::play(unsigned value) {
	if (!enabled)
		return;

	float freq = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_COUNT, Settings::AUDIO_MIN_FREQUENCY, Settings::AUDIO_MAX_FREQUENCY);
	float amp = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_AMP, Settings::AUDIO_MAX_AMP);
	float pitch = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_PITCH, Settings::AUDIO_MAX_PITCH);

	for (int i = 0; i < 44100; i++)
		samples[i] = Audio::SineWave(i, freq, amp);

	buffer().loadFromSamples(&samples[0], samples.size(), 1, 44100);
	sound().setPitch(pitch);
	sound().play();
}
