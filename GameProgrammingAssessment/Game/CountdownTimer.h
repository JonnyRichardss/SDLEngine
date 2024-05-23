#ifndef USE_COUNTDOWN
#define USE_COUNTDOWN
#include "TextDisplay.h"
class CountdownTimer : public TextDisplay {
public:
	CountdownTimer(Vector2 _pos, std::string _fontPath, int _ptSize, int _heightMult);
protected:
	int timer;
	bool Update();
};
#endif // !USE_COUNTDOWN
