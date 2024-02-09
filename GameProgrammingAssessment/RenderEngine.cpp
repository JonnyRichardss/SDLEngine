#include "RenderEngine.h"
#include <string>
#include <cmath>
RenderEngine::RenderEngine(GameClock* _clock)
{
    clock = _clock;
    //this whole clock business is VERY messy - id like to make all these classes static but i'm not too sure if thats "good practice" or not
    SDL_GetDesktopDisplayMode(0, &mode);
    window = SDL_CreateWindow("Jonathan Richards -- 26541501", mode.w /4, mode.h / 4, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    fps = 0;
    SHOW_FPS = false;
    FPSfont = nullptr;
}

RenderEngine::~RenderEngine()
{
    
}

void RenderEngine::RenderFrame()
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); //backg colour
    SDL_RenderClear(renderer);
    // test code
    /*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle = {50,50,100,100};
    SDL_RenderDrawRect(renderer, &rectangle);
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderDrawLine(renderer, 200, 100, 200, 500);
    */
    if (SHOW_FPS) DrawFPS();
    for (RenderableComponent c : RenderQueue) {
        SDL_RenderCopy(renderer, c.texture, c.source_pos, c.destination_pos);
    }
    RenderQueue.clear();
    SDL_RenderPresent(renderer);
}
void RenderEngine::DrawFPS()
{
    if (FPSfont == nullptr)
        return;
    if (clock->GetFrameCount() % 10 == 0)
        fps = clock->GetFPS();
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_LCD(FPSfont, std::to_string(fps).c_str(), {255,255,255,255},{0,0,0,0}));
    SDL_Rect counterLocation = { 0, -10, 25 * (log10(fps)+1),50};
    RenderableComponent component(fpsTexture, &counterLocation);
    Enqueue(component);

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
        SHOW_FPS = false;
        TTF_CloseFont(FPSfont);
        TTF_Quit();
        FPSfont = nullptr;
    }
    else {
        SHOW_FPS = true;
        TTF_Init();
        FPSfont = TTF_OpenFont("USN_Stencil.ttf", 72);\
    }
}

void RenderEngine::Enqueue(RenderableComponent& object)
{
    RenderQueue.push_back(object);
}


