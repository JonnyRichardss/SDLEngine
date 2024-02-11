#include "GameEngine.h"
#include <iostream>
static GameEngine* _instance;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock = GameClock::GetInstance();
    rendering = RenderEngine::GetInstance(); 
    clock->SetFPSLimit(FRAME_CAP);
    FPS = new FPSCounter();
    
}

GameEngine::~GameEngine()
{
}

GameEngine* GameEngine::GetInstance()
{
    if (_instance == nullptr)
        _instance = new GameEngine();
    return _instance;
}

void GameEngine::StartLoop()
{
    RegisterObject(FPS);
    GameLoop();
}

void GameEngine::RegisterObject(GameObject* g)
{
    UpdateQueue.push_back(g);
    g->Init();
}

void GameEngine::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_F11:
                rendering->ToggleFullscreen();
                break;
            case SDLK_ESCAPE:
                ExitGame();
                break;
            case SDLK_F10:
                clock->SetFPSLimit(FRAME_CAP);
                break;
            case SDLK_F9:
                clock->SetFPSLimit(0);
                break;
            case SDLK_F8:
                FPS->ToggleVisibility();
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            ExitGame();
        }
    }
}

void GameEngine::Update()
{
    for (GameObject* g : UpdateQueue) {
        RenderableComponent* newComponent = nullptr;
        if (g->UpdateAndRender(newComponent)) {
            rendering->Enqueue(newComponent);
        }
    }
}



void GameEngine::GameLoop() {
    while (!ENGINE_QUIT_FLAG) {
        ProcessEvents();
        Update();
        rendering->RenderFrame();
        clock->Tick();
        std::cout << "Frame " << clock->GetFrameCount() << " - " << clock->GetFPS() << " - ";
        std::cout << clock->GetBudgetPercent()<< "%\n";
    }
}


void GameEngine::ExitGame() {
    SDL_Quit();
    ENGINE_QUIT_FLAG = true;
}
