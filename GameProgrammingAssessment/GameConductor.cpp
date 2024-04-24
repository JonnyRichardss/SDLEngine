#include "GameConductor.h"
using namespace std::chrono_literals;
static GameConductor* _instance;
GameConductor* GameConductor::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameConductor();
    return _instance;
}
double GameConductor::GetInputTiming(std::chrono::high_resolution_clock::time_point inputTP)
{
    std::chrono::high_resolution_clock::duration durationSinceStart = inputTP  - firstBeat;
    std::chrono::milliseconds msSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(durationSinceStart);
    std::chrono::milliseconds modBeatLength = msSinceStart % beatLength;

    if (modBeatLength > beatLength / 2) {
        return std::chrono::duration_cast<std::chrono::milliseconds>((beatLength - modBeatLength)).count();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(modBeatLength).count();
}
void GameConductor::StartMusic()
{
    firstBeat = std::chrono::high_resolution_clock::now();
}
GameConductor::GameConductor()
{
    logging = GameLogging::GetInstance();
    audio = AudioEngine::GetInstance();
    beatLength = std::chrono::duration_cast<std::chrono::milliseconds>(1min);
    beatLength /= MUSIC_TEMPO;
    beatLength += std::chrono::duration_cast < std::chrono::milliseconds>(5800us);
    firstBeat = std::chrono::high_resolution_clock::now();
    logging->Log("Initialised conductor.");
}
GameConductor::~GameConductor()
{
}
