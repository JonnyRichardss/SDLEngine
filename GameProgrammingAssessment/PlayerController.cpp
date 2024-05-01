#include "PlayerController.h"
#include "Timer.h"
#include "GameConductor.h"
#include "MeleeCollider.h"
#include "Projectile.h"
#include "GameScene.h"
#include "IntegerDisplay.h"
#include <chrono>
using namespace std::chrono_literals;
//technically these could go in global flags but they will require iterating and i dont want to recomp the whole project every time



void PlayerController::Init()
{
	
	alive = true;
	position = Vector2(0, 100);
	name = "Player";
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	collisionTags.push_back("Player");
	collisionTags.push_back("Solid");
	shown = true;
	is_static = false;
	a1Scheduled = a2Scheduled = dashScheduled = false;
	a1Timing = a2Timing = dashTiming = 0;
	a1Combo = a2Combo = dashCombo = 0;
	acceleration = 1;
	deceleration = 0.25;
	maxSpeed = PLAYER_SPEED;
	score = new IntegerDisplay(Vector2(SCORE_POS_X, SCORE_POS_Y),"Score", SCORE_FONT_PATH, SCORE_FONT_PTSIZE);
	score->SetValue(0);
	scene->DeferredRegister(score);
	
}

void PlayerController::InitVisuals()
{
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
	Vector2 mouseDirection = position - mousePos;
	float mouseDirFacing = Vector2::AngleBetweenRAD(Vector2::up(), mouseDirection.Normalise());
	GetInput(MoveVector, mousePos);
	
	//movement
	facing = mouseDirFacing;
	DoMovement(MoveVector);

	//actions for on beat
	if (conductor->PollBeat()) {
		offBeatPassed = false;
		logging->DebugLog(std::to_string(conductor->GetBeat()));
		ToggleColour();
		audio->PlaySound(0);
		DoBeatAttacks();
	}
	else if (conductor->GetInputTiming() > MS_PER_BEAT * ((TIMING_LENIENCY - 1) / TIMING_LENIENCY) && !offBeatPassed) {
		ResetCombos();
		offBeatPassed = true;
	}

	CheckDamage();
	DeathCheck();
	return true;
}
void PlayerController::GetInput(Vector2& MoveVector, Vector2& mousePos)
{
	MoveVector.y -= input->GetActionState(InputActions::UP);
	MoveVector.y += input->GetActionState(InputActions::DOWN);
	MoveVector.x -= input->GetActionState(InputActions::LEFT);
	MoveVector.x += input->GetActionState(InputActions::RIGHT);

	mousePos = renderer->WindowToGameCoords(input->GetMousePos());

	ActionInput(InputActions::ATTACK1, a1Scheduled,a1Used, a1Timing,a1Combo,ATTACK1_COMBO_LENGTH);
	ActionInput(InputActions::ATTACK2, a2Scheduled, a2Used, a2Timing,a2Combo,ATTACK2_COMBO_LENGTH);
	ActionInput(InputActions::DASH, dashScheduled, dashUsed, dashTiming,dashCombo,DASH_COMBO_LENGTH);
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


void PlayerController::DoBeatAttacks()
{
	//actions negate their own schedule bools so they can run across multiple beats if they need to
	if (a1Scheduled) {
		
		DoAttack1();
	}
	if (a2Scheduled) {
		
		DoAttack2();
	}
	if (dashScheduled) {
		
		DoDash();
	}
}

void PlayerController::ActionInput(InputActions::Action action, bool& scheduled,bool& used, double& timing,int& comboCounter,int maxCombo)
{
	bool inputUsed = input->GetActionState(action);
	if (!inputUsed) return;

	if (comboCounter >= 0 && comboCounter < maxCombo) {
		if (scheduled) {
			logging->DebugLog("Action already scheduled! Skipping!");
			return;
		}
		timing = input->GetActionTiming(action);
		if (conductor->PollBeat()) {
			logging->DebugLog("Action perfectly timed! Scheduling for this beat!");
			scheduled = true;
		}
		else if (timing > MS_PER_BEAT * ((TIMING_LENIENCY - 1) / TIMING_LENIENCY)) {
			logging->DebugLog("Action early! Scheduling for next beat!");
			scheduled = true;
		}
		else if (timing < MS_PER_BEAT / TIMING_LENIENCY) {
			if (!used) {
				logging->DebugLog("Action late! Performing immediately!");
				DoAction(action);
			}
			else {
				logging->DebugLog("Duplicate late action for beat! Skipping!");
			}
		}
		else {
			logging->DebugLog("Action out of time! Cancelling!");
		}
	}
	else {
		logging->DebugLog("Action combo expired! Skipping!");
	}

}

void PlayerController::DoAction(InputActions::Action action)
{
	switch (action) {
	case (InputActions::ATTACK1):
		DoAttack1();
		break;
	case (InputActions::ATTACK2):
		DoAttack2();
		break;
	case (InputActions::DASH):
		DoDash();
		break;
	default:
		logging->Log("Invalid action passed to AttackInput()!");
		break;
	}
}

void PlayerController::DoDash()
{
	logging->DebugLog("Dash! Combo: "+std::to_string(dashCombo));
	position += velocity.Normalise() * DASH_DISTANCE;
	audio->PlaySound(1);
	dashScheduled = false;
	dashUsed = true;
	dashCombo++;
}
//whats happening is the attack is landing
//being registered as late on the same beat
//so then a1Beats == 1 on the next beat
//we need bloody cooldowns back
//well think about how to add combos first
constexpr static int comboIdx = 3;
void PlayerController::DoAttack1()
{
	switch (a1Beats) {
		case 0:
			audio->PlaySound(comboIdx+a1Combo);
			logging->DebugLog("Attack1 used! Combo: " + std::to_string(a1Combo));
			a1Scheduled = true;
			a1Used = true;
			a1Beats++;
			return;
		case 1:
			logging->DebugLog("Attack1 landing!");
			{	MeleeCollider* atk = new MeleeCollider(this, "Player Light Attack", TEST_COLLIDER_SIZE, 90, 40, 0.2, 10);
				scene->DeferredRegister(atk); }
			a1Scheduled = false;
			audio->PlaySound(2);
			a1Beats = 0;
			a1Combo++;
			return;
		default:
			logging->Log("Invalid value of a1Beats found!");
			return;
	}	
}
void PlayerController::DoAttack2() {
	a2Used = true;
	logging->DebugLog("Attack2  " + std::to_string(a2Timing));
	Projectile* atk2 = new Projectile(this, "Player Projectile", 3, TEST_COLLIDER_SIZE, 5, 0);
	scene->DeferredRegister(atk2);
	a2Scheduled = false;
	audio->PlaySound(2);
}
void PlayerController::DeathCheck()
{
	if (!alive) {
		//dostuff
	}
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
void PlayerController::ResetCombos()
{
	ResetSingleCombo(a1Used, a1Combo, ATTACK1_COMBO_COOLDOWN, ATTACK1_COMBO_LENGTH);
	ResetSingleCombo(a2Used, a2Combo, ATTACK2_COMBO_COOLDOWN, ATTACK2_COMBO_LENGTH);
	ResetSingleCombo(dashUsed, dashCombo, DASH_COMBO_COOLDOWN, DASH_COMBO_LENGTH);
}

void PlayerController::ResetSingleCombo(bool& used, int& combo, int cooldown, int max) {
	if (combo >= max) {
		combo = 0 - cooldown;
	}
	if (combo < 0) {
		combo++;
	}
	if (combo >0 && !used) {
		combo = -1;
	}
	used = false;
}
void PlayerController::TakeDamage(float damage)
{
	health -= damage;
	logging->DebugLog("Player damage taken - new health: " + std::to_string(health));
}
