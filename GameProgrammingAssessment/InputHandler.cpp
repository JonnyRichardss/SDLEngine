#include "InputHandler.h"
#include <chrono>

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
        actionTimings[i] = 0;
    }
}
InputHandler::InputHandler()
{
    ResetActions();
    logging = GameLogging::GetInstance();
    clock = GameClock::GetInstance();
    conductor = GameConductor::GetInstance();
}
InputHandler::~InputHandler()
{
}
void InputHandler::PollInput()
{
    const uint8_t* keyStates = SDL_GetKeyboardState(nullptr);

    int MouseX, MouseY;

    const uint32_t mouseState = SDL_GetMouseState(&MouseX,&MouseY);
    ResetActions();
    MousePos = { (float)MouseX,(float)MouseY };

    //big list of ifs that define each action
    if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) actionStates[InputActions::UP] = true;
    if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) actionStates[InputActions::DOWN] = true;
    if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]) actionStates[InputActions::LEFT] = true;
    if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]) actionStates[InputActions::RIGHT] = true;
    /*
    * these are handled by events
    if (mouseState & SDL_BUTTON(1)) actionStates[InputActions::ATTACK1] = true;
    if (mouseState & SDL_BUTTON(3)) actionStates[InputActions::ATTACK2] = true;
    */

    
}

bool InputHandler::GetActionState(InputActions::Action action)
{
    return actionStates[action];
}

double InputHandler::GetActionTiming(InputActions::Action action)
{
    return actionTimings[action];
}

Vector2 InputHandler::GetMousePos()
{
    return MousePos;
}

void InputHandler::MouseEvent(SDL_Event event)
{
    //no need to check for state since this function only receives button down events
    //also InputHandler runs BEFORE PollEvents so the relevent actions are definitely reset here
    int SDLtimestamp = event.button.timestamp;
    uint8_t mouseButton = event.button.button;

    std::chrono::high_resolution_clock::time_point inputTP = clock->SDLToTimePoint(SDLtimestamp);

    InputActions::Action action;
    switch (mouseButton){
    case 1:
        logging->DebugLog("Mouse1");
        action = InputActions::ATTACK1;
        break;
    case 3:
        logging->DebugLog("Mouse2");
        action = InputActions::ATTACK2;
        break;
    default:
        logging->DebugLog("Unregistered mouse button pressed!");
        return;
    }

    actionStates[action] = true;
    actionTimings[action] = conductor->GetInputTiming();
}

