#include "Boid.cuh"
#include "SDL.h"
#include "SDL_image.h"
#include "GameRNG.h"
#include "BoidScene.h"
#include <math.h>


//boids consts
static constexpr float BOID_SIZE = 10.0f;
static constexpr float BOID_SPEED = 4.0f;

static constexpr int NEIGHBOUR_STORAGE_DIV = 1; //divisor to reduce size of neighbour array - deemed unnecessary as it *appears* that memcpy has O(1) like performance (maybe not but at a glance there is no benefit to copying less data at this scale)
static constexpr float BOID_VISION_DISTANCE = 45.0f;
static constexpr float BOID_AVOID_DISTANCE = BOID_VISION_DISTANCE;// will try change later
static constexpr float BOID_VISION_ANGLE = 3.141592653589;
static constexpr float BOID_STEER_MULTIPLIER = 0.07f;
static constexpr float BOID_SEPARATION_STRENGTH = 1.0f;
static constexpr float BOID_ALIGNMENT_STRENGTH = 0.3f;
static constexpr float BOID_COHESION_STRENGTH = 1.0f;
static constexpr float RAND_WALK_SIZE_RAD = 0.05f;
void Boid::Init()
{
	BoundingBox = Vector2(BOID_SIZE, BOID_SIZE * 2);
	shown = true;
	facing = RNG::randf(0, 2 * M_PI);
	velocity = Vector2::zero();
	position = Vector2(RNG::randi(0, GAME_MAX_X * 2) - GAME_MAX_X, RNG::randi(0, GAME_MAX_Y * 2) - GAME_MAX_Y); //maybe ill eventually fix my random functions to behave with -ve values
	DoRotation();
	steerTarget = Vector2::zero();
}
void Boid::SetOwner(BoidScene* owner){
	manager = owner;
	GameScene* newPtr = dynamic_cast<GameScene*>(owner);
	if (newPtr != nullptr)
		GameObject::SetOwner(newPtr);
}
void Boid::SetName(int num)
{
	name = "Boid " + std::to_string(num);
}
void Boid::InitVisuals()
{
	visuals->LoadTexture("boid", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_SetTextureColorMod(Tex, RNG::randi(0, 0), RNG::randi(0, 128), RNG::randi(128, 255));
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);

}

void Boid::Update()
{
	numNeighbours = Neighbours.size();
	steerTarget = Vector2::zero();
	CalcTarget();
	SteerTowards(steerTarget);
	ScreenWrap();
	DoRotation();
	Neighbours.clear();
}

void Boid::DoRotation()
{
	velocity = Vector2(sin(facing) * BOID_SPEED, cos(facing) * BOID_SPEED);
}

void Boid::ScreenWrap()
{
	if (position.x > GAME_MAX_X) {
		position.x = -GAME_MAX_X;
	}
	else if (position.x < -GAME_MAX_X) {
		position.x = GAME_MAX_X;
	}
	if (position.y > GAME_MAX_Y) {
		position.y = -GAME_MAX_Y;
	}
	else if (position.y < -GAME_MAX_Y) {
		position.y = GAME_MAX_Y;
	}
}

void Boid::CalcTarget()
{
	Vector2 aligVec = Vector2::zero();
	Vector2 sepVec = Vector2::zero();
	Vector2 cohesVec = Vector2::zero();
	for (Boid* b : Neighbours) {

		aligVec -= b->GetVelo();
		cohesVec += b->GetPos();
		sepVec -= (position - b->position);
	}
	DoSeparation(sepVec);
	DoAlignment(aligVec);
	DoCohesion(cohesVec);

}

void Boid::SteerTowards(Vector2 target)
{
	facing += Vector2::AngleBetweenRAD(velocity, target) * BOID_STEER_MULTIPLIER;
	facing += (RNG::randf(0, RAND_WALK_SIZE_RAD * 2) - RAND_WALK_SIZE_RAD);
	//actually steer in velocity thanks


}
void Boid::DoSeparation(Vector2 vec)
{
	if (numNeighbours == 0)
		return;
	vec *= (1.0 / numNeighbours);
	vec *= BOID_SEPARATION_STRENGTH;
	steerTarget += vec;
}
void Boid::DoAlignment(Vector2 vec)
{
	if (numNeighbours == 0)
		return;
	vec = vec.Normalise();
	vec *= BOID_ALIGNMENT_STRENGTH;
	steerTarget += vec;
}
void Boid::DoCohesion(Vector2 vec)
{
	if (numNeighbours == 0)
		return;
	vec *= (1.0 / numNeighbours);
	vec = position - vec;
	vec *= BOID_COHESION_STRENGTH;
	steerTarget += vec;
}

