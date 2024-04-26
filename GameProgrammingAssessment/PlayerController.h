#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
class PlayerController : public GameObject
{
public:
	void Init();
	void InitVisuals();
protected:
	float health;
	std::vector<int> prevMelees;
	std::vector<int> prevProjectiles;
	bool Update();
	void ToggleColour();
	bool IsIDUsed(std::vector<int>& vec, int ID);
	void DoMovement(Vector2 MoveVector);
	void DoAttacks();
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void TakeDamage(float damage);
	bool a1waiting, a2waiting;
	double a1Timing, a2Timing;
};

#endif // !USE_PLAYERCONTROLLER

