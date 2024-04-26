#include "EnemyController.h"
#include "MeleeCollider.h"
#include "Projectile.h"
EnemyController::EnemyController(GameObject* _target, EnemyTypes::Type _enemyType, Vector2 _pos)
{
	target = _target;
	type = _enemyType;
	position = _pos;
}
void EnemyController::Init()
{
	shown = true;
	BoundingBox = { 20,20 };
	collisionTags.push_back("Enemy");
	collisionTags.push_back("Solid");
	acceleration = 0.5;
	deceleration = 0.1;//relying on just base friction
	maxSpeed = ENEMY_SPEED;
	
	GoalPosition = target->GetPos();
}

void EnemyController::InitVisuals()
{
	visuals->LoadTexture("boid", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_SetTextureColorMod(Tex, 255, 0, 255);
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
	visuals->UpdateLayer(1);
}
static float stepwidth = 50;
bool EnemyController::Update()
{
	if (conductor->PollBeat()) {
		GoalPosition = target->GetPos();
		Vector2 offset = (GoalPosition - position);
		position += offset.Normalise() * stepwidth;
		facing = -Vector2::AngleBetweenRAD(Vector2::up(), offset);
	}
	//DoMovement(GoalPosition-position);
	//SolidCollision();
	CheckDamage();

	return true;
}
bool EnemyController::IsIDUsed(std::vector<int>& vec, int ID)
{
	for (int i : vec) {
		if (i == ID) return true;
	}
	return false;
}
void EnemyController::CheckDamage()
{
	CheckMeleeDamage();
	CheckProjectileDamage();
}

void EnemyController::CheckMeleeDamage()
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
		if (!(IsIDUsed(prevMelees, id))) {
			prevMelees.push_back(id);
			TakeDamage(collider->GetDamage());
		}
	}
}
void EnemyController::CheckProjectileDamage()
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

void EnemyController::TakeDamage(float damage)
{
	health -= damage;
	logging->DebugLog("Enemy damage taken - new health: " + std::to_string(health));
}
