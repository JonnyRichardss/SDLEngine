#include "GameEngine.h"
#include <iostream>
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock.SetFPSLimit(60);
    rendering = new RenderEngine(&clock); //need to do it this way since SDL_Init needs to come BEFORE creating window and such
}

GameEngine::~GameEngine()
{
    delete rendering;
}

void GameEngine::StartLoop()
{
    GameLoop();
}

void GameEngine::RegisterObject(GameObject* g)
{
    UpdateQueue.push_back(g);
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
                clock.SetFPSLimit(60);
                break;
            case SDLK_F9:
                clock.SetFPSLimit(0);
                break;
            case SDLK_F8:
                rendering->ToggleFPSCounter();
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
        RenderableComponent newComponent;
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
        clock.Tick();
        std::cout << "Frame " << clock.GetFrameCount() << " - ";
        std::cout << clock.GetFPS() << "\n";
    }
}


void GameEngine::ExitGame() {
    SDL_Quit();
    ENGINE_QUIT_FLAG = true;
}
