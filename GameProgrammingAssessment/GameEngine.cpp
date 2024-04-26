#include "GameEngine.h"
//#include "IncludeGameObjects.h"
#include "IncludeScenes.h"
static GameEngine* _instance;
GameEngine::GameEngine()
{
    logging = GameLogging::GetInstance();
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logging->Log("Failed to initialise SDL: exiting.");
        ENGINE_QUIT_FLAG = true;
    }
    clock = GameClock::GetInstance();
    conductor = GameConductor::GetInstance();
    renderer = RenderEngine::GetInstance();
    audio = AudioEngine::GetInstance();
    input = InputHandler::GetInstance();
    logging->Log("Initialised game engine.");
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
    CreateScenes();
    GameLoop();
}



 void GameEngine::CreateScenes()
{
     GameScene* boidScene = new BoidScene();
     AllScenes.push_back(boidScene);

     //GameScene* eshopScene = new EshopScene();
     //AllScenes.push_back(eshopScene);
     
     //GameScene* collisionScene = new CollisionTestScene();
    // AllScenes.push_back(collisionScene);
      
     GameScene* mainScene = new MainScene();
     AllScenes.push_back(mainScene);

     for (auto Scene : AllScenes) {
         Scene->CreateObjects();
         logging->FileLog("Created object queues for all scenes.");
     }
     if (AllScenes.size() == 0) {
         logging->Log("Scene list empty!! Exiting!");
         ENGINE_QUIT_FLAG = true;
         return;
     }
     ActiveScene = AllScenes[0];
}

void GameEngine::SwitchScene(int SceneIndex)
{
    if (SceneIndex < 0 || SceneIndex >= AllScenes.size()) {
        logging->Log("Failed to switch to scene with index: " + std::to_string(SceneIndex));
        return;
    }
    //unloading and reloading allows for certain types of memory to be freed when not in use
    if (ActiveScene !=nullptr)
        ActiveScene->Unload();//incase last scene was unloaded
    ActiveScene = AllScenes[SceneIndex];
    ActiveScene->Load();
    logging->Log("Switched to scene with index: " + std::to_string(SceneIndex));
}
void GameEngine::DeleteScene(GameScene* scene)
{
    //WARNING: THIS FUCKS WITH YOUR SCENE INDICES -- USE CAREFULLY
    auto position = std::find(AllScenes.begin(), AllScenes.end(), scene);
    if (position == AllScenes.end()) {
        logging->FileLog("Failed to delete scene - not found in AllScenes!");
        return;
    }
    logging->FileLog("Deleted scene: " + scene->GetName());
    AllScenes.erase(position);
    SwitchScene(0); //default to switch to scene since activeScene is now invalid
    //this will get VERY confusing for generic deletes but I only plan to use this to clean up the splash screen since itll be big
    
}
void GameEngine::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        //I was going to part this out to input handler but these are all special case inputs so i'm leaving them here to separate them
        //Since i'm still processing events here I have to push mouse events back OUT to input so they can be timed
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            input->MouseEvent(event);
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_F11:
                renderer->ToggleFullscreen();
                break;
            case SDLK_ESCAPE:
                ENGINE_QUIT_FLAG = true;
                logging->Log("Recieved ESC input");
                break;
            case SDLK_F8:
                FPS->ToggleVisibility();
                break;
            case SDLK_SPACE:
                audio->ToggleTrack();
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            logging->Log("Recieved SDL Quit");
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
        clock->TickProfiling(PROFILING_STARTFRAME);
        input->PollInput();
        ProcessEvents();

        clock->TickProfiling(PROFILING_INPUT);
        ActiveScene->Update();
        FPSUpdate();

        clock->TickProfiling(PROFILING_UPDATE);
        renderer->RenderFrame();
        if (DEBUG_DRAW_BB)
           ActiveScene->DrawBBs();

        clock->TickProfiling(PROFILING_RENDER);
        clock->Tick();

        if (DO_BATCH_LOGGING)
            logging->SaveLogFile();
    }
    logging->Log("Exiting Program");
    SDL_Quit();
}


