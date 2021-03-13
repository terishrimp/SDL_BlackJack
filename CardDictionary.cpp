#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class CardDictionary {
public:
	static SDL_Texture* GetCardImage(std::string name, std::string suit, SDL_Renderer* renderer) {
		std::string filePath{ "./Images/Cards/" };
		filePath += name + "Of" + suit + ".png";
		return IMG_LoadTexture(renderer, filePath.c_str());
	}
};
