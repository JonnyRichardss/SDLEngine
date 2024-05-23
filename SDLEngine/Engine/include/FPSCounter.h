#pragma once
#ifndef USE_FPSCOUNTER
#define USE_FPSCOUNTER
#include "GameObject.h"
#include "GameClock.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "RenderEngine.h"
#include "Timer.h"
class FPSCounter : public GameObject
{
public:
	//things
	void Init();
	void InitVisuals();
protected:
	long long fps = 0;
	float budget = 0;
	int nextFrameCount = 0;
	float nextBudgetTotal = 0;
	Timer timer;
	bool Update();
	TTF_Font* FPSfont;

};
#endif // !USE_FPSCOUNTER


