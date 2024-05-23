#include "SpriteSheet.h"
#include "SDL_image.h"
#include "RenderEngine.h"
#include "GameUtils.h"

int SpriteSheet::GetSpriteIndex()
{
	return currentSprite;
}

void SpriteSheet::SetSpriteIndex(int index)
{
	currentSprite = index;
	UpdateSourcePos(Sprites[index]);
}

int SpriteSheet::GetSpriteIndexMax()
{
	return (Sprites.size()-1);
}

void SpriteSheet::InitSprites(std::string filename, std::string fileformat)
{
	std::string basePath = std::string(BASE_ASSET_PATH) + filename;
	std::string imgPath = basePath + fileformat;
	std::string dimPath = basePath + SPRITE_INFO_FORMAT;
	//load Texture
	LoadTexture(filename, fileformat);
	//load dimension file
	std::vector<std::string> dimLines;
	if (!ReadFile(dimPath, dimLines)){
		logging->Log("Could not open File "+dimPath);
		return;
	}
	std::vector<std::string> dimNums = StringSplit(dimLines[0], ',');
	//these comments are old I *think* the checks above have sorted it i'm not really sure - could use try catch but i cant be bothered lol
					//this can error but im not *really* sure I care
					//maybe later when adding logging and stuff I can crashdump it or something

	int w = stoi(dimNums[0]);
	int h = stoi(dimNums[1]);
	int numsprites = stoi(dimNums[2]);

	for (int i = 0; i < numsprites; i++) {
		Sprites.push_back(new SDL_Rect());
		*Sprites[i] = { w * i,0,w,h };
	}
	SetSpriteIndex(0);
	logging->FileLog("Successfully loaded asset " + imgPath);
}
