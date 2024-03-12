#ifndef USE_GAMESCENE
#define USE_GAMESCENE
#include <string>
#include <vector>
#include "GameObject.h"
#include "GameLogging.h"
#include "RenderEngine.h"
class GameScene
{
	//this will eventually be a wrapper for an update queue
	//it holds the queue and engine can update whatever scene it wants
	//hopefully makes it so engine.cpp doesn't need to include every single gameObject to create instances of them
	//not entirely sure how I will insantiate these
	//think i will have to do sceneIncludes in engine
	//Scene1.h : gamescene etc.
	//load and initalise scenes
public:
	GameScene();
	virtual ~GameScene();
	virtual void CreateObjects() = 0;
	void Update();
	virtual void PreUpdate() = 0;
	virtual void PostUpdate() = 0;
	//technically they can have any implementation but the intent is that Load() only has to be called AFTER Unload()
	virtual void Load()=0;
	virtual void Unload()=0;
	void Delete();
	void MoveStatics();
	void RegisterObject(GameObject* obj);
	void DeregisterObject(GameObject* obj);
	void DrawBBs();
	std::string GetName();
	GameLogging* logging;
	RenderEngine* renderer;
protected:
	bool initialised = false;
	bool loaded = false;
	void Init();
	void DestroyObjects();
	std::vector<GameObject*> UpdateQueue;
	std::string name;
};
#endif // !USE_GAMESCENE


