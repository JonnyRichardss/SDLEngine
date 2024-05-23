#ifndef USE_ENEMYSPAWNER
#define USE_ENEMYSPAWNER
#include "GameObject.h"
class PlayerController;
class EnemySpawner : public GameObject
{
public:
	EnemySpawner(Vector2 _posMax,Vector2 _posMin,GameObject* _player);
	void Init();
	void InitVisuals();
protected:
	Vector2 posMin, posMax;
	bool Update();
	void Teleport();
	PlayerController* player;
	int BeatCounter;
	int SpawnCount;
};
#endif // !USE_ENEMYSPAWNER


