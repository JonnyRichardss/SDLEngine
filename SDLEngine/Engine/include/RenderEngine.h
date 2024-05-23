
#ifndef USE_RENDER
#define USE_RENDER
#include"SDL.h"
#include "GameClock.h"
#include "SDL_ttf.h"
#include "RenderableComponent.h"
#include <vector>
#include "GameLogging.h"
#include "GameMath.h"
class RenderEngine
{
public:
	static RenderEngine* GetInstance();
	
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderContext();
	void RenderFrame();
	void ToggleFullscreen();

	void Enqueue(RenderableComponent* object);

	Vector2 GameToWindowScaling(Vector2 vec);
	Vector2 GameToWindowTranslation(Vector2 vec,bool BoidHack);
	Vector2 GameToWindowCoords(Vector2 vec, bool BoidHack);

	Vector2 WindowToGameScaling(Vector2 vec);
	Vector2 WindowToGameTranslation(Vector2 vec);
	Vector2 WindowToGameCoords(Vector2 vec);
private:
	RenderEngine();
	~RenderEngine();
	std::vector<RenderableComponent*> RenderQueue;
	GameLogging* logging;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	SDL_DisplayMode mode;

};
#endif // !USE_RENDER
