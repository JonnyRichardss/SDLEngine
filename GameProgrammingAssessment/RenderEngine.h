
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
	static RenderEngine* GetInstance();
	RenderEngine();
	~RenderEngine();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderContext();
	void RenderFrame();
	void ToggleFullscreen();
	void ToggleFPSCounter();
	void Enqueue(RenderableComponent* object);
private:
	std::vector<RenderableComponent*> RenderQueue;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	SDL_DisplayMode mode;
	TTF_Font* FPSfont;
	bool SHOW_FPS;
	long long fps;
	void DrawFPS();
};
#endif // !USE_RENDER
