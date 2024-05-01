#include "TextDisplay.h"
#include "GameScene.h"
TextDisplay::TextDisplay(std::string _text, Vector2 _pos, std::string _fontPath, int _ptSize,int _heightMult)
{
	position = _pos;
	name = "Text box";
	fontPath = _fontPath;
	ptSize = _ptSize;
	heightMult = _heightMult;
	displayString = _text;
}

void TextDisplay::Init()
{
	exists = true;
	shown = true;
	is_static = false;//statics are borked lol
	velocity = Vector2::zero();
	int lines = 1;
	for (char c : displayString) {
		if (c == '\n') {
			lines++;
		}
	}
	BoundingBox = Vector2(ptSize * displayString.length(), ptSize * heightMult * lines);
}

void TextDisplay::InitVisuals()
{
	Font = TTF_OpenFont(fontPath.c_str(), ptSize * 8);
	visuals->UpdateLayer(100);
	UpdateText();
}

void TextDisplay::UpdateText()
{
	SDL_Surface* Surf = TTF_RenderUTF8_Blended_Wrapped(Font, displayString.c_str(), { 255,255,255,255 }, 0);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);
	SDL_FreeSurface(Surf);

	visuals->UpdateTexture(Tex);
	BoundingBox.x = ptSize * displayString.length();
}

void TextDisplay::Destroy()
{
	scene->DeferredDeregister(this);
	exists = false;
}

bool TextDisplay::Update()
{
    return exists;
}
