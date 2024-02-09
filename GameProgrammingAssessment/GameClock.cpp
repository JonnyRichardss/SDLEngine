#include "GameClock.h"
#include "SDL.h"
GameClock::GameClock() : ENGINE_START_TP(std::chrono::high_resolution_clock::now())
{
	last_frame_tp = ENGINE_START_TP;
	framecounter = 0;
	frametime_ns = 0;
	target_ns = 0;
}

GameClock::~GameClock()
{
}

void GameClock::Tick()
{
	framecounter++;
	EnforceLimit(TimeSinceLastFrame());
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

void GameClock::EnforceLimit(long long current_frametime)
{
	if (target_ns == 0 || target_ns <= current_frametime) 
		return;
	SDL_Delay(((target_ns - current_frametime)/ 1000000));
}

long long GameClock::TimeSinceLastFrame()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - last_frame_tp).count();
}
