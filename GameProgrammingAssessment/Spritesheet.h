#ifndef USE_SPRITESHEET
#define USE_SPRITESHEET
#include "RenderableComponent.h"
#include "SDL.h"
#include <vector>
#include <string>
class SpriteSheet : public RenderableComponent
{
public:
	int GetSpriteIndex();

	void SetSpriteIndex(int index);
	int GetSpriteIndexMax();
	void InitSprites(std::string filename, std::string fileformat);
protected:
	std::vector<SDL_Rect*> Sprites;
	
	int currentSprite;
};
#endif // !USE_SPRITESHEET


