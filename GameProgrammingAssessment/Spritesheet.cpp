#include "Spritesheet.h"
#include "SDL_image.h"
#include "RenderEngine.h"
#include <iostream>
int Spritesheet::GetSpriteIndex()
{
	return currentSprite;
}

void Spritesheet::SetSpriteIndex(int index)
{
	currentSprite = index;
	UpdateSourcePos(Sprites[index]);
}

int Spritesheet::GetSpriteIndexMax()
{
	return (Sprites.size()-1);
}

void Spritesheet::InitSprites(std::string filename,std::string fileformat)
{
	//load Texture
	SDL_Surface* Surf = IMG_Load(filename.append(fileformat).c_str());
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(RenderEngine::GetInstance()->GetRenderContext(), Surf);
	SDL_FreeSurface(Surf);
	UpdateTexture(Tex);
	//load dimension file
	int w = 3;
	int h = 5;
	int numsprites = 10;
	//HARDCODED FOR NOW
	for (int i = 0; i < numsprites; i++) {
		Sprites.push_back(new SDL_Rect());
		*Sprites[i] = { w * i,0,w,h };
	}
	SetSpriteIndex(0);
}
