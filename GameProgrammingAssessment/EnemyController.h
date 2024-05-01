#ifndef USE_ENEMY
#define USE_ENEMY
#include "GameObject.h"
class MeleeCollider; class Projectile; class PlayerController; //fwd def
namespace EnemyTypes {
	enum Type {ALPHA,BRAVO,CHARLIE};
}
class EnemyController : public GameObject
{
public:
	EnemyController(GameObject* _target,EnemyTypes::Type _enemyType ,Vector2 _pos);
	void Init();
	void InitVisuals();
protected:
	PlayerController* player;
	Vector2 GoalPosition;
	EnemyTypes::Type type;
	bool alive;
	float health;
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


