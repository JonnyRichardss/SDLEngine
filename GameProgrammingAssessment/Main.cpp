
#include "GameEngine.h"
#include "EshopAnim.h"
int main(int argc, char* args[])
{
    //std::cout << "Hello World!\n";
    GameEngine* engine = GameEngine::GetInstance();
    engine->StartLoop();
    return 0;
}