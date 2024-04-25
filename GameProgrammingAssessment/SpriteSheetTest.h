#ifndef USE_TESTSS
#define USE_TESTSS
#include "GameObject.h"
#include "Spritesheet.h"
class SpriteSheetTest : public GameObject
{
public:
	void Init();
	void InitVisuals();
	void NextSprite();
protected:
	bool Update();
	SpriteSheet* Sprites;
};
#endif // !USE_TESTSS


