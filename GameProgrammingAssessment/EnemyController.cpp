#include "EnemyController.h"
#include "MeleeCollider.h"
#include "Projectile.h"
#include "GameScene.h"
#include "PlayerController.h"
EnemyController::EnemyController(GameObject* _player, Vector2 _pos)
{
	name = "enemy";
	position = _pos;
	alive = true;
	player = dynamic_cast<PlayerController*>(_player);
	if (player == nullptr) {
		logging->Log("Enemy Given non-player reference for player!");
		alive = false;
	}
}
void EnemyController::Init()
{
	shown = true;
	BoundingBox = { 20,20 };
	collisionTags.push_back("Enemy");
	collisionTags.push_back("Solid");
	stepwidth = ENEMY_STEP_WIDTH;
	GoalPosition = player->GetPos();
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

bool EnemyController::Update()
{
	if (conductor->PollBeat()) {
		GoalPosition = player->GetPos();
		Vector2 offset = (GoalPosition - position);
		position += offset.Normalise() * stepwidth;
		facing = -Vector2::AngleBetweenRAD(Vector2::up(), offset);
	}
	//DoMovement(GoalPosition-position);
	//SolidCollision();
	CheckDamage();
	DeathCheck();
	return alive;
}
bool EnemyController::IsIDUsed(std::vector<int>& vec, int ID)
{
	for (int i : vec) {
		if (i == ID) return true;
	}
	return false;
}
void EnemyController::DeathCheck()
{
	if (!alive) {
		scene->DeferredDeregister(this);
	}
}
void EnemyController::CheckDamage()
{
	CheckMeleeDamage();
	if (!alive) return; //early return so projectiles dont hit bodies
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
			AddScore(collider);
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
			AddScore(collider);
			collider->HasHit();
		}
	}
}

void EnemyController::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0) alive = false;//die
	logging->DebugLog("Enemy damage taken - new health: " + std::to_string(health));
}

void EnemyController::AddScore(MeleeCollider* collider)
{
	AddScore(collider->GetDamage(), collider->GetTiming());
}

void EnemyController::AddScore(Projectile* collider)
{
	AddScore(collider->GetDamage(), collider->GetTiming());
}

void EnemyController::AddScore(float damage, double timing)
{
	double ScoreMult = MS_PER_BEAT / (4.0 * timing);
	player->AddScore(ScoreMult * damage);
}
