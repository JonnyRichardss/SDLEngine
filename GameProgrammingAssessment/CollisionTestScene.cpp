#include "CollisionTestScene.h"
#include "CollisionCalculator.cuh"
#include "IncludeGameObjects.h"
CollisionTestScene::CollisionTestScene()
{
	name = "Collision Scene";
}

CollisionTestScene::~CollisionTestScene()
{
	Unload();
}

void CollisionTestScene::CreateObjects()
{
	for (int i = 0; i < NUM_TEST_COLLIDERS; i++) {
		//create colliders gameobjecst
		TestCollider* box = new TestCollider();
		UpdateQueue.push_back(box);
		box->SetName(i);
	}
}

void CollisionTestScene::PreUpdate()
{
	JRCollision::CalculateCollsion(UpdateQueue);
}

void CollisionTestScene::PostUpdate()
{
}

void CollisionTestScene::Load()
{
	JRCollision::Init();
}

void CollisionTestScene::Unload()
{
	JRCollision::Free();
}
