#include "GameRNG.h"
#include <stdlib.h>
#include <time.h>
static RNG instance;
int RNG::randi(int min, int max)
{
	return rand() % (max+1) + min;
}

float RNG::randf(float min, float max)
{
	float diff = max - min;
	float normalRand = (float)rand() / (float)RAND_MAX;
	return normalRand * diff + min;
}
RNG::RNG() 
{
	srand(time(NULL));
}
RNG::~RNG()
{
}
