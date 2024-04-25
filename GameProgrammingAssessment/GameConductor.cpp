#include "GameConductor.h"

using namespace std::chrono_literals;
static GameConductor* _instance;
GameConductor* GameConductor::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameConductor();
    return _instance;
}
double GameConductor::GetInputTiming() {
    double modBeatLength = audio->MSsinceLastBeat();
    if (modBeatLength > MS_PER_BEAT / 2) {
        return MS_PER_BEAT - modBeatLength;
    }
    return modBeatLength;
}
double GameConductor::GetInputTiming(int timestamp) {
    timestamp -= SDLoffset;
    //now timestamp is the number of MS between song start and input
    double modBeatLength = fmod(timestamp, MS_PER_BEAT);
    if (modBeatLength > MS_PER_BEAT / 2) {
        return MS_PER_BEAT - modBeatLength;
    }
    return modBeatLength;
}
void GameConductor::StartMusic(int ticks)
{
    SDLoffset = ticks;
    prevBeatTime = MS_PER_BEAT;
}
bool GameConductor::PollBeat()
{
    bool output = false;
    double ThisBeatTime = audio->MSsinceLastBeat();
    if (ThisBeatTime < prevBeatTime) { 
        output = true;
    }
    prevBeatTime = ThisBeatTime;
    return output;
}
GameConductor::GameConductor()
{
    logging = GameLogging::GetInstance();
    audio = AudioEngine::GetInstance();
    SDLoffset = 0;
    prevBeatTime = MS_PER_BEAT;
    logging->Log("Initialised conductor.");
}
GameConductor::~GameConductor()
{
}
