#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	bool UpdateAndRender(RenderableComponent*& render);
	
	void Hide();
	void Show();
	virtual void Init() = 0;
protected:
	
	virtual void Update() = 0;
	bool shown;
	RenderableComponent* visuals;
};
#endif // !USE_GAMEOBJECT

