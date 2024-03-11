#include "EshopScene.h"
#include "IncludeGameObjects.h"
EshopScene::EshopScene()
{
	name = "Eshop Animation";
}
EshopScene::~EshopScene()
{
}
void EshopScene::CreateObjects()
{
	EshopAnim* Eshop = new EshopAnim();
	UpdateQueue.push_back(Eshop);
}

void EshopScene::PreUpdate()
{
}
