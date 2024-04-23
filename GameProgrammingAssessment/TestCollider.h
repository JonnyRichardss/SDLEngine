
#ifndef USE_COLLTESTER
#define USE_COLLTESTER
#include "GameObject.h"
class TestCollider  : public GameObject
{
public:
	void Init();
	void InitVisuals();
	void SetName(int num); //from boid lol
protected:
	void Update();
	//taken direct from boid -- i think i need to robustify (thats a word) rotating things
	void DoRotation();
	void ScreenWrap();
	void SetWhite();
	void SetRed();
};
#endif // !USE_COLLTESTER


