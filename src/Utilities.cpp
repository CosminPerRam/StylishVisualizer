
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

	std::vector<std::pair<unsigned, unsigned>> multipliedPairs(unsigned n) {
		std::vector<std::pair<unsigned, unsigned>> pairs;

		unsigned rootN = (unsigned)sqrt(n);
		for(unsigned i = 1; i <= rootN; i++) {
			if(n % i != 0)
				continue;

			pairs.push_back({i, n / i});
		}

		return pairs;
	}
}