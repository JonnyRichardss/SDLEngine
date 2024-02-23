#include "FPSCounter.h"
#include <sstream>
void FPSCounter::Init()
{
    shown = false;
    is_static = true;
    clock = GameClock::GetInstance();
    renderer = RenderEngine::GetInstance();
    renderContext = renderer->GetRenderContext();
    InitVisuals();
    timer.Start();
}

void FPSCounter::InitVisuals()
{
    FPSfont = TTF_OpenFont("cour.ttf", 72);
    visuals->UpdateLayer(100);
}

void FPSCounter::Update()
{
   
    if (FPSfont == nullptr || !shown)
        return;
    nextFrameCount++;
    nextBudgetTotal += clock->GetBudgetPercent();
    if (timer.GetTimeElapsed() > 1s) {
        timer.Reset();
        fps = nextFrameCount;
        budget = nextBudgetTotal / nextFrameCount;
        nextFrameCount = 0;
        nextBudgetTotal = 0;
    }

    std::stringstream fpsText;
    fpsText << fps << "\n" << (int)budget << "%";
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderContext, TTF_RenderUTF8_LCD_Wrapped(FPSfont, fpsText.str().c_str(), { 255,255,255,255 }, { 0,0,0,0 }, 0));
    SDL_Rect counterLocation = { 0, 0, 25 * (log10(fps) + 1),72 };
    visuals->UpdateTexture( fpsTexture);
    visuals->UpdateDestPos(&counterLocation);
    
}
