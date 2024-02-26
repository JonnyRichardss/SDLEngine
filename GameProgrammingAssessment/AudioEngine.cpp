#include "AudioEngine.h"
#include <string>
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
            return;
        }
        else {
            logging->Log("Failed to init audio - continuing!");
            return;
        }
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        if (AUDIO_FAILURE_FATAL) {
            logging->Log("Failed to open audio device - exiting!");
            ENGINE_QUIT_FLAG = true;
            return;
        }
        else {
            logging->Log("Failed to open audio device - continuing!");
            return;
        }
    }
    //un-hardcode these paths thanks
    mainTrack = Mix_LoadMUS("Assets/music_main.mp3");
    if (mainTrack == nullptr) {
        logging->DebugLog(Mix_GetError());
        logging->Log("Failed to load file Assets/music_main.mp3");
    }
    soloTrack = Mix_LoadMUS("Assets/music_solo.mp3");
    if (soloTrack == nullptr) {
        logging->DebugLog(Mix_GetError());
        logging->Log("Failed to load file Assets/music_solo.mp3");
    }
    Mix_MasterVolume(MASTER_VOLUME);
    Mix_VolumeMusic(MUSIC_VOLUME);
    Mix_PlayMusic(mainTrack, 0);
    Mix_SetMusicPosition(MUSIC_START_OFFSET);
    logging->Log("Initialised audio engine.");
}
AudioEngine::~AudioEngine()
{

}
void AudioEngine::ToggleTrack()
{
    SwitchToTrack(soloPlaying ? mainTrack : soloTrack, soloPlaying ? soloTrack: mainTrack);
    soloPlaying = soloPlaying ? false : true;
    std::string logText = "Now playing";
    logText.append(soloPlaying ? " solo " : " main ");
    logText.append("track!");
    logging->Log(logText);
}
void AudioEngine::SwitchToTrack(Mix_Music* newTrack, Mix_Music* oldTrack) {
    double trackPos = Mix_GetMusicPosition(oldTrack);
    Mix_PlayMusic(newTrack, 0);
    Mix_SetMusicPosition(trackPos);
}
