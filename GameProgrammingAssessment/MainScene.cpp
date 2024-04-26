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
void MainScene::CreateWalls() {
	std::vector<Wall*> allWalls;
	allWalls.push_back(new Wall(Vector2( 100, 100 ), Vector2(50,50), ColourRGBA(125,125,125,255)));//left


	for (Wall* w : allWalls) {
		RegisterObject(w);
	}
}
void MainScene::CreateObjects()
{
	//CreateWalls();
	PlayerController* player = new PlayerController();
	RegisterObject(player);
	EnemyController* enemy = new EnemyController(player,EnemyTypes::BRAVO,{0,0});
	RegisterObject(enemy);
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
