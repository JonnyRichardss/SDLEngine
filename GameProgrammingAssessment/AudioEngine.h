#ifndef USE_AUDIOENGINE
#define USE_AUDIOENGINE
#include "GameLogging.h"
#include "GameClock.h"
#include "Global_Flags.h"
#include "SDL_mixer.h"
#include "SDL.h"

class AudioEngine
{
public:
	static AudioEngine* GetInstance();
	void ToggleTrack();
	void StartMusic();
	double GetTrackPos();
	double MSsinceLastBeat();
	void PlaySound(int index);
private:
	bool soloPlaying = false;
	AudioEngine();
	~AudioEngine();
	
	void SwitchToTrack(Mix_Music* newTrack, Mix_Music* oldTrack);

	std::vector<Mix_Chunk*> allSounds;
	void LoadAllSounds();
	void FreeAll();
	GameLogging* logging;
	Mix_Music* mainTrack;
	Mix_Music* soloTrack;
};
#endif // !USE_AUDIOENGINE


