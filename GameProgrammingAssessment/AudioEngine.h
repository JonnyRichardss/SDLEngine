#ifndef USE_AUDIOENGINE
#define USE_AUDIOENGINE
#include "GameLogging.h"
#include "GameClock.h"
#include "Global_Flags.h"
class AudioEngine
{
public:
	static AudioEngine* GetInstance();
private:
	AudioEngine();
	~AudioEngine();
	GameLogging* logging;
};
#endif // !USE_AUDIOENGINE


