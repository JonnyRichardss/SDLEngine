#ifndef USE_TEXTDISPLAY
#define USE_TEXTDISPLAY
#include "GameObject.h"
class TextDisplay : public GameObject
{
public:
	TextDisplay(std::string _text, Vector2 _pos, std::string _fontPath, int _ptSize);
	void Init();
	void InitVisuals();
	void Destroy();
protected:
	bool Update();
	bool exists;
	int ptSize;
	std::string fontPath;
	std::string displayString;
	TTF_Font* Font;
};
#endif // !USE_TEXTDISPLAY


