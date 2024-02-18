#include "GameClock.h"
#include "SDL.h"
#include <thread>
static GameClock* _instance;
GameClock::GameClock() : ENGINE_START_TP(std::chrono::high_resolution_clock::now())
{
	last_frame_tp = ENGINE_START_TP;
	framecounter = 0;
	frametime_ns = 0ns;
	target_ns = 0ns;
	unused_ns = 0ns;
}

GameClock::~GameClock()
{
}


GameClock* GameClock::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new GameClock();
	}
	return _instance;
}

void GameClock::Tick()
{
	framecounter++;
	EnforceLimit();
	frametime_ns = TimeSinceLastFrame();
	last_frame_tp = std::chrono::high_resolution_clock::now();
	
}

std::chrono::nanoseconds GameClock::GetFrametime()
{
	return frametime_ns;
}

long long GameClock::GetFrameCount()
{
	return framecounter;
}

float GameClock::GetBudgetPercent()
{
	if (target_ns == 0ns)
		return 100.0f;
	else
		return roundf((1- ( (float)unused_ns.count() / (float)target_ns.count())) / 100);
}

std::chrono::nanoseconds GameClock::GetRemainingBudget()
{
	return target_ns - TimeSinceLastFrame();
}

std::chrono::high_resolution_clock::time_point GameClock::GetTimePoint()
{
	return last_frame_tp;
}

int GameClock::GetFPS()
{
	if (frametime_ns == 0ns)
		return 1000000000;
	else
		return 1000000000/frametime_ns.count();
}

void GameClock::SetFPSLimit(int newLimit)
{
	if (newLimit == 0) 
		target_ns = 0ns;
	else
		target_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(1s) / newLimit;
}

void GameClock::EnforceLimit()
{
	unused_ns = GetRemainingBudget();
	if (unused_ns <= 0ns)
		return;
	else
		WaitFor(unused_ns);
}

std::chrono::nanoseconds GameClock::TimeSinceLastFrame()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - last_frame_tp);
}

void GameClock::WaitFor(std::chrono::nanoseconds wait_ns)
{
	switch (GF_WAIT_METHOD) {
	case SDL:
		SDL_Delay(std::chrono::duration_cast<std::chrono::milliseconds>(wait_ns).count());
		break;
	case THREAD:
		std::this_thread::sleep_for(wait_ns);
		break;
	case BUSY:
	{
		auto wait_until = std::chrono::high_resolution_clock::now() + wait_ns;
		while (std::chrono::high_resolution_clock::now() < wait_until) {
			//DoThingsWhileWaiting()
			//NOTE TO SELF - DONT ALLOW DISABLING FRAME LIMITER IF YOU IMPLEMENT FUNCTIONALITY IN HERE
		}
		break;
	}
	default:
		throw "Invalid Wait Method";
		//pretty sure the enum prevents invalid values being set but this isnt hurting anyone so
		break;
	}
}
