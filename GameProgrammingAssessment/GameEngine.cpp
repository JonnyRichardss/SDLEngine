#include "GameEngine.h"
#include <iostream>
#include "SpriteSheetTest.h"
static GameEngine* _instance;
static SpriteSheetTest* spriteSheet;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock = GameClock::GetInstance();
    rendering = RenderEngine::GetInstance(); 
    clock->SetFPSLimit(FRAME_CAP);
    
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
    FPS = new FPSCounter();
    spriteSheet = new SpriteSheetTest();
    RegisterObject(FPS);
    RegisterObject(spriteSheet);
    GameLoop();
}

void GameEngine::RegisterObject(GameObject* g)
{
    UpdateQueue.push_back(g);
    g->Init();
    g->InitVisuals();
}
bool GameEngine::DeregisterObject(GameObject* g,bool delete_obj) {
    bool found = false;
    for (auto i = UpdateQueue.begin(); i != UpdateQueue.end();i++ ) {
        if (*i == g) {
            UpdateQueue.erase(i);
            found = true;
            break;
        }
    }
    if (found && delete_obj) {
        delete g;
    }
    return found;
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
                ENGINE_QUIT_FLAG = true;
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
            case SDLK_SPACE:
                spriteSheet->NextSprite();
                //std::cout << "ASD";
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            ENGINE_QUIT_FLAG = true;
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
void GameEngine::MoveStatics() {
    for (GameObject* g : UpdateQueue) {
        if (g->GetStaticStatus())
            g->MoveVisuals();
    }
}


void GameEngine::GameLoop() {
    while (!ENGINE_QUIT_FLAG) {
        ProcessEvents();
        Update();
        rendering->RenderFrame();
        if (DEBUG_DRAW_BB)
            DrawBBs();
        clock->Tick();

        std::cout << "Frame " << clock->GetFrameCount() << " - " << clock->GetFPS() << " - ";
        std::cout << clock->GetBudgetPercent() << "%\n";
    }
    SDL_Quit();
}

void GameEngine::DrawBBs()
{
    SDL_Renderer* renderContext = rendering->GetRenderContext();
    SDL_SetRenderDrawColor(renderContext, 255, 0, 0, 255);
    for (GameObject* g : UpdateQueue) {
        g->DrawBoundingBox();
    }
    SDL_RenderPresent(renderContext);
}
