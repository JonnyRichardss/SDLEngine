#ifndef USE_PROJECTILE
#define USE_PROJECTILE
#include "GameObject.h"
#include "Spritesheet.h"
class Projectile : public GameObject
{
public:
	Projectile(GameObject* _parent, std::string _name, float _speed, float _size, float lifetimeSeconds, float _damage,double _timing);
	void Init();
	void InitVisuals();
	bool IsAlive();
	void HasHit();
	GameObject* GetParent();
	float GetDamage();
	double GetTiming();
	int GetID();
protected:
	SpriteSheet* sprites;
	bool spriteFrame;
	bool alive;
	static int nextID;
	int ID;
	double timing;
	GameObject* parent;
	float speed;
	float damage;
	int lifetime;
	bool Update();
};
#endif // !USE_PROJECTILE


