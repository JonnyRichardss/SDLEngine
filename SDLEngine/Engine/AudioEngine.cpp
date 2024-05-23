#include "AudioEngine.h"
#include <string>
//#include "GameConductor.h"  TODO!
#include "GameUtils.h"
static bool AUDIO_FAILURE_FATAL = true; // TODO!
static bool ENGINE_QUIT_FLAG = false; // TODO!
constexpr float MUSIC_VOLUME = 1; // TODO!
constexpr float MASTER_VOLUME = 1;// TODO!
constexpr int MUSIC_START_OFFSET = 0;// TODO!
//TODO! looks like the audio failure case used the non-global quit flag. This whole init wants re-doing properly
//TODO! add way to change volume at runtime - probably set by library consumer again
//engine settings struct seems like a good way to do this - pass when init'ing library

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
    LoadAllSounds();
    Mix_MasterVolume(MASTER_VOLUME);
    Mix_VolumeMusic(MUSIC_VOLUME);
    
    Mix_SetMusicPosition(MUSIC_START_OFFSET);
    logging->Log("Initialised audio engine.");
}
AudioEngine::~AudioEngine()
{
    FreeAll();
}
void AudioEngine::StartMusic() {
    Mix_PlayMusic(mainTrack, 0);
    //GameConductor::GetInstance()->StartMusic(SDL_GetTicks()); TODO!
}
double AudioEngine::GetTrackPos()
{
    Mix_Music* track = soloPlaying ? soloTrack : mainTrack;
    return (Mix_GetMusicPosition(track)*1000);
}
double AudioEngine::MSsinceLastBeat()
{
    return 0;
    //return fmod(GetTrackPos(),MS_PER_BEAT); TODO!
}
void AudioEngine::PlaySound(int index)
{
    if (index >= allSounds.size() || index < 0) {
        logging->Log("Tried to play sound with invalid index!");
        return;
    }
    Mix_PlayChannel(-1, allSounds[index], 0);
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

void AudioEngine::LoadAllSounds()
{
    std::vector<std::string> allPaths;
    if (!ReadFile("Assets/SoundPaths.txt", allPaths)) {
        logging->Log("Failed to load sound locations!");
        return;
    }
    for (std::string filePath : allPaths) {
        Mix_Chunk* sound;
        sound = Mix_LoadWAV(filePath.c_str());
        if (sound == nullptr) {
            logging->Log("Failed to load sound with path: " + filePath);
            continue;
        }
        allSounds.push_back(sound);
    }
}

void AudioEngine::FreeAll()
{
    for (Mix_Chunk* sound : allSounds) {
        Mix_FreeChunk(sound);
    }
    Mix_FreeMusic(mainTrack);
    Mix_FreeMusic(soloTrack);
}
