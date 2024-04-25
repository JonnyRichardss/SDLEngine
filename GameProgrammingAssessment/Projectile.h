#ifndef USE_PROJECTILE
#define USE_PROJECTILE
#include "GameObject.h"
class Projectile : public GameObject
{
public:
	Projectile(GameObject* _parent, std::string _name, float _speed, float _size, float lifetimeSeconds, float _damage);
	void Init();
	void InitVisuals();
protected:
	static int nextID;
	int ID;
	GameObject* parent;
	float speed;
	float damage;
	int lifetime;
	bool Update();
};
#endif // !USE_PROJECTILE


