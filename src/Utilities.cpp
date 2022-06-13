
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