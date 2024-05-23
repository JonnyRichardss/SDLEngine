#include "EndScreen.h"

void EndScreen::Init()
{
    position = Vector2::zero();
    BoundingBox = Vector2(GAME_MAX_X * 2, GAME_MAX_Y * 2);
    timer.Start();
}

void EndScreen::InitVisuals()
{
    SDL_Surface* Surf = ColourRGBA::Black().ColouredSurface();
    SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderContext, Surf);

    SDL_FreeSurface(Surf);
    visuals->UpdateTexture(Tex);
    SDL_Rect DefaultRect = BBtoDestRect();
    visuals->UpdateDestPos(&DefaultRect);
    visuals->UpdateLayer(9);
}

bool EndScreen::Update()
{
    if (timer.GetTimeElapsed() > 5s) {
        SDL_Event* event = new SDL_Event();
        event->type = SDL_QUIT;
        SDL_PushEvent(event);
        logging->Log("Game Over! Exiting!");
    }
    return true;
}
