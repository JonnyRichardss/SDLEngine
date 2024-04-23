#ifndef USE_INPUTHANDLER
#define USE_INPUTHANDLER
namespace InputActions {
	//encased this in a namespace cos being able to just access "UP" etc. raw anywhere in code made me feel gross
	enum Action { UP, DOWN, LEFT, RIGHT };//this is a little precarious but it should work, just make sure that you update the number and then you can update and access a bool for each action
	constexpr int NumActions = 4;
}
class InputHandler
{
public:
	static InputHandler* GetInstance();
	void PollInput();
	bool GetActionState(InputActions::Action action);


private:
	bool actionStates[InputActions::NumActions];//what if these arent booleans (eg mouse pos) (although maybe mouse pos is just a special case so i can handle it manually)
	void ResetActions();
	InputHandler();
	~InputHandler();
};
#endif // !USE_INPUTHANDLER


