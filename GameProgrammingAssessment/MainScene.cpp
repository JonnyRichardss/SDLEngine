#include "MainScene.h"
#include "CollisionCalculator.cuh"
#include "IncludeGameObjects.h"
#include "AudioEngine.h"
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
	RegisterObject(player);
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
	AudioEngine::GetInstance()->StartMusic();
}

void MainScene::Unload()
{
	JRCollision::Free();
}
