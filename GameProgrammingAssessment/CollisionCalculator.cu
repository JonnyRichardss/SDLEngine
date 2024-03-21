#include "CollisionCalculator.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Global_Flags.h"
static int ArraySize = COLLISION_INIT_SIZE;
struct GameObjectCUDA {
	float2 points[4];
};





void CalculateCollsion(std::vector<GameObject*>& UpdateQueue)
{
	while (ArraySize > UpdateQueue.size()) {
		ArraySize += COLLISION_EXPAND_SIZE;
	}

}