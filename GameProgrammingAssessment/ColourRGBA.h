#pragma once
#ifndef USE_COLOUR_RGBA
#define USE_COLOUR_RGBA
#include "SDL.h"
#include "GameMath.h"
struct ColourRGBA
{
	int r, g, b, a;
	ColourRGBA(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};
	Uint32 MapFromColour(SDL_PixelFormat* format) {
		return SDL_MapRGB(format, r, g, b);
	}
	static ColourRGBA ColourLerp(ColourRGBA a, ColourRGBA b, long double fac) {
		return ColourRGBA{ (int)Lerp(a.r,b.r,fac), (int)Lerp(a.g,b.g,fac), (int)Lerp(a.b,b.b,fac), (int)Lerp(a.a,b.a,fac) };
	};
};
#endif

