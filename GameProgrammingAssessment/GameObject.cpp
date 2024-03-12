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
Vector2 GameObject::GameToWindowTranslation(Vector2 GameCoords)
{
	//this function assumes you have already scaled - not much i can do about that save for combining the transforms but the way BBs work ATM i need scaling separate
	//INVERT Y AXIS
	GameCoords.y *= -1;
	//TRANSFORM VECTOR INTO +VE +VE
	GameCoords += GameToWindowScaling(Vector2(GAME_MAX_X, GAME_MAX_Y));

	return GameCoords;
}
//THIS IS VERY BROKEN: I THINK I NEED TO CHANGE TO CALCULATING AN CONSTEXPR MATRIX AND DOING THE TRANSFORMS THAT WAY
//not constexpr since window size can change with fullscreen but im sure the renderer can swap them out
//get renderengine to handle transformations - just hand it gamecoordinate SDL_Rects and get it to deal with them
//nvm turns out that its just Game to window always requires me to divide window by game width -- no idea how i didnt catch that when I was making the system in the first place
Vector2 GameObject::GameToWindowScaling(Vector2 vec) {
	//lowkey tempted to add a element-wise multiply but since multiplication technically isn't defined for vectors im just going to leave it as is with 2 variables

	vec.x *= (float)windowWidth / (float)(GAME_MAX_X*2);

	vec.y *= (float)windowHeight / (float)(GAME_MAX_Y*2);
	return vec;
}
SDL_Rect GameObject::BBtoDestRect()
{
	Vector2 TransformedBB = GameToWindowScaling(BoundingBox);
	Vector2 TransformedPos = GameToWindowScaling(position);
	TransformedPos -= (TransformedBB*0.5f);
	TransformedPos = GameToWindowTranslation(TransformedPos);
	
	SDL_Rect dest = { TransformedPos.x,TransformedPos.y,TransformedBB.x,TransformedBB.y };
	return dest;
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
	Vector2 WindowPos = GameToWindowTranslation(position);
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

