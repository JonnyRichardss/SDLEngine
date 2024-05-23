#include "BoidScene.h"
#include "IncludeGameObjects.h"
#include "Boid.cuh"
#include "Global_Flags.h"
#include "Timer.h"
BoidScene::BoidScene()
{
	name = "Boids Scene";
	countdownSpawned = false;
}

BoidScene::~BoidScene()
{
	Unload();
}
static Timer SplashTimer;
static AudioEngine* audio;
void BoidScene::CreateObjects()
{
	
	for (int i = 0; i < NUM_BOIDS; i++) {
		Boid* boid = new Boid();
		UpdateQueue.push_back(boid);
		boid->SetOwner(this);
		boid->SetName(i);
	}
	UpdateQueue.push_back(new TextDisplay("Welcome to: \nBrian vs Some Dudes", { 0,-325 }, SCORE_FONT_PATH, 32, 4));
	UpdateQueue.push_back(new TextDisplay("Controls:\nWASD - move\nMouse 1 - Melee Attack\nMouse 2 - Projectile Attack\nMouse Pointer - Aim\nESC - Exit", { -580,0 }, SCORE_FONT_PATH, 4,8));
}

void BoidScene::PreUpdate()
{
	if (!loaded) Load();
	JRCudaCalc::GetNeighboursCUDA(UpdateQueue);
}

void BoidScene::PostUpdate()
{
	double TrackPos = audio->GetTrackPos();
	if (TrackPos > SPLASH_SCREEN_DURATION) {
		Delete();
		//the way DeleteScene is implemented it goes to scene 0
	}
	else if (TrackPos > SPLASH_SCREEN_DURATION - (MS_PER_BEAT * 3.2) && !countdownSpawned) {
		CountdownTimer* countdown = new CountdownTimer({0,0},SCORE_FONT_PATH,72,4);
		RegisterObject(countdown);
		countdownSpawned = true;
	}
}

void BoidScene::Load()
{
	JRCudaCalc::Alloc(UpdateQueue.size());
	audio = AudioEngine::GetInstance();
	audio->StartMusic();
	loaded = true;

}

void BoidScene::Unload()
{
	JRCudaCalc::Free();
	loaded = false;
}

