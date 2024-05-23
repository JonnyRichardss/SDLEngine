#include "IntegerDisplay.h"

IntegerDisplay::IntegerDisplay(Vector2 _position,std::string _name, std::string _fontPath, int _ptSize)
{
	position = _position;
	name = _name;
	fontPath = _fontPath;
	ptSize = _ptSize;
	display = 0;
	displayString = std::to_string(display);
	colour = ColourRGBA::White();
}

void IntegerDisplay::Init()
{
	shown = true;
	is_static = false;//statics are borked lol
	hidden = false;
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

void IntegerDisplay::SetPos(Vector2 newPos)
{
	position = newPos;
}

void IntegerDisplay::SetColour(ColourRGBA col)
{
	colour = col;
	UpdateTexture();
}

void IntegerDisplay::SetName(std::string newName)
{
	name = newName;
}

void IntegerDisplay::HideNumber()
{
	hidden = true;
	UpdateTexture();
}

bool IntegerDisplay::Update()
{
	return true;
}

void IntegerDisplay::UpdateTexture()
{
	if (!hidden) {
		displayString = name + ": " + std::to_string(display);
	}
	else {
		displayString = name;
	}
	SDL_Surface* Surf = TTF_RenderUTF8_Blended_Wrapped(Font, displayString.c_str(), { 255,255,255,255 }, 0);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);
	SDL_FreeSurface(Surf);
	SDL_SetTextureColorMod(Tex, colour.r, colour.g, colour.b);
	visuals->UpdateTexture(Tex);
	BoundingBox.x = ptSize * displayString.length();
}
