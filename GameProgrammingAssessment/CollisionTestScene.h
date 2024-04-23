#ifndef USE_COLLSCENE
#define USE_COLLSCENE
#include "GameScene.h"
class CollisionTestScene : public GameScene
{
public:
	CollisionTestScene();
	~CollisionTestScene();
	void CreateObjects();
	void PreUpdate();
	void PostUpdate();
	void Load();
	void Unload();
private:

};

#endif // !USE_COLLSCENE

