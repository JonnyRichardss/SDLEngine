#include "FPSCounter.h"
#include <sstream>
void FPSCounter::Init()
{
    shown = false;
    clock = GameClock::GetInstance();
    renderer = RenderEngine::GetInstance();
    renderContext = renderer->GetRenderContext();
    FPSfont = TTF_OpenFont("cour.ttf", 72);
    visuals->UpdateLayer(100);
}


void FPSCounter::Update()
{
    if (!shown) {
        return;
    }
    if (FPSfont == nullptr)
        return;
    if (clock->GetFrameCount() % 10 == 0)
        fps = clock->GetFPS();
    std::stringstream fpsText;
    fpsText << fps << "\n" << clock->GetBudgetPercent() << "%";
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderContext, TTF_RenderUTF8_LCD_Wrapped(FPSfont, fpsText.str().c_str(), { 255,255,255,255 }, { 0,0,0,0 }, 0));
    SDL_Rect counterLocation = { 0, 0, 25 * (log10(fps) + 1),72 };
    visuals->UpdateTexture( fpsTexture);
    visuals->UpdateDestPos(&counterLocation);
    
}
