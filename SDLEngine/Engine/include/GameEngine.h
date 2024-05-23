#ifndef USE_ENGINE
#define USE_ENGINE

#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include "FPSCounter.h"
//#include "Global_Flags.h" TODO!
#include "GameLogging.h"
#include "GameScene.h"
//#include "GameConductor.h" TODO!
#include "AudioEngine.h"
//#include "InputHandler.h" TODO!
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
	//GameConductor* conductor;  TODO!
	GameClock* clock;
	FPSCounter* FPS;
	GameScene* ActiveScene;
	//InputHandler* input; TODO!
	std::vector<GameScene*> AllScenes;
	void CreateScenes();
	void SwitchScene(int SceneIndex);
	void ProcessEvents();

	void FPSUpdate();


	void GameLoop();

};
#endif // !USE_ENGINE
