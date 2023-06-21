#include "Randomizer.hpp"

#include <random>

Point Randomizer::randomPoint(RectangleArea&& area)
{
	return Point{ this->randomNumber(area.upLeftX, area.downRightX),
				  this->randomNumber(area.upLeftY, area.downRightY) };
}

unsigned int Randomizer::randomNumber(unsigned int& left, unsigned int& right)
{
	// A uniformly-distributed integer random number generator that produces non-deterministic random numbers
	std::random_device device;

	// A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
	std::mt19937 generator(device());

	// Produces random integer values i, uniformly distributed on the closed interval[a, b],
	// that is, distributed according to the discrete probability function
	// P(i|a,b)=1/(b-a+1).
	// std::uniform_int_distribution satisfies all requirements of RandomNumberDistribution
	std::uniform_int_distribution<int> distribute_number(left, right);

	return distribute_number(generator);
}
