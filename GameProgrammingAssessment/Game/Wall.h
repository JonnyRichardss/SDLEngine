#ifndef USE_WALL
#define USE_WALL
#include "GameObject.h"
class Wall : public GameObject
{
public:
	//Wall constructor -- define with x,y (pos) and w,h (size) same as SDL_rect
	Wall(Vector2 _pos, Vector2 _size,ColourRGBA _colour);
	void Init();
	void InitVisuals();
protected:
	ColourRGBA colour;
	bool Update();
	void SetWhite();
	void SetRed();
};
#endif // !USE_WALL


