
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

void Audio::play(unsigned value) {
	if (!enabled)
		return;

	samples.clear();

	float freq = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_COUNT, Settings::AUDIO_MIN_FREQUENCY, Settings::AUDIO_MAX_FREQUENCY);
	float amp = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_AMP, Settings::AUDIO_MAX_AMP);
	for (int i = 0; i < 44100; i++)
		samples.emplace_back(Audio::SineWave(i, freq, amp));

	sound().stop();
	buffer().loadFromSamples(&samples[0], samples.size(), 1, 44100);
	sound().setBuffer(buffer());
	float pitch = Utilities::Math::map(static_cast<float>(value), 0, Settings::SHUFFLE_MAX_VALUE, Settings::AUDIO_MIN_PITCH, Settings::AUDIO_MAX_PITCH);
	sound().setPitch(pitch);
	sound().setVolume(volume);
	sound().play();
}
