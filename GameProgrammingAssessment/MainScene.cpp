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
	std::vector<Vector2> positionsMins = {{-GAME_MAX_X,-GAME_MAX_Y},{GAME_MAX_X,-GAME_MAX_Y},{-GAME_MAX_X,-GAME_MAX_Y},{-GAME_MAX_X,GAME_MAX_Y}};
	std::vector<Vector2> positionsMaxs = { {-GAME_MAX_X,GAME_MAX_Y},{GAME_MAX_X,GAME_MAX_Y},{GAME_MAX_X,-GAME_MAX_Y},{GAME_MAX_X,GAME_MAX_Y} };
	for (int i = 0; i < positionsMaxs.size();i++) {
		UpdateQueue.push_back(new EnemySpawner(positionsMaxs[i],positionsMins[i], player));
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
