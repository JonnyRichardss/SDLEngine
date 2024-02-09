
#ifndef USE_RENDER
#define USE_RENDER
#include"SDL.h"
#include "GameClock.h"
#include "SDL_ttf.h"
#include "RenderableComponent.h"
#include <vector>
class RenderEngine
{
public:
	RenderEngine(GameClock* _clock);
	~RenderEngine();
	
	void RenderFrame();
	void ToggleFullscreen();
	void ToggleFPSCounter();
	void Enqueue(RenderableComponent& object);
private:
	std::vector<RenderableComponent> RenderQueue;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode mode;
	TTF_Font* FPSfont;
	bool SHOW_FPS;
	long long fps;
	void DrawFPS();
};
#endif // !USE_RENDER
