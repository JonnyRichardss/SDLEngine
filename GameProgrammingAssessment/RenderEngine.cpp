#include "RenderEngine.h"
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

static RenderEngine* _instance;
RenderEngine* RenderEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new RenderEngine();
    return _instance;
}
RenderEngine::RenderEngine()
{
    RenderQueue.clear();
    clock = GameClock::GetInstance();
    logging = GameLogging::GetInstance();
    SDL_GetDesktopDisplayMode(0, &mode);
    window = SDL_CreateWindow("Jonathan Richards -- 26541501", (mode.w - WINDOW_WIDTH) / 2, (mode.h - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderContext = SDL_CreateRenderer(window, -1, 0);
    TTF_Init();
    logging->Log("Initialised render engine.");
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
    std::sort(RenderQueue.begin(),RenderQueue.end(), [](auto a, auto b){return *a < *b;});
    for (RenderableComponent* c : RenderQueue) {
        SDL_RenderCopyEx(renderContext, c->GetTexture(), c->GetSourcePos(), c->GetDestPos(), c->GetAngle(), c->GetCentrePoint(), c->GetFlip());
    }
    RenderQueue.clear();
    SDL_RenderPresent(renderContext);
}

void RenderEngine::ToggleFullscreen()
{
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) 
        SDL_SetWindowFullscreen(window, 0);
    else 
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void RenderEngine::Enqueue(RenderableComponent* object)
{
    RenderQueue.push_back(object);
}

Vector2 RenderEngine::GameToWindowScaling(Vector2 vec)
{
    //lowkey tempted to add a element-wise multiply but since multiplication technically isn't defined for vectors im just going to leave it as is with 2 variables
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    vec.x *= (float)windowWidth / (float)(GAME_MAX_X * 2);

    vec.y *= (float)windowHeight / (float)(GAME_MAX_Y * 2);
    return vec;
}

Vector2 RenderEngine::GameToWindowTranslation(Vector2 vec)
{
    //this function assumes you have already scaled - not much i can do about that save for combining the transforms but the way BBs work ATM i need scaling separate
    //INVERT Y AXIS
    //vec.y *= -1;
    //TRANSFORM VECTOR INTO +VE +VE
    vec += GameToWindowScaling(Vector2(GAME_MAX_X, GAME_MAX_Y));

    return vec;
}

Vector2 RenderEngine::GameToWindowCoords(Vector2 vec)
{
    vec = GameToWindowScaling(vec);
    vec = GameToWindowTranslation(vec);
    return vec;
}

Vector2 RenderEngine::WindowToGameScaling(Vector2 vec)
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    vec.x *=  (float)(GAME_MAX_X * 2)/(float)windowWidth ;

    vec.y *= (float)(GAME_MAX_Y * 2)/ (float)windowHeight;
    return vec;
}

Vector2 RenderEngine::WindowToGameTranslation(Vector2 vec)
{
    
    vec -= Vector2(GAME_MAX_X, GAME_MAX_Y);
    //vec.y *= -1;
    return vec;
}

Vector2 RenderEngine::WindowToGameCoords(Vector2 vec)
{
    
    vec = WindowToGameScaling(vec);
    vec = WindowToGameTranslation(vec);
    return vec;
}


