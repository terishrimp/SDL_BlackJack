#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Card {
public:
	Card(bool isFaceDown, int value, std::string name, std::string suit, SDL_Texture *cardImg);
	void setIsFacingDown(const bool value);
	bool getIsFacingDown();
	void setSuit(const std::string &str);
	std::string getSuit();
	int getValue();
	std::string getName();
	SDL_Texture* GetCardImg();

private:
	SDL_Texture* m_cardImg;
	bool isFaceDown;
	std::string m_suit;
	int m_value;
	std::string m_name;
};

