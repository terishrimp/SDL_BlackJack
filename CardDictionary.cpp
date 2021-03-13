#include "Card.h"



static class CardDictionary {
private:
	const std::string cardFilePath{ "./Images/Cards/" };
public:
	SDL_Texture* GetCardImage(Card& card, SDL_Renderer* renderer) {
		std::string filePath{ cardFilePath };
		filePath += card.getName() + "Of" + card.getSuit() + ".png";
		return IMG_LoadTexture(renderer, filePath.c_str());
	}
};
