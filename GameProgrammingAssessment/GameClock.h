#ifndef USE_GAMECLOCK
#define USE_GAMECLOCK
#include <chrono>

class GameClock
{
public:
	static GameClock* GetInstance();
	void Tick();
	long long GetFrametime();
	long long GetFrameCount();
	float GetBudgetPercent();
	std::chrono::high_resolution_clock::time_point GetTimePoint();
	int GetFPS();
	void SetFPSLimit(int fps);
private:
	GameClock();
	~GameClock();
	
	const std::chrono::high_resolution_clock::time_point ENGINE_START_TP;
	std::chrono::high_resolution_clock::time_point last_frame_tp;

	long long frametime_ns;
	long long unused_ns;
	long long framecounter;
	long long target_ns;
	long long GetRemainingBudget();
	void EnforceLimit();
	long long TimeSinceLastFrame();
};
#endif // !USE_GAMECLOCK

