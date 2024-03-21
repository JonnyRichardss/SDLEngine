#include "GameObject.h"
#include "GameEngine.h"
GameObject::GameObject()
{
	shown = true;
	visuals = new RenderableComponent();
	renderer = RenderEngine::GetInstance();
	//engine = GameEngine::GetInstance();
	clock = GameClock::GetInstance();
	logging = GameLogging::GetInstance();
	window = renderer->GetWindow();
	renderContext = renderer->GetRenderContext();
	GetWindowParams();
	velocity = Vector2::zero();
	position = Vector2::zero();
	name = "Default GameObject name";
}

GameObject::~GameObject()
{
	delete visuals;
}

SDL_Rect GameObject::BBtoDestRect()
{
	Vector2 TransformedBB = renderer->GameToWindowScaling(BoundingBox);
	Vector2 TransformedPos = renderer->GameToWindowScaling(position);
	TransformedPos -= (TransformedBB*0.5f);
	TransformedPos = renderer->GameToWindowTranslation(TransformedPos);
	
	SDL_Rect dest = { TransformedPos.x,TransformedPos.y,TransformedBB.x,TransformedBB.y };
	return dest;
}
JRrect GameObject::BBtoGameRect()
{
	JRrect GameRect = JRrect((position - (BoundingBox * 0.5f)), {position.x + (BoundingBox.x*0.5f),position.y - (BoundingBox.y * 0.5f)}, (position + (BoundingBox * 0.5f)), { position.x - (BoundingBox.x * 0.5f),position.y + (BoundingBox.y * 0.5f) });
	
	return JRrect::RotateAroundPoint(GameRect,facing, position);

}
void GameObject::GetWindowParams()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
bool GameObject::UpdateAndRender(RenderableComponent*& render)
{
	Update();
	if (!is_static)//now i'm back looking at this im not entirely sure specifing static objects is necessary but ig it can stay as an artefact from pong
		position += velocity;
	if (shown) {
		if (!is_static)
			MoveVisuals();
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
void GameObject::SetOwner(GameScene* owner)
{
	scene = owner;
}
void GameObject::DrawBoundingBox()
{

	SDL_Rect BBrect = BBtoDestRect();
	Vector2 WindowPos = renderer ->GameToWindowCoords(position);
	//SDL_Rect PosRect = {WindowPos.x,WindowPos.y,5,5};
	SDL_RenderDrawRect(renderContext, &BBrect);
	//SDL_RenderDrawRect(renderContext, &PosRect);
	SDL_RenderDrawPoint(renderContext, WindowPos.x, WindowPos.y);
}
float GameObject::GetFacing()
{
	return facing;
}
bool GameObject::GetStaticStatus()
{
	return is_static;
}

Vector2 GameObject::GetPos()
{
	return position;
}

Vector2 GameObject::GetVelo()
{
	return velocity;
}

Vector2 GameObject::GetBB()
{
	return BoundingBox;
}

JRrect GameObject::GetCorners()
{
	return BBtoGameRect();
}

void GameObject::MoveVisuals()
{
	GetWindowParams();
	SDL_Rect pos = BBtoDestRect();

	visuals->UpdateDestPos(&pos);
	visuals->UpdateAngleRAD(facing);
}

std::string GameObject::GetName()
{
	return name;
}

