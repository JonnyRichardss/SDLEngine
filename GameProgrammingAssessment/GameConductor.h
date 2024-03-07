#ifndef USE_CONDUCTOR
#define USE_CONDUCTOR
#include "GameClock.h"
#include <chrono>
class GameConductor
{
public:
	static GameConductor* GetInstance();
	double GetInputTiming(std::chrono::high_resolution_clock::time_point INPUT_TP);
private:

	GameConductor();
	~GameConductor();
	std::chrono::high_resolution_clock::time_point firstBeat;
	GameClock* clock = GameClock::GetInstance();
	std::chrono::nanoseconds beatLength;
};

#endif // !USE_CONDUCTOR

