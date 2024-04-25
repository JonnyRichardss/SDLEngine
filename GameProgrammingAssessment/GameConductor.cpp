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
    if (lastPolledFrame == clock->GetFrameCount()) {
        //condition so that only the first poll across the program will execute on each frame
        return prevBeatPoll;
    }
    lastPolledFrame = clock->GetFrameCount();
    bool output = false;
    double ThisBeatTime = audio->MSsinceLastBeat();
    if (ThisBeatTime < prevBeatTime) { 
        output = true;
    }
    prevBeatTime = ThisBeatTime;
    prevBeatPoll = output;
    return output;
}
GameConductor::GameConductor()
{
    logging = GameLogging::GetInstance();
    audio = AudioEngine::GetInstance();
    clock = GameClock::GetInstance();
    SDLoffset = 0;
    prevBeatTime = MS_PER_BEAT;
    lastPolledFrame = 0;
    prevBeatPoll = false;
    logging->Log("Initialised conductor.");
}
GameConductor::~GameConductor()
{
}
