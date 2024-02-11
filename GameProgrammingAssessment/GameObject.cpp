#include "GameObject.h"

GameObject::GameObject()
{
	shown = true;
	visuals = new RenderableComponent();
	renderer = RenderEngine::GetInstance();
	//engine = GameEngine::GetInstance();
	clock = GameClock::GetInstance();
	window = renderer->GetWindow();
	renderContext = renderer->GetRenderContext();
	GetWindowParams();
}

GameObject::~GameObject()
{
	delete visuals;
}
void GameObject::GetWindowParams()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
bool GameObject::UpdateAndRender(RenderableComponent*& render)
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

void GameObject::ToggleVisibility()
{
	shown = shown ? false : true;
}
