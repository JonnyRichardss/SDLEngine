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
void MainScene::CreateSpawners(GameObject* player) {
	std::vector<Vector2> positions = {{-GAME_MAX_X,0},{GAME_MAX_X,0},{0,-GAME_MAX_Y},{0,GAME_MAX_Y}};

	for (Vector2 p : positions) {
		UpdateQueue.push_back(new EnemySpawner(p,player));
	}
}
void MainScene::CreateObjects()
{
	PlayerController* player = new PlayerController();
	UpdateQueue.push_back(player);
	CreateSpawners(player);
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
	//AudioEngine::GetInstance()->StartMusic();
}

void MainScene::Unload()
{
	JRCollision::Free();
}
