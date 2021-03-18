#include "Helper.h"

SDL_Rect Helper::getOffsetRect(SDL_Point point, SDL_Texture* tex) {
	SDL_Rect tempRect{ NULL };
	tempRect.x = point.x;
	tempRect.y = point.y;
	SDL_QueryTexture(tex, NULL, NULL, &tempRect.w, &tempRect.h);

	return tempRect;
}
SDL_Rect Helper::getOffsetRect(const int x, const int y, SDL_Texture* tex) {
	SDL_Rect tempRect{ NULL };
	tempRect.x = x;
	tempRect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &tempRect.w, &tempRect.h);

	return tempRect;
}
SDL_Rect Helper::getOffsetRect(const int x, const int y, int scale, SDL_Texture* tex) {
	SDL_Rect tempRect{ NULL };
	tempRect.x = x;
	tempRect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &tempRect.w, &tempRect.h);
	tempRect.w *= scale;
	tempRect.h *= scale;
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