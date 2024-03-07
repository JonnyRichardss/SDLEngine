#pragma once
#ifndef USE_INPUTHANDLER
#define USE_INPUTHANDLER
class InputHandler
{
public:
	static InputHandler* GetInstance();
	void PollInput();
	//could do a few things
	//1 - hardcode actions here
	//2 - store inputs in inputhandler and access them per-object
	//3 - use void* to dynamically change action (silly?)

private:
	InputHandler();
	~InputHandler();
};
#endif // !USE_INPUTHANDLER


