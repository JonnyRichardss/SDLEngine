
#include "GameEngine.h"
#include "EshopAnim.h"
int main(int argc, char* args[])
{
    //std::cout << "Hello World!\n";
    GameEngine* engine = GameEngine::GetInstance();
    EshopAnim* anim = new EshopAnim();
    engine->RegisterObject(anim);
    engine->StartLoop();
    return 0;
}