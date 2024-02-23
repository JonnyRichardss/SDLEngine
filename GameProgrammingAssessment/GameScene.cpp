#include "GameScene.h"

GameScene::GameScene()
{
    logging = GameLogging::GetInstance();
    name = "Default Scene name";
}

GameScene::~GameScene()
{
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
}

void GameScene::Update()
{
    for (GameObject* g : UpdateQueue) {
        RenderableComponent* newComponent = nullptr;
        if (g->UpdateAndRender(newComponent)) {
            renderer->Enqueue(newComponent);
        }
    }
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
    logging->Log("Scene " + name + ": registered object: "+obj->GetName());
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
        logging->Log("Scene " + name + " deregistered object: " + g->GetName());
        delete g;
    }
    else
        logging->Log("Scene " + name + " failed to deregister object: " + g->GetName());
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
