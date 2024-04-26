#ifndef USE_MAINSCENE
#define USE_MAINSCENE
#include "GameScene.h"
class MainScene : public GameScene
{
public:
	MainScene();
	~MainScene();
	
	void CreateObjects();
	void PreUpdate();
	void PostUpdate();
	void Load();
	void Unload();
private:
	void CreateWalls();
};

#endif // !USE_MAINSCENE

