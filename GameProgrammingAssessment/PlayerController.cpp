#include "PlayerController.h"
#include "Timer.h"
#include "GameConductor.h"
#include "MeleeCollider.h"
#include "GameScene.h"
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
	name = "Player";
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	collisionTags.push_back("Player");
	shown = true;
	is_static = false;
	attack1 = false;
	attack2 = false;
	a1Timing = 0;
	a2Timing = 0;
	timer.Start();
	conductor = GameConductor::GetInstance();
}

void PlayerController::InitVisuals()
{
	visuals->LoadTexture("boid", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

bool PlayerController::Update()
{
	//grab inputs
	Vector2 MoveVector;//see i could have done this with IFs but this takes up less characters and is harder to understand which is obviously more important
	MoveVector.y += input->GetActionState(InputActions::UP);
	MoveVector.y -= input->GetActionState(InputActions::DOWN);
	MoveVector.x -= input->GetActionState(InputActions::LEFT);
	MoveVector.x += input->GetActionState(InputActions::RIGHT);
	//the attack bools are actually waiting flags so only update them if we are not waiting
	if (!attack1) {
		attack1 = input->GetActionState(InputActions::ATTACK1);
		a1Timing = input->GetActionTiming(InputActions::ATTACK1);
	}
	if (!attack2) {
		attack2 = input->GetActionState(InputActions::ATTACK2);
		a2Timing = input->GetActionTiming(InputActions::ATTACK2);
	}
	Vector2 mousePos = renderer->WindowToGameCoords(input->GetMousePos());
	
	Vector2 mouseDirection = position - mousePos;
	mouseDirection.y *= -1;//this is very odd - I'm 100% sure its something to do with windowToGameCoords but setting the pos directly worked so idk man
	float mouseDirFacing = Vector2::AngleBetweenRAD(Vector2::up(), mouseDirection.Normalise());
	//movement
	facing = mouseDirFacing;
	DoMovement(MoveVector);
	
	//attacks
	DoAttacks();
	//beat test
	if (conductor->PollBeat()) {
		ToggleColour();
		audio->PlaySound(0);
		
	}
	
	return true;
}
static bool is_red = false;
void PlayerController::ToggleColour() {
	SDL_Texture* Tex = visuals->GetTexture();
	if (is_red) {
		SDL_SetTextureColorMod(Tex, 255, 255, 255);
	}
	else {
		SDL_SetTextureColorMod(Tex, 255, 0, 0);
	}
	is_red = is_red ? false : true;

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

void PlayerController::DoAttacks()
{
	//alternative to measuring timing could just be to count the # of frames between the input being queued and actually being executed
	//this sounds like a better idea tbh
	if (conductor->PollBeat()) {
		if (attack1) {
			logging->DebugLog("Attack1  "+std::to_string(a1Timing));
			MeleeCollider* atk = new MeleeCollider(this, "Player Light Attack", TEST_COLLIDER_SIZE, 10, 10, 1, 0);
			scene->DeferredRegister(atk);
			attack1 = false;
		}
		if (attack2) {
			logging->DebugLog("Attack2  "+std::to_string(a2Timing));
			MeleeCollider* atk = new MeleeCollider(this, "Player Heavy Attack", TEST_COLLIDER_SIZE, 10, 20, 1, 0);
			scene->DeferredRegister(atk);
			attack2 = false;
		}
	}
}
