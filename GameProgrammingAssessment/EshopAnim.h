#ifndef USE_ESHOP
#define USE_ESHOP

#include "GameObject.h"
#include "Timer.h"
#include "ColourRGBA.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
class EshopAnim : public GameObject
{
public:
	//things
	void Init();
protected:
	
	void Update();
	
private:
	const std::string name = "Jonathan Richards";
	const int numBars = 50;
	const int ptsize = 48;
	const int movePeriod = 600;
	const int colourPeriod = 1800;

	ColourRGBA leftInit = { 255,128,0,0 };
	ColourRGBA leftFinal = { 255,196,0,0 };

	ColourRGBA rightInit = { 255,196,0,0 };
	ColourRGBA rightFinal = { 255,128,0,0 };


	bool reverseAnim,reverseColour;
	
	std::vector<RenderableComponent*> lefts;
	std::vector<RenderableComponent*> rights;

	Timer timer;
	

	TTF_Font* nameFont;
	
	
	void Animate();
	void CreateNameText();
	void MoveName();
	void UpdateColours();
	void InitComponents();
};

#endif // !USE_ESHOP

