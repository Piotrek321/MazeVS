#include "Globals.h"

int getRandomValue(int to, int from )
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist_width(from, to);
	return uniform_dist_width(e1);
}