#ifndef USE_GAMECLOCK
#define USE_GAMECLOCK
#include <chrono>
class GameClock
{
public:
	GameClock();
	~GameClock();
	void Tick();
	long long GetFrametime();
	long long GetFrameCount();
	int GetFPS();
	void SetFPSLimit(int fps);
private:

	const std::chrono::high_resolution_clock::time_point ENGINE_START_TP;
	std::chrono::high_resolution_clock::time_point last_frame_tp;
	long long frametime_ns;
	long long framecounter;
	long long target_ns;
	void EnforceLimit(long long current_frametime);
	long long TimeSinceLastFrame();
};
#endif // !USE_GAMECLOCK

