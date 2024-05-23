#ifndef USE_INTDISPLAY
#define USE_INTSIDPLAY
#include "GameObject.h"

class IntegerDisplay : public GameObject
{
public:
	IntegerDisplay(Vector2 _position,std::string _name,std::string _fontPath,int _ptSize);
	void Init();
	void InitVisuals();
	void SetValue(int newVal);
	int GetValue();
	void AddValue(int newVal);
	void SetPos(Vector2 newPos);
	void SetColour(ColourRGBA col);
	void SetName(std::string newName);
	void HideNumber();
protected:
	bool hidden;
	ColourRGBA colour;
	std::string fontPath;
	int ptSize;
	int display;
	std::string displayString;
	TTF_Font* Font;
	bool Update();
	void UpdateTexture();
};

#endif // !USE_NUMDISPLAY

