#include <locale>
#include "GameEngine.h"
int main(int argc, char* args[])
{
    std::setlocale(LC_ALL, "");
    //std::cout << "Hello World!\n";
    GameEngine* engine = GameEngine::GetInstance();
    engine->StartLoop();
    return 0;
}