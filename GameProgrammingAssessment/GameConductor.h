#ifndef USE_CONDUCTOR
#define USE_CONDUCTOR
#include "AudioEngine.h"
#include <chrono>
class GameConductor
{
public:
	static GameConductor* GetInstance();
	double GetInputTiming();
	double GetInputTiming(int timestamp);
	void StartMusic(int ticks);
	bool PollBeat();
private:

	GameConductor();
	~GameConductor();
	double prevBeatTime;
	GameLogging* logging;
	AudioEngine* audio;
	GameClock* clock;
	int SDLoffset;
	long long lastPolledFrame;
	bool prevBeatPoll;
};

#endif // !USE_CONDUCTOR

