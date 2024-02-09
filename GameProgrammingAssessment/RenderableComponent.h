#pragma once
#ifndef USE_RENDERABLE
#define USE_RENDERABLE
#include "SDL.h"
class RenderableComponent
{
public:
	RenderableComponent();
	RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos);
	RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos);
	virtual ~RenderableComponent();
	SDL_Rect* source_pos;
	SDL_Texture* texture;
	SDL_Rect* destination_pos;
};
#endif
