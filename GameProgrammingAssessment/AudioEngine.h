#ifndef USE_AUDIOENGINE
#define USE_AUDIOENGINE
#include "GameLogging.h"
#include "GameClock.h"
#include "Global_Flags.h"
#include "SDL_mixer.h"
class AudioEngine
{
public:
	static AudioEngine* GetInstance();
	void ToggleTrack();
	void StartMusic();
private:
	bool soloPlaying = false;
	AudioEngine();
	~AudioEngine();
	
	void SwitchToTrack(Mix_Music* newTrack, Mix_Music* oldTrack);
	GameLogging* logging;
	Mix_Music* mainTrack;
	Mix_Music* soloTrack;
};
#endif // !USE_AUDIOENGINE


