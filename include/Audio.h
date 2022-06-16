
#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Audio
{
private:
	static sf::Sound& sound();
	static sf::SoundBuffer& buffer();

	inline static std::vector<sf::Int16> samples = std::vector<sf::Int16>(44100, 0);
	static short SineWave(double time, double freq, double amp);

public:
	inline static bool enabled = true;
	inline static float volume = 30;

	static void initialize();

	static void volumeChanged();
	static void play(unsigned position);
};
