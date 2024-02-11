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
	static GameEngine* GetInstance();
	void StartLoop();
	void RegisterObject(GameObject* g);
private:
	GameEngine();
	~GameEngine();
	bool ENGINE_QUIT_FLAG = false;
	const int FRAME_CAP = 240;
	RenderEngine* rendering;
	GameClock* clock;

	std::vector<GameObject*> UpdateQueue;
	void ProcessEvents();
	void Update();
	void GameLoop();
	void ExitGame();
};
#endif // !USE_ENGINE
