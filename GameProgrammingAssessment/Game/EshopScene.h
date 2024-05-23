#pragma once
#ifndef USE_ESHOPSCENE
#define USE_ESHOPSCENE
#include "GameScene.h"

class EshopScene : public GameScene
{
public:
	EshopScene();
	~EshopScene();
	void CreateObjects();
	void PreUpdate();
	void PostUpdate();
	void Load();
	void Unload();
};
#endif // !USE_ESHOPSCENE


