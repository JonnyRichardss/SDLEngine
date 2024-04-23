#include "TestCollider.h"
#include "GameRNG.h"
void TestCollider::Init()
{
	BoundingBox = Vector2(TEST_COLLIDER_SIZE);
	shown = true;
	is_static = false;
	facing = RNG::randf(0, 2 * M_PI);
	velocity = Vector2::zero();
	position = Vector2(RNG::randi(0, GAME_MAX_X * 2) - GAME_MAX_X, RNG::randi(0, GAME_MAX_Y * 2) - GAME_MAX_Y);
}

void TestCollider::InitVisuals()
{
	SetWhite();
	SDL_Rect DefaultRect = BBtoDestRect();
	visuals->UpdateDestPos(&DefaultRect);
}
//stolen from boid
void TestCollider::DoRotation()
{
	velocity = Vector2(sin(facing) * 2.0f, cos(facing) * 2.0f);
}

void TestCollider::ScreenWrap()
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
//D R Y but who tf cares tbh
void TestCollider::SetWhite()
{
	SDL_Surface* Surf = ColourRGBA::White().ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
}
void TestCollider::SetRed()
{
	SDL_Surface* Surf = ColourRGBA(255,0,0,255).ColouredSurface();
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

	SDL_FreeSurface(Surf);
	visuals->UpdateTexture(Tex);
}
void TestCollider::SetName(int num)
{
	name = "Box " + std::to_string(num);
}

void TestCollider::Update()
{
	ScreenWrap();
	DoRotation();
	if (colliders.empty()) {
		SetWhite();
		//SetRed();
	}
	else {
		SetRed();
	}
}
