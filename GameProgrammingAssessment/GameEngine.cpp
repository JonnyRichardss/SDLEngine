#include "GameEngine.h"
#include "IncludeGameObjects.h"
static GameEngine* _instance;
static SpriteSheetTest* spriteSheet;
GameEngine::GameEngine()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    clock = GameClock::GetInstance();
    renderer = RenderEngine::GetInstance();
    logging = GameLogging::GetInstance();
    
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
    FPS->Init();
    GameLoop();
}

void GameEngine::SwitchScene(int SceneIndex)
{
    if (SceneIndex < 0 || SceneIndex >= AllScenes.size()) {
        logging->Log("Failed to switch to scene with index: " + std::to_string(SceneIndex));
        return;
    }
    ActiveScene = AllScenes[SceneIndex];
    logging->Log("Switched to scene with index: " + std::to_string(SceneIndex));
}

void GameEngine::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_F11:
                renderer->ToggleFullscreen();
                break;
            case SDLK_ESCAPE:
                ENGINE_QUIT_FLAG = true;
                break;
            case SDLK_F10:
                //clock->SetFPSLimit(FRAME_CAP);
                break;
            case SDLK_F9:
                //clock->SetFPSLimit(0);
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

void GameEngine::FPSUpdate() {
    RenderableComponent* newComponent = nullptr;
    if (FPS->UpdateAndRender(newComponent)) {
        renderer->Enqueue(newComponent);
    }
}

void GameEngine::GameLoop() {
    while (!ENGINE_QUIT_FLAG) {
        ProcessEvents();
        ActiveScene->Update();
        
        renderer->RenderFrame();
        if (DEBUG_DRAW_BB)
           ActiveScene->DrawBBs();
        clock->Tick();
        
    }
    SDL_Quit();
}


