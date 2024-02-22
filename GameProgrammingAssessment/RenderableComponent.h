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
	RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, int _layer);
	RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos,int _layer);
	virtual ~RenderableComponent();
	SDL_Rect* GetSourcePos();
	SDL_Rect* GetDestPos();
	SDL_Texture* GetTexture();
	int GetLayer();
	void UpdateLayer(int newLayer);
	void UpdateSourcePos(SDL_Rect* newPos);
	void UpdateDestPos(SDL_Rect* newPos);
	void UpdateTexture(SDL_Texture* newTex);
	bool operator > (const RenderableComponent& other);
	bool operator < (const RenderableComponent& other);
protected:
	int layer;
	SDL_Rect* source_pos;
	SDL_Texture* texture;
	SDL_Rect* destination_pos;
};
#endif
