#ifndef USE_BOID
#define USE_BOID
#include "GameObject.h"
class BoidScene; //fwd def

class Boid : public GameObject
{
public:
	void Init();
	void InitVisuals();
	void SetOwner(BoidScene* owner);
	std::vector<Boid*> Neighbours;
protected:
	Vector2 steerTarget;
	void DoSeparation(Vector2 vec);
	void DoAlignment(Vector2 vec);
	void DoCohesion(Vector2 vec);
	int numNeighbours = 0;
	void Update();
	void DoRotation();
	void ScreenWrap();
	void CalcTarget();
	void SteerTowards(Vector2 target);

	BoidScene* manager;
};
namespace JRCudaCalc {
	void GetNeighboursCUDA(std::vector<GameObject*>& AllBoids);
	void Init(int size);
	void Clear();
}
#endif // !USE_BOID

