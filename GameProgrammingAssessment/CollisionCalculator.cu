#include "CollisionCalculator.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Global_Flags.h"
#include "GameMath.h"
#include <math.h>
#include "GameLogging.h"
static int AllocSize = COLLISION_INIT_SIZE;

struct GameObjectCUDA {
	int id;
	/*
	* points MUST be fed as
	* (technically order doesnt matter but 0 and 3 must be opposite)
	0-------1
	|       |
	|       |
	2-------3
	*/
	float2 points[4];
	float2 centre;
	int colliders[MAX_COLLISIONS];
	unsigned int currentIdx = 0;
};
static GameObjectCUDA* objsGPU;
static bool allocated = false;
__device__ inline float dotProduct(float2 a, float2 b) {
	return (a.x * b.x) + (a.y * b.y);
}
__device__ inline float2 CalcNormalAxis(float2 p1, float2 p2) {
	//return -dy, dx
	float dy = p1.y - p2.y;
	float dx = p1.x - p2.x;
	float length = sqrtf(dx * dx + dy * dy);
	float2 axis = make_float2(dy / (length * -1), dx / length);
	return axis;
}
__device__ inline float2 MinMaxProjectionOnAxis(float2 points[4],float2 axis) {
	//https://textbooks.cs.ksu.edu/cis580/04-collisions/04-separating-axis-theorem/index.html
	//accessed 19/04/24
	//project each point
	//return min,max
	float projection = dotProduct(points[0],axis);
	float min = projection;
	float max = projection;
	for (int i = 1; i < 4; i++) {
		projection = dotProduct(points[i], axis);
		max = max > projection ? max : projection;
		min = min < projection ? min : projection;
	}
	return make_float2(min, max);
}
__device__ inline bool SATCheck(GameObjectCUDA* object, GameObjectCUDA* other) {
	//TRUE IS A COLLISION
	//Last step -- implement actual alg
	//we are assuming boxes so we only need up normal and right normal for both
	float2 normals[4];
	normals[0] = CalcNormalAxis(object->points[0], object->points[1]);
	normals[1] = CalcNormalAxis(object->points[1], object->points[3]);
	normals[2] = CalcNormalAxis(other->points[0], other->points[1]);
	normals[3] = CalcNormalAxis(other->points[1], other->points[3]);
	for (int i = 0; i < 4; i++) {
		float2 objectProjection = MinMaxProjectionOnAxis(object->points, normals[i]);
		float2 otherProjection = MinMaxProjectionOnAxis(other->points, normals[i]);
		if (objectProjection.x > otherProjection.y || otherProjection.x > objectProjection.y) {
			return false;
		}
	}
	return true;
}
__device__ inline float SqrDistance(float2 p1, float2 p2) {
	float2 offset = make_float2(p1.x - p2.x, p1.y - p2.y);
	return (offset.x * offset.x) + (offset.y * offset.y);
}
__device__ inline bool SphereCheck(GameObjectCUDA* object, GameObjectCUDA* other) {
	float SQRradius = fmaxf(SqrDistance(object->centre,object->points[0]), SqrDistance(other->centre,other->points[0]));

	return SqrDistance(object->centre, other->centre) < SQRradius;
}
__global__ void GPUCollisionCalc(GameObjectCUDA* objs, int size) {
	int i = blockIdx.x;
	if (i > size) return;//think this is never true but oh well
	for (int j = threadIdx.x; j < size; j += blockDim.x) {
		GameObjectCUDA* object = &objs[i];
		GameObjectCUDA* other = &objs[j];
		//TRUE IS A COLLISION
		//if (!SphereCheck(object, other)) //simple sphere check to see if they are in range of each other
		//	continue;
		//full SAT to see if they actually collide
		//if collision found add to j.id to colliders
		if (SATCheck(object, other)) {
			unsigned int index = atomicInc(&objs[i].currentIdx, (MAX_COLLISIONS));//atomic inc prevents race conditions - each thread *should* always have its own unique index to access
			
			objs[i].colliders[index] = objs[j].id;
		}
	}
}
void MakePoints(JRrect rect,GameObjectCUDA& output) {
	for (int i = 0; i < 4; i++) {
		output.points[i] = make_float2(rect.points[i].x, rect.points[i].y);
	}
}
void MakeStructs(GameObjectCUDA* output, std::vector<GameObject*>& input) {
	for (int i = 0; i < input.size(); i++) {
		//clear colliders from last frame
		input[i]->colliders.clear();
		output[i].id = i;
		Vector2 pos = input[i]->GetPos();
		output[i].centre = make_float2(pos.x,pos.y);
		MakePoints(input[i]->GetCorners(), output[i]);
		input[i]->colliders.clear();
	}
}
void UnMakeStructs(std::vector<GameObject*>& output, GameObjectCUDA* input) {
	for (int i = 0; i < output.size(); i++) {
		int idx = static_cast<int>(input[i].currentIdx);
		for (int j = 0; j < std::min(idx, (int)output.size()); j++) {
			if (i == input[i].colliders[j])
				continue;
			if (output[i] == nullptr) 
				continue;
			int outID = input[i].colliders[j];
			if (outID < 0 || outID >= output.size()) {
				//GameLogging::GetInstance()->Log("ERROR: Invalid ID for detected collider (objectID colliderID) " + std::to_string(i) + " " + std::to_string(outID));
				continue;
			}

			output[i]->colliders.push_back(output[outID]);
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
namespace JRCollision {
	void Init() {
		AllocCUDA(AllocSize);
	}
	void Free()
	{
		FreeCUDA();
	}
	void CalculateCollsion(std::vector<GameObject*>& UpdateQueue)
	{
		//make sure we have enough room on the GPU -- doing it this way prevents us from allocating every frame for different update queue sizes
		/*
		bool need_new_alloc = false;
		while (AllocSize < UpdateQueue.size()) {
			AllocSize += COLLISION_EXPAND_SIZE;
			need_new_alloc = true;
		}
		if (need_new_alloc || !allocated) {
			AllocCUDA(AllocSize);
		}
		*/
		AllocCUDA(UpdateQueue.size());
		GameObjectCUDA* objs = new GameObjectCUDA[UpdateQueue.size()];
		//copy to
		MakeStructs(objs, UpdateQueue);
		cudaMemcpy(objsGPU, objs, sizeof(GameObjectCUDA) * UpdateQueue.size(), cudaMemcpyHostToDevice);

		//exec
		GPUCollisionCalc << < UpdateQueue.size(), 1024 >> > (objsGPU, AllocSize);
		//copy from
		cudaMemcpy(objs, objsGPU, sizeof(GameObjectCUDA) * UpdateQueue.size(), cudaMemcpyDeviceToHost);
		UnMakeStructs(UpdateQueue, objs);
		//free
		delete[] objs;
		FreeCUDA();
	}
}