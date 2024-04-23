#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
class PlayerController : public GameObject
{
public:
	//things
	void Init();
	void InitVisuals();
protected:

	void Update();
	void DoMovement(Vector2 MoveVector);
};

#endif // !USE_PLAYERCONTROLLER

