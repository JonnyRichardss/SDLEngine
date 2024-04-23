#include "InputHandler.h"
#include "SDL.h"
static InputHandler* _instance;
InputHandler* InputHandler::GetInstance()
{
    if (_instance == nullptr)
        _instance = new InputHandler();
    return _instance;
}
void InputHandler::ResetActions()
{
    for (int i = 0; i < InputActions::NumActions; i++) {
        actionStates[i] = false;
    }
}
InputHandler::InputHandler()
{
    ResetActions();
}
InputHandler::~InputHandler()
{
}
void InputHandler::PollInput()
{
    const uint8_t* keyStates = SDL_GetKeyboardState(nullptr);
    ResetActions();
    //big list of ifs that define each action
    if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) actionStates[InputActions::UP] = true;
    if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) actionStates[InputActions::DOWN] = true;
    if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]) actionStates[InputActions::LEFT] = true;
    if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]) actionStates[InputActions::RIGHT] = true;
}

bool InputHandler::GetActionState(InputActions::Action action)
{
    return actionStates[action];
}

