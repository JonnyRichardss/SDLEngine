#ifndef USE_ENEMYSPAWNER
#define USE_ENEMYSPAWNER
#include "GameObject.h"
class PlayerController;
class EnemySpawner : public GameObject
{
public:
	EnemySpawner(Vector2 pos,GameObject* _player);
	void Init();
	void InitVisuals();
protected:
	bool Update();
	PlayerController* player;
	bool OddBeat;
	int SpawnCount;
};
#endif // !USE_ENEMYSPAWNER


