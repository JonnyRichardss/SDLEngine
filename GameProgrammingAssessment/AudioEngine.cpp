#include "AudioEngine.h"
#include "SDL_mixer.h"
static AudioEngine* _instance;
AudioEngine* AudioEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new AudioEngine();
    return _instance;
}
AudioEngine::AudioEngine()
{
    logging = GameLogging::GetInstance();
    MIX_InitFlags flags = MIX_INIT_MP3;
    if (Mix_Init(flags) != flags) {
        if (AUDIO_FAILURE_FATAL) {
            logging->Log("Failed to init audio - exiting!");
            ENGINE_QUIT_FLAG = true;
        }
        else {
            logging->Log("Failed to init audio - continuing!");
        }
    }

}
AudioEngine::~AudioEngine()
{

}
