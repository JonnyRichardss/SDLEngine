#ifndef USE_RNG
#define USE_RNG

namespace RNG
{
	/*
	* Provides a random integer between min and max (both inclusive)
	*/
	int randi(int min, int max);
	/*
	* Provides a random integer between min and max (both inclusive)
	*/
	float randf(float min, float max);
	void Seed();
};
#endif // !USE_RNG

