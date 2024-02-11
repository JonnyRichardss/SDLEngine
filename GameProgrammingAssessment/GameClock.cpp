#include "GameClock.h"
#include "SDL.h"

static GameClock* _instance;
GameClock::GameClock() : ENGINE_START_TP(std::chrono::high_resolution_clock::now())
{
	last_frame_tp = ENGINE_START_TP;
	framecounter = 0;
	frametime_ns = 0;
	target_ns = 0;
	unused_ns = 0;
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

long long GameClock::GetFrametime()
{
	return frametime_ns;
}

long long GameClock::GetFrameCount()
{
	return framecounter;
}

float GameClock::GetBudgetPercent()
{
	if (target_ns == 0)
		return 100.0f;
	else
		return roundf((1-((float)unused_ns / (float)target_ns) )* 10000)/100;
}

long long GameClock::GetRemainingBudget()
{
	return target_ns - TimeSinceLastFrame();
}

std::chrono::high_resolution_clock::time_point GameClock::GetTimePoint()
{
	return last_frame_tp;
}

int GameClock::GetFPS()
{
	if (frametime_ns == 0)
		return 1000000000;
	else
		return 1000000000/frametime_ns;
}

void GameClock::SetFPSLimit(int fps)
{
	if (fps == 0) 
		target_ns = 0;
	else
		target_ns = 1000000000 / fps;
}

void GameClock::EnforceLimit()
{
	unused_ns = GetRemainingBudget();
	if (unused_ns <= 0)
		return;
	SDL_Delay((unused_ns / 1000000));
}

long long GameClock::TimeSinceLastFrame()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - last_frame_tp).count();
}
