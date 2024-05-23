#pragma once
#ifndef USE_COLOUR_RGBA
#define USE_COLOUR_RGBA
#include "SDL.h"
#include "GameMath.h"
struct ColourRGBA
{
	int r, g, b, a;
	ColourRGBA() :r(0), g(0), b(0), a(255) {};
	ColourRGBA(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};
	Uint32 MapFromColour(SDL_PixelFormat* format) {
		return SDL_MapRGB(format, r, g, b);
	}
	static ColourRGBA ColourLerp(ColourRGBA a, ColourRGBA b, long double fac) {
		return ColourRGBA{ (int)Lerp(a.r,b.r,fac), (int)Lerp(a.g,b.g,fac), (int)Lerp(a.b,b.b,fac), (int)Lerp(a.a,b.a,fac) };
	};
	static ColourRGBA White() {
		return ColourRGBA(255, 255, 255, 255);
	}
	static ColourRGBA Black() {
		return ColourRGBA();
	}
	SDL_Surface* ColouredSurface() {
		SDL_Surface* Surf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
		//const char* test = SDL_GetError();
		SDL_FillRect(Surf, NULL, MapFromColour(Surf->format));
		return Surf;
	}
};
#endif

