#include "EshopAnim.h"
#include "GameMath.h"
void EshopAnim::Init()
{
	shown = true;
	is_static = true;
	name = "Eshop Animation";
	
}

void EshopAnim::Update()
{
	GetWindowParams();
	MoveName();
	UpdateColours();
	Animate();
}
void EshopAnim::InitVisuals()
{
	CreateNameText();
	MoveName();
	//make two coloured textures
	SDL_Surface* leftSurf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
	SDL_Surface* rightSurf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	SDL_FillRect(leftSurf, NULL, leftInit.MapFromColour(leftSurf->format));
	SDL_FillRect(rightSurf, NULL, rightInit.MapFromColour(rightSurf->format));
	//make textures
	SDL_Texture* leftTex = SDL_CreateTextureFromSurface(renderContext, leftSurf);
	SDL_Texture* rightTex = SDL_CreateTextureFromSurface(renderContext, rightSurf);
	//surfs no longer needed
	SDL_FreeSurface(leftSurf);
	SDL_FreeSurface(rightSurf);
	//rect to construct renderableComponents
	SDL_Rect blankRect = { 0,0,0,0 };
	//make renderableComponents
	for (int i = 0; i < numBars; i++) {
		lefts.push_back(new RenderableComponent(leftTex, new SDL_Rect(blankRect)));
		rights.push_back(new RenderableComponent(rightTex, new SDL_Rect(blankRect)));
	}
	UpdateColours();
}
void EshopAnim::MoveName() {

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	SDL_Rect nameLocation = { 0, windowHeight - ptsize, 25 * (myName.length() + 1),ptsize }; 
	visuals->UpdateDestPos(&nameLocation);

}

void EshopAnim::UpdateColours()
{
	float lerpFactor = (clock->GetFrameCount() % colourPeriod) / (float)colourPeriod;
	if (lerpFactor == 1 || lerpFactor == 0)
		reverseColour = reverseColour ? false : true;//learning to use ternary operator - its pretty cool
	//make two coloured textures
	SDL_Surface* leftSurf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
	SDL_Surface* rightSurf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	SDL_FillRect(leftSurf, NULL, ColourRGBA::ColourLerp(reverseColour ? leftInit : leftFinal, reverseColour ? leftFinal : leftInit, lerpFactor).MapFromColour(leftSurf->format));
	SDL_FillRect(rightSurf, NULL, ColourRGBA::ColourLerp(reverseColour ? rightInit : rightFinal, reverseColour ? rightFinal : rightInit, lerpFactor).MapFromColour(rightSurf->format));
	//make textures
	SDL_Texture* leftTex = SDL_CreateTextureFromSurface(renderContext, leftSurf);
	SDL_Texture* rightTex = SDL_CreateTextureFromSurface(renderContext, rightSurf);
	//surfs no longer needed
	SDL_FreeSurface(leftSurf);
	SDL_FreeSurface(rightSurf);
	//rect to construct renderableComponents
	SDL_Rect blankRect = { 0,0,0,0 };
	//make renderableComponents
	for (int i = 0; i < numBars; i++) {
		
		lefts[i]->UpdateTexture(leftTex);
		rights[i]->UpdateTexture(rightTex);
	}
}
void EshopAnim::Animate()
{
	//reverseAnim = true;
	//float lerpFactor = 0.333;
	float lerpFactor = (clock->GetFrameCount() % movePeriod) / (float)movePeriod;
	if (lerpFactor ==1 || lerpFactor == 0) 
		reverseAnim = reverseAnim ? false : true;//learning to use ternary operator - its pretty cool

	int barHeight = windowHeight / numBars;
	int targetSpot = reverseAnim ?  windowWidth * 2  : (0- windowWidth * 2);
	int initSpot = reverseAnim ? 0 : windowWidth;
	for (int i = 0; i < numBars; i++) {
		SDL_Rect* leftRect = lefts[i]->GetDestPos();
		SDL_Rect* rightRect = rights[i]->GetDestPos();
		leftRect->y = i * barHeight;
		leftRect->h = barHeight;
		rightRect->y = i * barHeight;
		rightRect->h = barHeight;
		float frontierXpos = Lerp(initSpot, targetSpot, lerpFactor - ((float)i/(2*(numBars-1))));

		leftRect->x = 0;
		leftRect->w =frontierXpos;
		rightRect->x = frontierXpos;
		rightRect->w = windowWidth - frontierXpos;
		//create two objects for left and right
		//calculate frontier pos
			//lerp between left and right pos
			//delay based on i
			//
		//place left and right accordingly
		renderer->Enqueue(lefts[i]);
		renderer->Enqueue(rights[i]);
	}
}
void EshopAnim::CreateNameText()
{
	nameFont = TTF_OpenFont("cour.ttf", ptsize);
	SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderContext, TTF_RenderUTF8_Solid(nameFont, myName.c_str(), {255,255,255,255}));
	const char* test = SDL_GetError();
	visuals->UpdateTexture(nameTexture);
	visuals->UpdateLayer(10);
}


