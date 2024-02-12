#include "RenderableComponent.h"

RenderableComponent::RenderableComponent()
{
	texture = nullptr;
	destination_pos = nullptr;
	source_pos = nullptr;
	layer = 0;
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos) : RenderableComponent()
{
	//might want to make these into copies so the renderableComponent "owns" the data so they can be safely deleted whenever
	//that WOULD mean the texture has to be re-rendered into a new texture which is fun
	texture = _texture;
	destination_pos = _destination_pos;
	//source pos can be optionally null - dest pos can too but at that point itd render fullscreen so prob best to just get a rect of the screen instead
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos) : RenderableComponent(_texture,_destination_pos)
{
	source_pos = _source_pos;
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, int _layer) : RenderableComponent(_texture, _destination_pos)
{
	layer = _layer;
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos, int _layer) : RenderableComponent(_texture,  _destination_pos,  _source_pos)
{
	layer = _layer;
}

RenderableComponent::~RenderableComponent()
{
	//this makes sense to me but apparently something is wrong with it - i might be leaking memory atm
	// 
	//SDL_DestroyTexture(texture);
	//delete destination_pos;
	//delete source_pos;
}

SDL_Rect* RenderableComponent::GetSourcePos()
{
	return source_pos;
}

SDL_Rect* RenderableComponent::GetDestPos()
{
	return destination_pos;
}

SDL_Texture* RenderableComponent::GetTexture()
{
	return texture;
}

int RenderableComponent::GetLayer()
{
	return layer;
}

void RenderableComponent::UpdateLayer(int newLayer)
{
	layer = newLayer;
}

void RenderableComponent::UpdateSourcePos(SDL_Rect* newPos)
{
	if (source_pos == nullptr) {
		source_pos = new SDL_Rect();
	}
	*source_pos = *newPos;
}

void RenderableComponent::UpdateDestPos(SDL_Rect* newPos)
{
	if (destination_pos == nullptr) {
		destination_pos = new SDL_Rect();
	}
	*destination_pos = *newPos;
}

void RenderableComponent::UpdateTexture(SDL_Texture* newTex)
{
	if (texture !=nullptr)
		SDL_DestroyTexture(texture);
	texture = newTex;
}

bool RenderableComponent::operator>(const RenderableComponent& other)
{
	return this->layer > other.layer;
}

bool RenderableComponent::operator<(const RenderableComponent& other)
{
	return this->layer < other.layer;
}
