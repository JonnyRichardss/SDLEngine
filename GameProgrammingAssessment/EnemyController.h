#ifndef USE_ENEMY
#define USE_ENEMY
#include "GameObject.h"
class EnemyController : public GameObject
{
public:
	void Init();
	void InitVisuals();
protected:

	bool Update();
};
#endif // !USE_ENEMY


