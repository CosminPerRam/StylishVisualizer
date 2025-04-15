
#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Audio
{
private:
	static sf::Sound& sound();
	static sf::SoundBuffer& buffer();

	inline static std::int16_t samples[44100];

public:
	inline static bool enabled = true;
	inline static float volume = 10;

	static void initialize();

	static void volumeChanged();
	static void play(unsigned position);
};
