#ifndef USE_TIMER
#define USE_TIMER
#include "GameClock.h"
#include <chrono>
class Timer
{
public:
	void Start();
	void Stop();
	void Reset();
	long long GetTimeElapsedms();
	Timer();
	~Timer();
private:
	GameClock* clock;
	std::chrono::high_resolution_clock::time_point start_tp;
	bool running;
};

#endif // !USE_TIMER

