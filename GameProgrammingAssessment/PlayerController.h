#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
#include "Timer.h"
class IntegerDisplay;
class PlayerController : public GameObject
{
public:
	void Init();
	void InitVisuals();
	void AddScore(int numToAdd);
	bool GameRunning;
protected:
	bool alive;
	float health;
	Timer GameTimer;
	
	bool BonusModeActive,BonusModeApplied;
	IntegerDisplay* score;
	std::vector<int> prevMelees;
	std::vector<int> prevProjectiles;
	bool Update();
	void GetInput(Vector2& MoveVector, Vector2& mousePos);
	void ToggleColour();
	bool IsIDUsed(std::vector<int>& vec, int ID);
	void DoBeatAttacks();
	void ActionInput(InputActions::Action attack, bool& scheduled, bool& used, double& timing, int& comboCounter, int maxCombo);
	void DoAction(InputActions::Action action);
	void DoDash();
	void DoAttack1();
	void DoAttack2();
	void DeathCheck();
	void CheckDamage();
	void CheckMeleeDamage();
	void CheckProjectileDamage();
	void ResetCombos();
	void ResetSingleCombo(bool& used, int& combo, int cooldown, int max);
	void TakeDamage(float damage);
	bool offBeatPassed;
	float a1Damage, a2Damage;
	bool a1Scheduled, a2Scheduled, dashScheduled;
	bool a1Used, a2Used, dashUsed;
	int a1Beats, a2Beats;
	double a1Timing, a2Timing, dashTiming;
	int a1Combo, a2Combo, dashCombo;
};

#endif // !USE_PLAYERCONTROLLER

