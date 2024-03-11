#include "BoidScene.h"
#include "IncludeGameObjects.h"
#include "Boid.cuh"
#include "Global_Flags.h"
BoidScene::BoidScene()
{
	name = "Boids Scene";
}

BoidScene::~BoidScene()
{
	JRCudaCalc::Clear();
}

void BoidScene::CreateObjects()
{
	for (int i = 0; i < NUM_BOIDS; i++) {
		UpdateQueue.push_back(new Boid());
		UpdateQueue[i]->SetOwner(this);
	}
	JRCudaCalc::Init(UpdateQueue.size());
}

void BoidScene::PreUpdate()
{
	JRCudaCalc::GetNeighboursCUDA(UpdateQueue);
}

