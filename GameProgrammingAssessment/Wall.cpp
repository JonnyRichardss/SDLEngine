#include "Wall.h"

Wall::Wall(Vector2 _pos, Vector2 _size, ColourRGBA _colour)
{
	_pos.x += (_size.x / 2.0);
	_pos.y -= (_size.y / 2.0);
	position += _pos;
	BoundingBox = _size ;
}

void Wall::Init()
{
	shown = true;
	is_static = true;
	collisionTags.push_back("Wall");
	collisionTags.push_back("Solid");
}

void Wall::InitVisuals()
{
	SDL_Surface* Surf = colour.ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

bool Wall::Update()
{
	if (colliders.empty()) {
		SetWhite();
		//SetRed();
	}
	else {
		SetRed();
	}
	//no update - returns true for "does still exist"
	return true;
}
void Wall::SetWhite()
{
	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
}
void Wall::SetRed()
{
	SDL_Surface* Surf = ColourRGBA(255, 0, 0, 255).ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
}
