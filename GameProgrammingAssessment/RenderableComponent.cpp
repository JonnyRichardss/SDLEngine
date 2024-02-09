#include "RenderableComponent.h"

RenderableComponent::RenderableComponent()
{
	texture = nullptr;
	destination_pos = nullptr;
	source_pos = nullptr;
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos) : RenderableComponent()
{
	texture = _texture;
	destination_pos = _destination_pos;
	//source pos can be optionally null - dest pos can too but at that point itd render fullscreen so prob best to just get a rect of the screen instead
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos) : RenderableComponent(_texture,_destination_pos)
{
	source_pos = _source_pos;
}

RenderableComponent::~RenderableComponent()
{

}
