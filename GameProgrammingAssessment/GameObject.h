#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	bool UpdateAndRender(RenderableComponent &render);
	virtual void Update() = 0;
	void Hide();
	void Show();
private:
	bool shown;
	RenderableComponent visuals;
};
#endif // !USE_GAMEOBJECT

