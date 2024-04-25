#include "MeleeCollider.h"
#include "GameScene.h"
int MeleeCollider::currentID = 0;
MeleeCollider::MeleeCollider(GameObject* _parent,std::string _name,Vector2 _offset, int w, int h, float lifetimeSeconds,float _damage)
{
	parent = _parent;
	name = _name;
	offset = _offset;
	position = parent->GetPos() + offset;
	BoundingBox = Vector2(w, h);
	lifetime = FRAME_CAP * lifetimeSeconds;
	facing = parent->GetFacing();
	damage = _damage;
	ID = currentID++;
}

void MeleeCollider::Init()
{
	collisionTags.push_back("MeleeAttack");
	shown = false;
}

void MeleeCollider::InitVisuals()
{
	//no visuals
}

float MeleeCollider::GetDamage()
{
	return damage;
}

int MeleeCollider::GetID()
{
	//ID is used by the damage receiver to check if it has already taken damage from this attack
	return ID;
}

bool MeleeCollider::Update()
{
	//post-decrement accesses THEN decrements so if lifetime == 1 it will be alive this frame and gone the next
	//not likely to be important but it WILL register collision on the frame that it is destroyed since collision is in preupdate (for mainscene)
	if (lifetime-- <= 0) {
		//this very well may crash idk what happens if an object calls code that deletes it
		scene->DeregisterObject(this);
		return false;
	}
	//else exist
	position = parent->GetPos() + offset;
	return true;
}
