#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject()
{
	shown = true;
	has_friction = true;
	visuals = new RenderableComponent();
	renderer = RenderEngine::GetInstance();
	//engine = GameEngine::GetInstance();
	clock = GameClock::GetInstance();
	logging = GameLogging::GetInstance();
	window = renderer->GetWindow();
	renderContext = renderer->GetRenderContext();
	input = InputHandler::GetInstance();
	audio = AudioEngine::GetInstance();
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
	
	TransformedPos = renderer->GameToWindowTranslation(TransformedPos);
	TransformedPos -= (TransformedBB / 2);
	SDL_Rect dest = { TransformedPos.x,TransformedPos.y,TransformedBB.x,TransformedBB.y };
	return dest;
}
JRrect GameObject::BBtoGameRect()
{
	/*
	* points MUST be fed as
	* (technically order doesnt matter but 0 and 3 must be opposite)
	0-------1
	|       |
	|   .   |
	|       |
	2-------3
	*/
	Vector2 point0,point1,point2,point3;
	point0 = (position - (BoundingBox * 0.5f));
	point1 = {position.x - (BoundingBox.x * 0.5f),position.y + (BoundingBox.y * 0.5f) };
	point2 = {position.x + (BoundingBox.x * 0.5f), position.y - (BoundingBox.y * 0.5f) };
	point3 = (position + (BoundingBox * 0.5f));
	JRrect GameRect = JRrect(point0,point1 ,point2 ,point3 );
	
	return JRrect::RotateAroundPoint(GameRect,facing, position);

}
void GameObject::GetWindowParams()
{
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}
bool GameObject::UpdateAndRender(RenderableComponent*& render)
{
	if (!Update()) {
		//this is silly that I have to do this but if an object deletes itself in its own update, UpdateAndRender returns true, putting a trailing RenderableComponent nullptr on the render queue
		return false;
	}
	if (!is_static) {//now i'm back looking at this im not entirely sure specifing static objects is necessary but ig it can stay as an artefact from pong -- NO it def is cos walls exist 
		if (has_friction) velocity -= velocity * BASE_FRICTION;
		position += velocity;
	}
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
static int debugVecidx=0;
void GameObject::DrawBoundingBox()
{
	/*
	0-------1
	|       |
	|   .   |
	|       |
	2-------3
	*/
	
	Vector2 WindowPos = renderer->GameToWindowCoords(position);
	
	
	JRrect corners = BBtoGameRect();
	SDL_Point* points = new SDL_Point[5];
	for (int i = 0; i < 4;i++) {
		Vector2 vec = corners.points[i];
		vec = renderer->GameToWindowCoords(vec);
		points[i] = vec.ToSDLPoint();
	}
	SDL_Point temp = points[0];
	points[0] = points[1];
	points[1] = temp;
	points[4] = points[0];
	SDL_RenderDrawPoint(renderContext,WindowPos.x,WindowPos.y);
	SDL_RenderDrawLines(renderContext, points, 5);
	SDL_SetRenderDrawColor(renderContext, 0, 255, 0, 255);
	if (!collisionVectors.empty()) {
		Vector2 debugVec = collisionVectors[debugVecidx];
		debugVec += position;
		debugVec = renderer->GameToWindowCoords(debugVec);
		SDL_RenderDrawLine(renderContext, WindowPos.x, WindowPos.y, debugVec.x, debugVec.y);
	}
	SDL_SetRenderDrawColor(renderContext,  255,0, 0, 255);
	delete[] points;
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

bool GameObject::CompareTag(std::string tag)
{
	for (std::string otherTag : collisionTags) {
		if (tag == otherTag)
			return true;
	}
	return false;
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
void GameObject::Reflect(Vector2 SurfaceNormal) {
	SurfaceNormal = SurfaceNormal.Normalise();
	velocity -= 2 * SurfaceNormal * Vector2::dot(velocity, SurfaceNormal);
}
void GameObject::SolidCollision() {
	if (colliders.empty()) return;
	for (int i = 0; i < colliders.size(); i++) {
		GameObject* c = colliders[i];
		if (!(c->CompareTag("Solid")) || c == this) continue;
		Vector2 offset = c->GetPos() - position;
		float shortestOffset = (abs(offset.x) < abs(offset.y)) ? offset.x : offset.y;
		shortestOffset = abs(shortestOffset);
		if (shortestOffset == 0) {
			shortestOffset = 0.000001;
		}
		Vector2 collisionVector = collisionVectors[i];
		Reflect(collisionVector);
		position += collisionVector ;
		debugVecidx = i;
	}
}

