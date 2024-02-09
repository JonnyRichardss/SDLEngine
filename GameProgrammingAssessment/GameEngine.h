#ifndef USE_ENGINE
#define USE_ENGINE
#include "SDL.h"
#include "GameClock.h"
#include "RenderEngine.h"
#include "GameObject.h"
#include <vector>
class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void StartLoop();
	void RegisterObject(GameObject* g);
private:
	bool ENGINE_QUIT_FLAG = false;
	
	RenderEngine* rendering;

	std::vector<GameObject*> UpdateQueue;
	GameClock clock;
	void ProcessEvents();
	void Update();
	void GameLoop();
	void ExitGame();
};
#endif // !USE_ENGINE
