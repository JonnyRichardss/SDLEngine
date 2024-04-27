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
	void GetInput(Vector2& MoveVector, Vector2& mousePos);
	void ToggleColour();
	bool IsIDUsed(std::vector<int>& vec, int ID);
	void DoAttacks();
	void DecrementCooldowns();
	void DecrementCooldown(float& cooldown);
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void TakeDamage(float damage);
	bool a1Used, a2Used, dashUsed;
	float a1CoolDown, a2CoolDown, dashCoolDown;
	double a1Timing, a2Timing, dashTiming;
};

#endif // !USE_PLAYERCONTROLLER

