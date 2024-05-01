#include "CountdownTimer.h"
CountdownTimer::CountdownTimer(Vector2 _pos, std::string _fontPath, int _ptSize, int _heightMult) : TextDisplay("3",_pos,_fontPath,_ptSize,_heightMult)
{
	timer = 4;
}
bool CountdownTimer::Update()
{
	displayString = std::to_string(timer);
	if (conductor->PollBeat()) {
		UpdateText();
		timer--;
	}
	return exists;
}
