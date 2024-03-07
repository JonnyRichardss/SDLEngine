#include "InputHandler.h"
static InputHandler* _instance;
InputHandler* InputHandler::GetInstance()
{
    if (_instance == nullptr)
        _instance = new InputHandler();
    return _instance;
}
void InputHandler::PollInput()
{

}
InputHandler::InputHandler()
{
}
InputHandler::~InputHandler()
{
}
