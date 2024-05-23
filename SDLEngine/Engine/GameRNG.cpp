#include "GameRNG.h"
#include <stdlib.h>
#include <time.h>
namespace RNG {
	int randi(int min, int max)
	{
		return (int)randf(min, max);
	}

	float randf(float min, float max)
	{
		float diff = max - min;
		float normalRand = (float)rand() / (float)RAND_MAX;
		return normalRand * diff + min;
	}
	void Seed() {
		srand((unsigned int)time(NULL));
	}
}
