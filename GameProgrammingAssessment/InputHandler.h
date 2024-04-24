#ifndef USE_INPUTHANDLER
#define USE_INPUTHANDLER
#include "GameMath.h"
#include "SDL.h"
#include "GameLogging.h"
#include "GameClock.h"
#include "GameConductor.h"
namespace InputActions {
	//encased this in a namespace cos being able to just access "UP" etc. raw anywhere in code made me feel gross
	enum Action { UP, DOWN, LEFT, RIGHT, ATTACK1, ATTACK2 };//this is a little precarious but it should work, just make sure that you update the number and then you can update and access a bool for each action
	constexpr int NumActions = 6;
}
class InputHandler
{
public:
	static InputHandler* GetInstance();
	void PollInput();
	bool GetActionState(InputActions::Action action);
	double GetActionTiming(InputActions::Action action);
	Vector2 GetMousePos();
	void MouseEvent(SDL_Event event);

private:
	Vector2 MousePos;
	bool actionStates[InputActions::NumActions];
	double actionTimings[InputActions::NumActions];//this is just zero for non-timed actions
	void ResetActions();
	InputHandler();
	~InputHandler();
	GameLogging* logging;
	GameClock* clock;
	GameConductor* conductor;
};
#endif // !USE_INPUTHANDLER


