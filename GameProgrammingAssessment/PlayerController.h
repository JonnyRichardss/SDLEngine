#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
class PlayerController : public GameObject
{
public:
	void Init();
	void InitVisuals();
protected:

	bool Update();
	void ToggleColour();
	void DoMovement(Vector2 MoveVector);
	void DoAttacks();
	bool a1waiting, a2waiting;
	double a1Timing, a2Timing;
};

#endif // !USE_PLAYERCONTROLLER

