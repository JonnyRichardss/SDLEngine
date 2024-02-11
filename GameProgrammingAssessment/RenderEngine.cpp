#include "RenderEngine.h"
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
static RenderEngine* _instance;
RenderEngine* RenderEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new RenderEngine();
    return _instance;
}
RenderEngine::RenderEngine()
{
    clock = GameClock::GetInstance();
    
    SDL_GetDesktopDisplayMode(0, &mode);
    window = SDL_CreateWindow("Jonathan Richards -- 26541501", mode.w /4, mode.h / 4, 800, 600, SDL_WINDOW_RESIZABLE);
    renderContext = SDL_CreateRenderer(window, -1, 0);
    fps = 0;
    SHOW_FPS = false;
    FPSfont = nullptr;
    TTF_Init();
}

RenderEngine::~RenderEngine()
{
    
}

SDL_Window* RenderEngine::GetWindow()
{
    return window;
}

SDL_Renderer* RenderEngine::GetRenderContext()
{
    return renderContext;
}

void RenderEngine::RenderFrame()
{
    SDL_SetRenderDrawColor(renderContext, 0, 0, 0, 0); //backg colour
    SDL_RenderClear(renderContext);
    // test code
    /*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle = {50,50,100,100};
    SDL_RenderDrawRect(renderer, &rectangle);
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderDrawLine(renderer, 200, 100, 200, 500);
    */
    if (SHOW_FPS) DrawFPS();
    for (RenderableComponent* c : RenderQueue) {
        SDL_RenderCopy(renderContext, c->texture, c->source_pos, c->destination_pos);
    }
    RenderQueue.clear();
    SDL_RenderPresent(renderContext);
}
void RenderEngine::DrawFPS()
{
    if (FPSfont == nullptr)
        return;
    if (clock->GetFrameCount() % 10 == 0)
        fps = clock->GetFPS();
    std::stringstream fpsText;
    fpsText << fps << "\n" << clock->GetBudgetPercent() << "%";
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderContext,TTF_RenderUTF8_LCD_Wrapped(FPSfont, fpsText.str().c_str(), {255,255,255,255}, {0,0,0,0},0));
    SDL_Rect counterLocation = { 0, 0, 25 * (log10(fps)+1),72};
    RenderableComponent component(fpsTexture, &counterLocation);
    Enqueue(&component);

}
void RenderEngine::ToggleFullscreen()
{
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) 
        SDL_SetWindowFullscreen(window, 0);
    else 
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void RenderEngine::ToggleFPSCounter()
{
    if (SHOW_FPS) {
        std::cout << "DISABLED FPS COUNTER\n";
        SHOW_FPS = false;
        TTF_CloseFont(FPSfont);
        FPSfont = nullptr;
    }
    else {
        std::cout << "ENABLED FPS COUNTER\n";
        SHOW_FPS = true;
        FPSfont = TTF_OpenFont("cour.ttf", 72);
    }
}

void RenderEngine::Enqueue(RenderableComponent* object)
{
    RenderQueue.push_back(object);
}


