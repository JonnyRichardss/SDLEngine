#include "PlayerController.h"
#include "Timer.h"
#include "GameConductor.h"
#include "MeleeCollider.h"
#include "Projectile.h"
#include "GameScene.h"
#include <chrono>
using namespace std::chrono_literals;
//technically these could go in global flags but they will require iterating and i dont want to recomp the whole project every time


static Timer timer;
void PlayerController::Init()
{
	position = Vector2(0, 100);
	name = "Player";
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	collisionTags.push_back("Player");
	collisionTags.push_back("Solid");
	shown = true;
	is_static = false;
	a1Used = a2Used = dashUsed = false;
	a1Timing = a2Timing = dashTiming = 0;

	acceleration = 1;
	deceleration = 0.25;
	
	maxSpeed = PLAYER_SPEED;
	timer.Start();
	
}

void PlayerController::InitVisuals()
{
	/*SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);*/
	
	visuals->LoadTexture("boid", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);

	visuals->UpdateLayer(10);
}

bool PlayerController::Update()
{
	Vector2 MoveVector;
	Vector2 mousePos;
	GetInput(MoveVector, mousePos);
	
	Vector2 mouseDirection = position - mousePos;
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
	CheckDamage();
	DecrementCooldowns();
	return true;
}
void PlayerController::GetInput(Vector2& MoveVector, Vector2& mousePos)
{
	MoveVector.y -= input->GetActionState(InputActions::UP);
	MoveVector.y += input->GetActionState(InputActions::DOWN);
	MoveVector.x -= input->GetActionState(InputActions::LEFT);
	MoveVector.x += input->GetActionState(InputActions::RIGHT);

	mousePos = renderer->WindowToGameCoords(input->GetMousePos());
	//only update actions if they are off cooldown
	if (a1CoolDown == 0) {
		a1Used = input->GetActionState(InputActions::ATTACK1);
		a1Timing = input->GetActionTiming(InputActions::ATTACK1);
	}
	if (a2CoolDown == 0) {
		a2Used = input->GetActionState(InputActions::ATTACK2);
		a2Timing = input->GetActionTiming(InputActions::ATTACK2);
	}
	if (dashCoolDown == 0) {
		dashUsed = input->GetActionState(InputActions::DASH);
		dashTiming = input->GetActionTiming(InputActions::DASH);
	}
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
bool PlayerController::IsIDUsed(std::vector<int>& vec, int ID)
{
	for (int i : vec) {
		if (i == ID) return true;
	}
	return false;
}


void PlayerController::DoAttacks()
{

	if (a1Used) {
		logging->DebugLog("Attack1  " + std::to_string(a1Timing));
		MeleeCollider* atk = new MeleeCollider(this, "Player Light Attack", TEST_COLLIDER_SIZE, 30, 10, 0.2, 0);
		scene->DeferredRegister(atk);
		a1Used = false;
		a1CoolDown = (1 * MS_PER_BEAT)/1100;
	}
	if (a2Used) {
		logging->DebugLog("Attack2  " + std::to_string(a2Timing));
		Projectile* atk = new Projectile(this, "Player Projectile", 3, TEST_COLLIDER_SIZE, 5, 0);
		scene->DeferredRegister(atk);
		a2Used = false;
		a2CoolDown = (1 *  MS_PER_BEAT)/1100;
	}
	if (dashUsed) {
		logging->DebugLog("Dash!");
		position += velocity.Normalise() * DASH_DISTANCE;
		audio->PlaySound(1);
		dashUsed = false;
		dashCoolDown = (1 * MS_PER_BEAT)/1200;
	}
}

void PlayerController::DecrementCooldowns()
{
	DecrementCooldown(a1CoolDown);
	DecrementCooldown(a2CoolDown);
	DecrementCooldown(dashCoolDown);
}
static int frame = 0;
void PlayerController::DecrementCooldown(float& cooldown)
{
 	frame++;
	if (cooldown < ((float)1 / FRAME_CAP)) {
		cooldown = 0;
		return;
	}
	double elapsedsecs = clock->GetFrametime().count() / (float)1000000000;
	cooldown -= elapsedsecs;
}

void PlayerController::CheckDamage()
{
	CheckMeleeDamage();
	CheckProjectileDamage();
}

void PlayerController::CheckMeleeDamage()
{
	if (colliders.empty()) return;
	for (GameObject* c : colliders) {
		if (!(c->CompareTag("MeleeAttack")) || c == this) continue;
		MeleeCollider* collider = dynamic_cast<MeleeCollider*>(c);
		if (c == nullptr) {
			logging->Log("Tried to cast non-meleeattack to meleeattack!");
			continue;
		}
		if (collider->GetParent() == this) continue;
		int id = collider->GetID();
		if (!(IsIDUsed(prevMelees,id))) {
			prevMelees.push_back(id);
			TakeDamage(collider->GetDamage());
		}
	}
}
void PlayerController::CheckProjectileDamage()
{
	if (colliders.empty()) return;
	for (GameObject* c : colliders) {
		if (!(c->CompareTag("Projectile")) || c == this) continue;
		Projectile* collider = dynamic_cast<Projectile*>(c);
		if (c == nullptr) {
			logging->Log("Tried to cast non-projectile to projectile!");
			continue;
		}
		if (collider->GetParent() == this) continue;
		int id = collider->GetID();
		if (!(IsIDUsed(prevProjectiles, id))) {
			prevProjectiles.push_back(id);
			TakeDamage(collider->GetDamage());
			collider->HasHit();
		}
	}
}
void PlayerController::TakeDamage(float damage)
{
	health -= damage;
	logging->DebugLog("Player damage taken - new health: " + std::to_string(health));
}
