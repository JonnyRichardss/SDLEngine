#pragma once
#ifndef USE_FPSCOUNTER
#define USE_FPSCOUNTER
#include "GameObject.h"
#include "GameClock.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "RenderEngine.h"
class FPSCounter : public GameObject
{
public:
	//things
	void Init();
	
protected:
	long long fps = 0;
	bool initialised = false;
	bool enabled;
	void Update();
	TTF_Font* FPSfont;

};
#endif // !USE_FPSCOUNTER


