#include "GameObject.h"

GameObject::GameObject()
{
	shown = true;
}

GameObject::~GameObject()
{
}

bool GameObject::UpdateAndRender(RenderableComponent &render)
{
	Update();
	if (shown) {
		render = visuals;
		return true;
	}
	else 
		return false;

}

void GameObject::Hide()
{
	shown = false;
}

void GameObject::Show()
{
	shown = true;
}
