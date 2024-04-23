#include "PlayerController.h"

void PlayerController::Init()
{
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	shown = true;
	is_static = false;
}

void PlayerController::InitVisuals()
{

	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);

	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}

void PlayerController::Update()
{
	if (input->GetActionState(InputActions::UP)) {
		//dostuff
	}
}
