#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
#include "RenderEngine.h"
#include "GameMath.h"
#include "GameClock.h"
#include "ColourRGBA.h"
#include "InputHandler.h"
#include "AudioEngine.h"
#include <string>
#include <vector>
class GameEngine; //forward definition to prevent circular includes in header
class GameScene;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	bool UpdateAndRender(RenderableComponent*& render);
	
	void Hide();
	void Show();
	void ToggleVisibility();
	virtual void Init() = 0;
	virtual void InitVisuals() = 0;
	bool hasCollision = true;
	void SetOwner(GameScene* owner);
	float GetFacing();
	void DrawBoundingBox();
	bool GetStaticStatus();
	void MoveVisuals();
	std::string GetName();
	
	Vector2 GetPos();
	Vector2 GetVelo();
	Vector2 GetBB();
	JRrect GetCorners();
	bool CompareTag(std::string tag);
	std::vector<GameObject*> colliders;
	std::vector<Vector2> collisionVectors;
protected:
	virtual bool Update() = 0;
	bool has_friction;
	int windowWidth, windowHeight;
	std::string name;
	std::vector<std::string> collisionTags;
	float facing;
	Vector2 position;
	Vector2 velocity;
	Vector2 BoundingBox;
	void Reflect(Vector2 SurfaceNormal);
	void SolidCollision();
	SDL_Rect BBtoDestRect();
	JRrect BBtoGameRect();
	void GetWindowParams();
	bool shown = false;
	bool is_static = false;
	GameLogging* logging;
	RenderEngine* renderer;
	//GameEngine* engine;
	InputHandler* input;
	GameScene* scene;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	RenderableComponent* visuals;
	AudioEngine* audio;
};
#endif // !USE_GAMEOBJECT

