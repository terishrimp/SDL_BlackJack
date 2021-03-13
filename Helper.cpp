#include "Helper.h"

const SDL_Color Helper::colorWhite = { 255,255,255,255 };
const SDL_Color Helper::colorGrey{ 127,127,127,255 };

SDL_Rect Helper::getOffsetRect(const int x, const int y, SDL_Texture* tex) {
	SDL_Rect tempRect{ NULL };
	tempRect.x = x;
	tempRect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &tempRect.w, &tempRect.h);

	return tempRect;
}
SDL_Rect Helper::getOffsetRect(const int x, const int y, const int w, const int h) {
	SDL_Rect tempRect{ NULL };
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

SDL_Texture* Helper::TTFtoTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
	return SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, text, color));
}
SDL_Rect Helper::TextRect(TTF_Font* font, const char* text) {
	SDL_Rect tempRect{ NULL };
	TTF_SizeText(font, text, &tempRect.w, &tempRect.h);
	return tempRect;
}