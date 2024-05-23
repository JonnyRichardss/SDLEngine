#include "FPSCounter.h"
#include <sstream>
void FPSCounter::Init()
{
    shown = false;
    is_static = false;
    name = "FPS counter";
    clock = GameClock::GetInstance();
    renderer = RenderEngine::GetInstance();
    renderContext = renderer->GetRenderContext();
    position = Vector2(745, -410);
    InitVisuals();
    timer.Start();
}

void FPSCounter::InitVisuals()
{
    FPSfont = TTF_OpenFont("Assets/cour.ttf", 72);
    visuals->UpdateLayer(100);
}

bool FPSCounter::Update()
{
   
    if (FPSfont == nullptr || !shown)
        return true;
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
    SDL_Surface* surf = TTF_RenderUTF8_LCD_Wrapped(FPSfont, fpsText.str().c_str(), { 255,255,255,255 }, { 0,0,0,0 }, 0);
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderContext,surf);
    SDL_FreeSurface(surf);
    //SDL_Rect counterLocation = { 0, 0, 25 * (log10(fps) + 1),72 };
    BoundingBox = Vector2(20 * fpsText.str().length(), 80);
    visuals->UpdateTexture( fpsTexture);
    //visuals->UpdateDestPos(&counterLocation);
    return true;
}
