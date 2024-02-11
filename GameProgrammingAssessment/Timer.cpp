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

long long Timer::GetTimeElapsedms()
{
	if (running)
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock->GetTimePoint() - start_tp).count();
	else
		return -1;
}

Timer::Timer()
{
	clock = GameClock::GetInstance();
	running = false;
}

Timer::~Timer()
{
}
