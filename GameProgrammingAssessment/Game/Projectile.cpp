#include "Projectile.h"
#include "GameScene.h"
int Projectile::nextID = 0;
Projectile::Projectile(GameObject* _parent, std::string _name, float _speed, float size, float lifetimeSeconds, float _damage,double _timing)
{
	parent = _parent;
	name = _name;
	speed = _speed;
	facing = parent->GetFacing();
	velocity = Vector2::RotateAroundOrigin(Vector2::up(), facing);
	velocity *= -1;
	position = parent->GetPos() + velocity * (parent->GetBB().x);
	BoundingBox = Vector2(size);
	velocity *= speed;
	lifetime = FRAME_CAP * lifetimeSeconds;
	damage = _damage;
	ID = nextID++;
	if (_timing > MS_PER_BEAT / 2.0) {
		_timing = MS_PER_BEAT - _timing;
	}
	timing = _timing;
}

void Projectile::Init()
{
	shown = true;
	is_static = false;
	alive = true;
	has_friction = false;
	collisionTags.push_back("Projectile");
}

void Projectile::InitVisuals()
{
	spriteFrame = false;
	delete visuals;
	sprites = new SpriteSheet();
	visuals = sprites;
	sprites->InitSprites("Projectile", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

bool Projectile::IsAlive()
{
	return alive;
}

void Projectile::HasHit()
{
	alive = false;
}

GameObject* Projectile::GetParent()
{
	return parent;
}

float Projectile::GetDamage()
{
	return damage;
}

double Projectile::GetTiming()
{
	return timing;
}

int Projectile::GetID()
{
	return ID;
}

bool Projectile::Update()
{
	if (lifetime-- <= 0 || !alive) {
		//this very well may crash idk what happens if an object calls code that deletes it
		scene->DeferredDeregister(this);
		return false;
	}
	if (conductor->PollBeat()) {
		spriteFrame = spriteFrame ? false : true;
		sprites->SetSpriteIndex(spriteFrame);
	}
	return true;
}
