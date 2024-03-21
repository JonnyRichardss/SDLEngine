#include "CollisionCalculator.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Global_Flags.h"
#include "GameMath.h"
#include <math.h>
static int AllocSize = COLLISION_INIT_SIZE;

struct GameObjectCUDA {
	int id;
	float2 points[4];
	int colliders[MAX_COLLISIONS];
	unsigned int currentIdx = 0;
};
static GameObjectCUDA* objsGPU;
static bool allocated = false;
__global__ void GPUCollisionCalc(GameObjectCUDA* objs, int size) {
	int i = blockIdx.x;
	if (i > size) return;//think this is never true but oh well
	for (int j = threadIdx.x; j < size; j += blockDim.x) {
		//do SAT
		//if collision found add to j.id to colliders
		//currentIDx++
	}
}
void MakePoints(JRrect rect,GameObjectCUDA& output) {
	for (int i = 0; i < 4; i++) {
		output.points[i] = make_float2(rect.points[i].x, rect.points[i].y);
	}
}
void MakeStructs(GameObjectCUDA* output, std::vector<GameObject*> input) {
	for (int i = 0; i < input.size(); i++) {
		output[i].id = i;
		MakePoints(input[i]->GetCorners(), output[i]);
		input[i]->colliders.clear();
	}
}
void UnMakeStructs(std::vector<GameObject*> output, GameObjectCUDA* input) {
	for (int i = 0; i < output.size(); i++) {
		int idx = static_cast<int>(input[i].currentIdx);
		for (int j = 0; j < std::min(idx, (int)output.size()); j++) {
			if (i == input[i].colliders[j])continue;
			if (output[i] == nullptr) continue;
			output[i]->colliders.push_back(output[input[i].colliders[j]]);
		}
	}
}
void FreeCUDA() {
	if (allocated)
		cudaFree(objsGPU);
	allocated = false;
}
void AllocCUDA(int size) {
	if (allocated)
		FreeCUDA();
	cudaMalloc((void**)&objsGPU, sizeof(GameObjectCUDA) * size);
	allocated = true;
}

void CalculateCollsion(std::vector<GameObject*>& UpdateQueue)
{
	bool need_new_alloc = false;
	while (AllocSize > UpdateQueue.size()) {
		AllocSize += COLLISION_EXPAND_SIZE;
		need_new_alloc = true;
	}
	if (need_new_alloc) {
		AllocCUDA(AllocSize);
	}
	GameObjectCUDA* objs = new GameObjectCUDA[UpdateQueue.size()];
}