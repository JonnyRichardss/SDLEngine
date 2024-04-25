#include "EnemyController.h"

void EnemyController::Init()
{
}

void EnemyController::InitVisuals()
{
	visuals->LoadTexture("boid", ".png");
	SDL_Texture* Tex = visuals->GetTexture();
	SDL_SetTextureColorMod(Tex, 255, 0, 255);
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

bool EnemyController::Update()
{


	return true;
}
