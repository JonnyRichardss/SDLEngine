#ifndef USE_MELEEBOX
#define USE_MELEEBOX
#include "GameObject.h"
#include "Spritesheet.h"
class MeleeCollider : public GameObject
{
public:
	MeleeCollider(GameObject* _parent,std::string _name,float _offset, int w, int h,float lifetimeSeconds,float _damage,double _timing);
	void Init();
	void InitVisuals();
	GameObject* GetParent();
	float GetDamage();
	int GetID();
	double GetTiming();
protected:
	SpriteSheet* sprites;
	int spriteFrame;
	double timing;
	static int nextID;
	int ID;
	GameObject* parent;
	float offset;
	float damage;
	int lifetime;
	bool Update();
};
#endif // !USE_MELEEBOX


