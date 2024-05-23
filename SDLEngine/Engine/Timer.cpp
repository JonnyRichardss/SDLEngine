#include "Timer.h"

void Timer::Start()
{
	if (running)
		return;
	else {
		running = true;
		start_tp = clock->GetTimePoint();
	}
}

void Timer::Stop()
{
	running = false;
}

void Timer::Reset()
{
	start_tp = clock->GetTimePoint();
}

std::chrono::nanoseconds Timer::GetTimeElapsed()
{
	if (running)
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock->GetTimePoint() - start_tp);
	else
		return 0ns;
}

Timer::Timer()
{
	clock = GameClock::GetInstance();
	running = false;
}

Timer::~Timer()
{
}
