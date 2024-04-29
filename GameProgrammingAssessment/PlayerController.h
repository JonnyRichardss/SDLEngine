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
	void DoBeatAttacks();
	void ActionInput(InputActions::Action attack, bool& scheduled, double& timing);
	void DoAction(InputActions::Action action);
	void DoDash();
	void DoAttack1();
	void DoAttack2();
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void TakeDamage(float damage);
	bool a1Scheduled, a2Scheduled, dashScheduled;
	int a1Beats, a2Beats;
	double a1Timing, a2Timing, dashTiming;
};

#endif // !USE_PLAYERCONTROLLER

