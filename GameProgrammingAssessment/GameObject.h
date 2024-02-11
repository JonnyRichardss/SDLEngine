#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
#include "RenderEngine.h"

#include "GameClock.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	
	bool UpdateAndRender(RenderableComponent*& render);
	
	void Hide();
	void Show();
	void ToggleVisibility();
	virtual void Init() = 0;
protected:
	int windowWidth, windowHeight;
	virtual void Update() = 0;
	void GetWindowParams();
	bool shown;
	RenderEngine* renderer;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	RenderableComponent* visuals;
};
#endif // !USE_GAMEOBJECT

