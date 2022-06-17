
#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Audio
{
private:
	static sf::Sound& sound();
	static sf::SoundBuffer& buffer();

	inline static sf::Int16 samples[44100];

public:
	inline static bool enabled = true;
	inline static float volume = 30;

	static void initialize();

	static void volumeChanged();
	static void play(unsigned position);
};
