#ifndef USE_TIMER
#define USE_TIMER
#include "GameClock.h"
#include <chrono>
class Timer
{
public:
	/*
	Starts the timer at the current time
	*/
	void Start();
	/*
	Stops the timer
	*/
	void Stop();
	/*
	Resets the timer to the current time
	*/
	void Reset();
	/*
	Returns a std::chrono::duration of how long has elapsed since Start() or Reset() were called
	Can be compared to std::chrono_literals
	https://en.cppreference.com/w/cpp/symbol_index/chrono_literals
	*/
	std::chrono::nanoseconds GetTimeElapsed();
	Timer();
	~Timer();
private:
	GameClock* clock;
	std::chrono::high_resolution_clock::time_point start_tp;
	bool running;
};

#endif // !USE_TIMER

