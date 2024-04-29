#include "GameScene.h"
#include "GameEngine.h"
GameScene::GameScene()
{
    logging = GameLogging::GetInstance();
    renderer = RenderEngine::GetInstance();
    name = "Default Scene name";
}

GameScene::~GameScene()
{
    DestroyObjects();
}

void GameScene::Init()
{
    std::string logString ="Scene " +name+ ": registered objects: ";
    for (GameObject* obj : UpdateQueue) {
        obj->Init();
        obj->InitVisuals();
        logString.append(obj->GetName()+", ");
    }
    logging->FileLog(logString);
    initialised = true;
}

void GameScene::DestroyObjects()
{
    for (GameObject* obj : UpdateQueue) {
        delete obj;
    }
    std::string logString = "Scene " + name + ": destroyed all objects.";
    logging->Log(logString);
}

void GameScene::Update()
{
    if (!initialised)
        Init();
    PreUpdate();
    for (GameObject* g : UpdateQueue) {
        RenderableComponent* newComponent = nullptr;
        if (g->UpdateAndRender(newComponent)) {
            renderer->Enqueue(newComponent);
        }
    }
    PostUpdate();
    DoDeferredRegsitration();
}

void GameScene::DoDeferredRegsitration()
{
    if (!RegisterQueue.empty()) {
        for (GameObject* g : RegisterQueue) {
            RegisterObject(g);
        }
        RegisterQueue.clear();
    }
    if (!DeregisterQueue.empty()) {
        for (GameObject* g : DeregisterQueue) {
            DeregisterObject(g);
        }
        DeregisterQueue.clear();
    }
}

void GameScene::Delete()
{
    GameEngine::GetInstance()->DeleteScene(this);
}

void GameScene::MoveStatics()
{
    for (GameObject* g : UpdateQueue) {
        if (g->GetStaticStatus())
            g->MoveVisuals();
    }
}

void GameScene::RegisterObject(GameObject* obj)
{
    UpdateQueue.push_back(obj);
    obj->Init();
    obj->InitVisuals();
    obj->SetOwner(this);
    logging->FileLog("Scene " + name + ": registered object: "+obj->GetName());
}

void GameScene::DeferredRegister(GameObject* obj)
{
    RegisterQueue.push_back(obj);
}

void GameScene::DeregisterObject(GameObject* g)
{
    bool found = false;
    for (auto i = UpdateQueue.begin(); i != UpdateQueue.end(); i++) {
        if (*i == g) {
            UpdateQueue.erase(i);
            found = true;
            
            break;
        }
    }
    if (found) {
        logging->FileLog("Scene " + name + " deregistered object: " + g->GetName());
        delete g;
    }
    else
        logging->Log("Scene " + name + " failed to deregister object: " + g->GetName());
}

void GameScene::DeferredDeregister(GameObject* obj)
{
    DeregisterQueue.push_back(obj);
}

void GameScene::DrawBBs()
{
    SDL_Renderer* renderContext = renderer->GetRenderContext();
    SDL_SetRenderDrawColor(renderContext, 255, 0, 0, 255);
    for (GameObject* g : UpdateQueue) {
        g->DrawBoundingBox();
    }
    SDL_RenderPresent(renderContext);
}

std::string GameScene::GetName()
{
    return name;
}