namespace JRCudaCalc {
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
	constexpr int NUMBLOCKS = NUM_BOIDS;
	constexpr int NUMTHREADS = 1024;
	struct CudaNeighbourStruct {
		int id;
		float2 position;
		int neighbours[NUM_BOIDS];
		//int neighbours[1024];
		unsigned int currentIdx = 0;
	};
	//(as from my previous AMP code) most of this adapted from
	//https://github.com/SebLague/Boids/blob/master/Assets/Scripts/BoidCompute.compute
	//not anymore but *some* basics of the way it's calculated on the CPU are
	__global__ void GPUNeighbourCalc(CudaNeighbourStruct* boids, int size, float sqrVisDist) {
		int itest = blockIdx.x;

		if (itest > size) return;//think this is never true but oh well
		for (int jtest = threadIdx.x; jtest < size; jtest += blockDim.x) {
			float2 offset = make_float2(boids[itest].position.x - boids[jtest].position.x, boids[itest].position.y - boids[jtest].position.y);
			float sqrDist = offset.x * offset.x + offset.y * offset.y;
			if (sqrDist < sqrVisDist) {
				unsigned int index = atomicInc(&boids[itest].currentIdx, (NUM_BOIDS));
				boids[itest].neighbours[index] = boids[jtest].id;
			}
		}
	}
	void MakeNeighbourStructs(CudaNeighbourStruct* output, std::vector<GameObject*>& input) {
		int size = input.size();
		for (int i = 0; i < size; i++) {
			Boid* boidPtr = dynamic_cast<Boid*>(input[i]);
			if (boidPtr == nullptr) continue;
			Vector2 position = boidPtr->GetPos();
			output[i].id = i;
			output[i].position = make_float2(position.x, position.y);
		}
	}
	void UnMakeNeighbourStructs(std::vector<GameObject*>& output, CudaNeighbourStruct* input) {
		int size = output.size();
		for (int i = 0; i < size; i++) {
			Boid* iBoidPtr = dynamic_cast<Boid*>(output[i]);
			if (iBoidPtr == nullptr) continue;
			int idx = static_cast<int>(input[i].currentIdx);
			for (int j = 0; j < std::min(idx, NUM_BOIDS); j++) {
				if (i == input[i].neighbours[j])continue;
				Boid* jBoidPtr = dynamic_cast<Boid*>(output[input[i].neighbours[j]]);
				if (jBoidPtr == nullptr) continue;
				iBoidPtr->Neighbours.push_back(jBoidPtr);
			}
		}
	}
	static CudaNeighbourStruct* gpuBoids;
	static size_t arraySize;
	void GetNeighboursCUDA(std::vector<GameObject*>& AllBoids)
	{
		//GameLogging::GetInstance()->DebugLog("OI");
		int size = AllBoids.size();
		CudaNeighbourStruct* boids = new CudaNeighbourStruct[size];
		MakeNeighbourStructs(boids, AllBoids);
		//allocate and copy
		//CudaBoidStruct* gpuBoids;

		cudaMemcpy(gpuBoids, boids, arraySize, cudaMemcpyHostToDevice);
		//do calc
		float sqrVisDist = BOID_VISION_DISTANCE * BOID_VISION_DISTANCE;
		float sqrAvoidDist = BOID_AVOID_DISTANCE * BOID_AVOID_DISTANCE;
		GPUNeighbourCalc << <NUMBLOCKS, NUMTHREADS >> > (gpuBoids, size, sqrVisDist);
		//copy back
		cudaMemcpy(boids, gpuBoids, arraySize, cudaMemcpyDeviceToHost);
		UnMakeNeighbourStructs(AllBoids, boids);
		//free all

		delete[] boids;
	}
	void Alloc(int size) {
		arraySize = sizeof(CudaNeighbourStruct) * size;
		cudaMalloc((void**)&gpuBoids, arraySize);
	}
	void Free() {
		cudaFree(gpuBoids);
	}

}


