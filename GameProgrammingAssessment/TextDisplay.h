#ifndef USE_TEXTDISPLAY
#define USE_TEXTDISPLAY
#include "GameObject.h"
class TextDisplay : public GameObject
{
public:
	TextDisplay(std::string _text, Vector2 _pos, std::string _fontPath, int _ptSize,int _heightMult);
	void Init();
	void InitVisuals();
	void UpdateText();
	void Destroy();
protected:
	bool Update();
	bool exists;
	int ptSize;
	int heightMult;
	std::string fontPath;
	std::string displayString;
	TTF_Font* Font;
};
#endif // !USE_TEXTDISPLAY


