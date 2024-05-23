#ifndef  USE_COLLISION
#define USE_COLLISION
#include <vector>
#include "GameObject.h"
namespace JRCollision {
	void Init();
	void Free();
	void CalculateCollsion(std::vector<GameObject*>& UpdateQueue);
}
#endif // ! USE_COLLISION

