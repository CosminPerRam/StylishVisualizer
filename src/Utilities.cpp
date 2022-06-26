
#include "Utilities.h"

#include <random>
#include <numeric>

#include "Settings.h"

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

	void downsample(const std::vector<unsigned>& source, std::vector<unsigned>& result, unsigned downsamplingFactor)
	{
		unsigned src_len = unsigned(source.size());
		if (downsamplingFactor >= src_len) { //not enough elements, fill the array with the remaining elements
			result.resize(src_len);
			for (unsigned i = 0; i != src_len; ++i)
				result[i] = source[i];
		}
		else {
			unsigned dest_len = (unsigned)std::ceil(src_len / downsamplingFactor);
			if (downsamplingFactor > dest_len) {
				dest_len = downsamplingFactor;
				downsamplingFactor = (unsigned)std::ceil(src_len / downsamplingFactor);
			}
			result.resize(dest_len);

			for (unsigned j = 0; j < dest_len - 1; j++)
				result[j] = unsigned(std::accumulate(source.begin() + j * downsamplingFactor, source.begin() + (j + 1) * downsamplingFactor, 0u) / downsamplingFactor);
			
			result[dest_len - 1] = unsigned(std::accumulate(source.begin() + (dest_len - 1) * downsamplingFactor, source.end(), 0u) / downsamplingFactor);
			if (result[dest_len - 1] > Settings::SHUFFLE_MAX_VALUE)
				result[dest_len - 1] = Settings::SHUFFLE_MAX_VALUE;
		}
	}
}