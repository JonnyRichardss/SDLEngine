#ifndef USE_ENEMY
#define USE_ENEMY
#include "GameObject.h"
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
	GameObject* target;
	Vector2 GoalPosition;
	EnemyTypes::Type type;
	float health;
	std::vector<int> prevMelees;
	std::vector<int> prevProjectiles;
	bool Update();
	bool IsIDUsed(std::vector<int>& vec, int ID);
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void TakeDamage(float damage);
};
#endif // !USE_ENEMY


