
#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Audio
{
private:
	static sf::Sound& sound();
	static sf::SoundBuffer& buffer();

	inline static std::vector<sf::Int16> samples;
	static short SineWave(double time, double freq, double amp);

public:
	inline static bool enabled = true;
	inline static float volume = 100;

	static void play(unsigned position);
};
