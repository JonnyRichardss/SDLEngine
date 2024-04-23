#include "MainScene.h"
#include "CollisionCalculator.cuh"
#include "IncludeGameObjects.h"
MainScene::MainScene()
{
	name = "Main Game Scene";
}

MainScene::~MainScene()
{
	Unload();
}

void MainScene::CreateObjects()
{
	PlayerController* player = new PlayerController();
	UpdateQueue.push_back(player);
}

void MainScene::PreUpdate()
{
	JRCollision::CalculateCollsion(UpdateQueue);
}

void MainScene::PostUpdate()
{
}

void MainScene::Load()
{
	JRCollision::Init();
}

void MainScene::Unload()
{
	JRCollision::Free();
}
