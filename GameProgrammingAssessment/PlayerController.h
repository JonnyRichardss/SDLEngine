#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
class PlayerController : public GameObject
{
public:
	//things
	void Init();
protected:

	void Update();
};

#endif // !USE_PLAYERCONTROLLER

