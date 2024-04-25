#include "Projectile.h"
#include "GameScene.h"
int Projectile::nextID = 0;
Projectile::Projectile(GameObject* _parent, std::string _name, float _speed, float size, float lifetimeSeconds, float _damage)
{
	parent = _parent;
	name = _name;
	speed = _speed;
	facing = parent->GetFacing();
	velocity = Vector2::RotateAroundOrigin(Vector2::up(), facing);
	position = parent->GetPos() + velocity * (parent->GetBB().x);
	BoundingBox = Vector2(size);
	velocity *= speed;
	lifetime = FRAME_CAP * lifetimeSeconds;
	damage = _damage;
}

void Projectile::Init()
{
}

void Projectile::InitVisuals()
{
	visuals->LoadTexture("Projectile", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

bool Projectile::Update()
{
	if (lifetime-- <= 0) {
		//this very well may crash idk what happens if an object calls code that deletes it
		scene->DeferredDeregister(this);
		return false;
	}
	return true;
}
