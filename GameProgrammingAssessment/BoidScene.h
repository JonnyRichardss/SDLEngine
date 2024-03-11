#ifndef USE_BOIDSCENE
#define USE_BOIDSCENE
#include "GameScene.h"
class BoidScene : public GameScene
{
public:
	BoidScene();
	~BoidScene();
	void CreateObjects();
	void PreUpdate();
private:

};

#endif // !USE_BOIDSCENE

