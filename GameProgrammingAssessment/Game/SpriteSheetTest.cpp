#include "SpriteSheetTest.h"

void SpriteSheetTest::Init()
{
	shown = true;
	name = "Sprite Sheet tester";
	
}

void SpriteSheetTest::InitVisuals()
{
	BoundingBox = Vector2(30, 50);
	delete visuals;
	Sprites = new SpriteSheet();
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

bool SpriteSheetTest::Update()
{
	return true;
}
