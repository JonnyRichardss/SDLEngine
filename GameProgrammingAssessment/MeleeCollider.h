#ifndef USE_MELEEBOX
#define USE_MELEEBOX
#include "GameObject.h"
class MeleeCollider : public GameObject
{
public:
	MeleeCollider(GameObject* _parent,std::string _name,float _offset, int w, int h,float lifetimeSeconds,float _damage);
	void Init();
	void InitVisuals();
	float GetDamage();
	int GetID();
protected:
	static int nextID;
	int ID;
	GameObject* parent;
	float offset;
	float damage;
	int lifetime;
	bool Update();
};
#endif // !USE_MELEEBOX


