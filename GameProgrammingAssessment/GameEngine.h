#ifndef USE_ENGINE
#define USE_ENGINE
#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include "FPSCounter.h"
#include "Global_Flags.h"
#include "GameLogging.h"
#include "GameScene.h"
#include "GameConductor.h"
#include "AudioEngine.h"
#include "InputHandler.h"
#include <vector>
class GameEngine
{
public:
	static GameEngine* GetInstance();
	void StartLoop();
	void DeleteScene(GameScene* scene);
private:
	GameEngine();
	~GameEngine();
	GameLogging* logging;
	RenderEngine* renderer;
	AudioEngine* audio;
	GameConductor* conductor;
	GameClock* clock;
	FPSCounter* FPS;
	GameScene* ActiveScene;
	InputHandler* input;
	std::vector<GameScene*> AllScenes;
	void CreateScenes();
	void SwitchScene(int SceneIndex);
	void ProcessEvents();

	void FPSUpdate();


	void GameLoop();

};
#endif // !USE_ENGINE
