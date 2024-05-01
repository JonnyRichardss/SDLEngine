#include "IntegerDisplay.h"

IntegerDisplay::IntegerDisplay(Vector2 _position,std::string _name, std::string _fontPath, int _ptSize)
{
	position = _position;
	name = _name;
	fontPath = _fontPath;
	ptSize = _ptSize;
	display = 0;
	displayString = std::to_string(display);
}

void IntegerDisplay::Init()
{
	shown = true;
	is_static = false;//statics are borked lol
	velocity = Vector2::zero();
	BoundingBox = Vector2(ptSize * displayString.length(), ptSize * 2);
}

void IntegerDisplay::InitVisuals()
{
	Font = TTF_OpenFont(fontPath.c_str(), ptSize*4);
	UpdateTexture();
	visuals->UpdateLayer(100);
}

void IntegerDisplay::SetValue(int newVal)
{
	display = newVal;
	UpdateTexture();
}

int IntegerDisplay::GetValue()
{
	return display;
}

void IntegerDisplay::AddValue(int newVal)
{
	display += newVal;
	UpdateTexture();
}

void IntegerDisplay::SetName(std::string newName)
{
	name = newName;
}

bool IntegerDisplay::Update()
{
	return true;
}

void IntegerDisplay::UpdateTexture()
{

	displayString = name +": "+std::to_string(display);
	SDL_Surface* Surf = TTF_RenderUTF8_Blended_Wrapped(Font, displayString.c_str(), { 255,255,255,255 }, 0);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);
	SDL_FreeSurface(Surf);

	visuals->UpdateTexture(Tex);
	BoundingBox.x = ptSize * displayString.length();
}
