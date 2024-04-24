#ifndef USE_CONDUCTOR
#define USE_CONDUCTOR
#include "GameClock.h"

#include <chrono>
class GameConductor
{
public:
	static GameConductor* GetInstance();
	double GetInputTiming(std::chrono::high_resolution_clock::time_point INPUT_TP);
	void StartMusic();
private:

	GameConductor();
	~GameConductor();
	std::chrono::high_resolution_clock::time_point firstBeat;
	GameClock* clock = GameClock::GetInstance();
	std::chrono::milliseconds beatLength;
	GameLogging* logging;

};

#endif // !USE_CONDUCTOR

