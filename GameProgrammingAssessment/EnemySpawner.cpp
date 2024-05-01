#include "EnemySpawner.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "GameScene.h"
#include "GameRNG.h"
EnemySpawner::EnemySpawner(Vector2 _posMax,Vector2 _posMin,GameObject* _player)
{
	posMax = _posMax;
	posMin = _posMin;
	position = posMax;
	player = dynamic_cast<PlayerController*>(_player);
	if (player == nullptr) {
		logging->Log("Enemy Spawner Given non-player reference for player!");
	}
}

void EnemySpawner::Init()
{
	name = "EnemySpawner";
	BeatCounter = 0;
	shown = false;
	SpawnCount = 1;
}

void EnemySpawner::InitVisuals()
{
}

bool EnemySpawner::Update()
{
	if (!(player->GameRunning)) return true;
	Teleport();
	if (conductor->PollBeat()) {
		BeatCounter++;
		if (BeatCounter % 4 == 0 || player->BonusModeApplied) {
			for (int i = 0; i < SpawnCount; i++) {
				//logging->DebugLog("Tried to spawn enemy!");
				EnemyController* enemy = new EnemyController(player, position);
				scene->DeferredRegister(enemy);
			}
		}
	}
	return true;
}

void EnemySpawner::Teleport()
{
	position = Vector2::Lerp(posMin, posMax, RNG::randf(0, 1));
}

