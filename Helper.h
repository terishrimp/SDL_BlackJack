#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cstdlib>
static class Helper {
public:
	static const SDL_Color colorWhite;
	static const SDL_Color colorGrey;

	template <typename T>
	static int CheckError(const T toCheck) {
		if (!toCheck) {
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		return -1;
	}

	static SDL_Rect getOffsetRect(const int x, const int y, SDL_Texture* tex);
	static SDL_Rect getOffsetRect(const int x, const int y, int scale, SDL_Texture* tex);
	static SDL_Rect getOffsetRect(const int x, const int y, const int w, const int h);

	static SDL_Texture* TTFtoTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
	static SDL_Rect TextRect(TTF_Font* font, const char* text);
};