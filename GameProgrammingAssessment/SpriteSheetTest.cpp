#include "SpriteSheetTest.h"

void SpriteSheetTest::Init()
{
	shown = true;
	
}

void SpriteSheetTest::InitVisuals()
{
	BoundingBox = Vector2(30, 50);
	delete visuals;
	Sprites = new Spritesheet();
	visuals = Sprites;
	Sprites->InitSprites("Numbers", ".png");
	Sprites->UpdateLayer(100);
}

void SpriteSheetTest::NextSprite()
{
	int index = Sprites->GetSpriteIndex();
	if (index >= Sprites->GetSpriteIndexMax())
		Sprites->SetSpriteIndex(0);
	else
		Sprites->SetSpriteIndex(++index);
}

void SpriteSheetTest::Update()
{
}
