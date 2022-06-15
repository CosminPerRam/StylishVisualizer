
#include "Utilities.h"

#include <random>

namespace Utilities::Random {
	int getNumberInBetween(int a, int b) {
		static std::random_device rd; // obtain a random number from hardware
		static std::mt19937 gen(rd()); // seed the generator

		std::uniform_int_distribution<> distr(a, b); // define the range

		return distr(gen);
	}
}

namespace Utilities::Math {
	int pow(int base, int power) {
		if (power == 0)
			return 1;

		return base * pow(base, power - 1);
	}

	float map(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}