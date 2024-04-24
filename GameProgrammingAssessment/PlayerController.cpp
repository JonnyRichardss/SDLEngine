#include "PlayerController.h"
#include "Timer.h"
#include <chrono>
using namespace std::chrono_literals;
//technically these could go in global flags but they will require iterating and i dont want to recomp the whole project every time
static constexpr int maxSpeed = 10;
static constexpr float acceleration = 0.75;
static constexpr float deceleration = 0.5;
static Timer timer;
static GameConductor* conductor;
void PlayerController::Init()
{
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	shown = true;
	is_static = false;
	timer.Start();
	conductor = GameConductor::GetInstance();
}

void PlayerController::InitVisuals()
{

	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);

	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

void PlayerController::Update()
{
	Vector2 MoveVector;//see i could have done this with IFs but this takes up less characters and is harder to understand which is obviously more important
	MoveVector.y += input->GetActionState(InputActions::UP);
	MoveVector.y -= input->GetActionState(InputActions::DOWN);
	MoveVector.x -= input->GetActionState(InputActions::LEFT);
	MoveVector.x += input->GetActionState(InputActions::RIGHT);
	DoMovement(MoveVector);
	if (input->GetActionState(InputActions::ATTACK1)) {
		logging->DebugLog(std::to_string(input->GetActionTiming(InputActions::ATTACK1)));
	}
	if (input->GetActionState(InputActions::ATTACK2)) {
		logging->DebugLog(std::to_string(input->GetActionTiming(InputActions::ATTACK2)));
	}
	//logging->DebugLog(input->GetMousePos().ToString());
	position = renderer->WindowToGameCoords(input->GetMousePos());

}
void PlayerController::DoMovement(Vector2 MoveVector) {
	//not entirely happy with how this is but i *think* i can play with the consts tofix it

	//logging->DebugLog(MoveVector.ToString());
	//logging->DebugLog(std::to_string(MoveVector == Vector2::zero()));
	if (MoveVector != Vector2::zero()) {
		//accelerate
		velocity += MoveVector * acceleration;
		velocity = velocity.Clamp(maxSpeed);
	}
	else{
		//brake
		if (velocity.GetMagnitude() < 0.0001) {
			velocity = Vector2::zero();
		}
		else {
			velocity -= velocity * deceleration;
		}
	}
}
