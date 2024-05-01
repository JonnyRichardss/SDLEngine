#include "EnemySpawner.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "GameScene.h"
EnemySpawner::EnemySpawner(Vector2 pos,GameObject* _player)
{
	position = pos;
	player = dynamic_cast<PlayerController*>(_player);
	if (player == nullptr) {
		logging->Log("Enemy Spawner Given non-player reference for player!");
	}
}

void EnemySpawner::Init()
{
	name = "EnemySpawner";
	OddBeat = false;
	shown = false;
	SpawnCount = 1;
}

void EnemySpawner::InitVisuals()
{
}

bool EnemySpawner::Update()
{
	if (!(player->GameRunning)) return true;
	if (conductor->PollBeat()) {
		OddBeat = OddBeat ? false : true;
		if (OddBeat || player->BonusModeApplied) {
			for (int i = 0; i < SpawnCount; i++) {
				//logging->DebugLog("Tried to spawn enemy!");
				EnemyController* enemy = new EnemyController(player, position);
				scene->DeferredRegister(enemy);
			}
		}
	}
	return true;
}
