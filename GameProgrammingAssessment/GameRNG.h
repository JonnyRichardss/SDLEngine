#pragma once
#ifndef USE_RNG
#define USE_RNG

class RNG
{
public:
	static int randi(int min, int max);
	static float randf(float min, float max);
	RNG();// DO NOT CALL MANUALLY, USE STATIC FUNCTIONS
	~RNG();
};
#endif // !USE_RNG

