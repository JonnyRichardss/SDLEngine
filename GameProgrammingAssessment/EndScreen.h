#ifndef USE_ENDSCREEN
#define USE_ENDSCREEN
#include "GameObject.h"
#include "Timer.h"
class EndScreen : public GameObject
{
public:
	void Init();
	void InitVisuals();
protected:
	bool Update();
	Timer timer;
};

#endif // !USE_ENDSCREEN

