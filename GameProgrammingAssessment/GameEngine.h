#ifndef USE_ENGINE
#define USE_ENGINE
#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include "FPSCounter.h"
#include <vector>
#include "Global_Flags.h"
#include "GameLogging.h"
class GameEngine
{
public:
	static GameEngine* GetInstance();
	void StartLoop();
	void RegisterObject(GameObject* g);
	bool DeregisterObject(GameObject* g,bool delete_obj);
private:
	GameEngine();
	~GameEngine();
	bool ENGINE_QUIT_FLAG = false;
	GameLogging* logging;
	RenderEngine* rendering;
	GameClock* clock;
	FPSCounter* FPS;
	std::vector<GameObject*> UpdateQueue;
	void ProcessEvents();
	void Update();
	void MoveStatics();
	void GameLoop();
	void DrawBBs();
};
#endif // !USE_ENGINE
