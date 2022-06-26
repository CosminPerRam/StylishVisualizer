
#pragma once

#include <vector>

#ifdef _WIN32
#define IF_PLATFORM_WINDOWS(x, o) x
#else
#define IF_PLATFORM_WINDOWS(X, o) o
#endif

namespace Utilities
{
	namespace Random
	{
		int getNumberInBetween(int a, int b);
	}

	namespace Math
	{
		int pow(int base, int power);
		float map(float x, float in_min, float in_max, float out_min, float out_max);

		std::vector<std::pair<unsigned, unsigned>> multipliedPairs(unsigned n);

		void downsample(const std::vector<unsigned>& source, std::vector<unsigned>& result, unsigned downsamplingFactor);
	}
}