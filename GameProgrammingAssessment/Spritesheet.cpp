#include "Spritesheet.h"
#include "SDL_image.h"
#include "RenderEngine.h"
#include "GameUtils.h"
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
	std::string imgPath = filename+fileformat;
	std::string dimPath = filename+".spritedims";
	SDL_Surface* Surf = IMG_Load(imgPath.c_str());
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(RenderEngine::GetInstance()->GetRenderContext(), Surf);
	SDL_FreeSurface(Surf);
	UpdateTexture(Tex);
	//load dimension file
	std::vector<std::string> dimLines = ReadFile(dimPath);
	std::vector<std::string> dimNums = Split(dimLines[0], ',');
	

	int w = stoi(dimNums[0]);
	int h = stoi(dimNums[1]);
	int numsprites = stoi(dimNums[2]);
	//HARDCODED FOR NOW
	for (int i = 0; i < numsprites; i++) {
		Sprites.push_back(new SDL_Rect());
		*Sprites[i] = { w * i,0,w,h };
	}
	SetSpriteIndex(0);
}
