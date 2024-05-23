#include "GameConductor.h"

using namespace std::chrono_literals;
static GameConductor* _instance;
GameConductor* GameConductor::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameConductor();
    return _instance;
}
int GameConductor::GetBeat() {
    //dividing 2 doubles so round
    return floor(audio->GetTrackPos() / MS_PER_BEAT);
}
double GameConductor::GetInputTiming() {

    return audio->MSsinceLastBeat();
}
double GameConductor::GetInputTiming(int timestamp) {
    timestamp -= SDLoffset;
    //now timestamp is the number of MS between song start and input
    double modBeatLength = fmod(timestamp, MS_PER_BEAT);
    return modBeatLength;
}
void GameConductor::StartMusic(int ticks)
{
    SDLoffset = ticks;
    prevBeatNo = -1;
}
bool GameConductor::PollBeat()
{
    if (lastPolledFrame == clock->GetFrameCount()) {
        //condition so that only the first poll across the program will execute on each frame
        return prevBeatPoll;
    }
    lastPolledFrame = clock->GetFrameCount();
    bool output = false;
    int ThisBeatNo = GetBeat();
    if (ThisBeatNo > prevBeatNo) {
        output = true;
        prevBeatNo = ThisBeatNo;
    } 
    prevBeatPoll = output;
    return output;
}
GameConductor::GameConductor()
{
    logging = GameLogging::GetInstance();
    audio = AudioEngine::GetInstance();
    clock = GameClock::GetInstance();
    SDLoffset = 0;
    lastPolledFrame = 0;
    prevBeatPoll = false;
    logging->Log("Initialised conductor.");
}
GameConductor::~GameConductor()
{
}
