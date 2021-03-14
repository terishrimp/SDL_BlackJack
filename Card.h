#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "CardDictionary.cpp"

class Card {
public:
	Card(bool isFaceDown, int value, std::string name, std::string suit, SDL_Renderer* renderer);
	void setIsFacingDown(const bool value);
	bool getIsFacingDown();
	void setSuit(const std::string &str);
	std::string getSuit();
	int getValue();
	std::string getName();
	SDL_Texture* getCardImg();

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_cardImg;
	bool isFaceDown;
	std::string m_suit;
	int m_value;
	std::string m_name;
};

