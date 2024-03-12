#include "BoidScene.h"
#include "IncludeGameObjects.h"
#include "Boid.cuh"
#include "Global_Flags.h"
#include "Timer.h"
BoidScene::BoidScene()
{
	name = "Boids Scene";
}

BoidScene::~BoidScene()
{
	Unload();
}
static Timer SplashTimer;
void BoidScene::CreateObjects()
{
	SplashTimer.Start();
	for (int i = 0; i < NUM_BOIDS; i++) {
		Boid* boid = new Boid();
		UpdateQueue.push_back(boid);
		boid->SetOwner(this);
		boid->SetName(i);
	}
}

void BoidScene::PreUpdate()
{
	if (!loaded) Load();
	JRCudaCalc::GetNeighboursCUDA(UpdateQueue);
}

void BoidScene::PostUpdate()
{
	if (SplashTimer.GetTimeElapsed() > 999s) {
		Delete();
		//the way DeleteScene is implemented it goes to scene 0
	}
}

void BoidScene::Load()
{
	JRCudaCalc::Alloc(UpdateQueue.size());
	loaded = true;
}

void BoidScene::Unload()
{
	JRCudaCalc::Free();
	loaded = false;
}

