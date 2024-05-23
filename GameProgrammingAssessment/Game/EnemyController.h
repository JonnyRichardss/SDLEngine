#ifndef USE_ENEMY
#define USE_ENEMY
#include "GameObject.h"
#include "Spritesheet.h"
class MeleeCollider; class Projectile; class PlayerController; //fwd def

class EnemyController : public GameObject
{
public:
	EnemyController(GameObject* _target,Vector2 _pos);
	void Init();
	void InitVisuals();
protected:
	SpriteSheet* sprites;
	bool spriteFrame;
	PlayerController* player;
	Vector2 GoalPosition;
	bool alive;
	float health;
	float stepwidth;
	std::vector<int> prevMelees;
	std::vector<int> prevProjectiles;
	bool Update();
	bool IsIDUsed(std::vector<int>& vec, int ID);
	void DeathCheck();
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void TakeDamage(float damage);
	void AddScore(MeleeCollider* collider);
	void AddScore(Projectile* collider);
	void AddScore(float damage, double timing);
};
#endif // !USE_ENEMY


