#pragma once
#include "Card.h"

SDL_Texture* Card::FindCardTexture(std::string name, std::string suit, SDL_Renderer* renderer) {
	std::string filePath{ "./Images/Cards/" };
	filePath += name + "Of" + suit + ".png";
	return IMG_LoadTexture(renderer, filePath.c_str());
}

Card::Card(bool isFaceDown, int m_value, std::string name, std::string suit, SDL_Renderer* renderer) {
	Card::isFaceDown = isFaceDown;
	Card::m_value = m_value;
	Card::m_name = name;
	Card::m_suit = suit;
	Card::m_renderer = renderer;
	if (!isFaceDown)
		Card::m_cardImg = Card::FindCardTexture(m_name, m_suit, renderer);
	else
		Card::m_cardImg = IMG_LoadTexture(m_renderer, "./Images/Cards/CardFaceDown.png");
}

bool Card::getIsFacingDown() {
	return isFaceDown;
}

int Card::getValue() {
	return m_value;
}

std::string Card::getName() {
	return m_name;
}

void Card::setIsFacingDown(const bool m_value) {
	isFaceDown = m_value;
	if (!isFaceDown)
		Card::m_cardImg = Card::FindCardTexture(m_name, m_suit, m_renderer);
	else
		Card::m_cardImg = IMG_LoadTexture(m_renderer, "./Images/Cards/CardFaceDown.png");
}

void Card::setSuit(const std::string& str) {
	std::string lowered;
	for (size_t i{ 0 }; i < str.length(); ++i) {
		lowered += std::tolower(str[i]);
	}
	if (lowered == "spades" || lowered == "clubs"
		|| lowered == "hearts" || lowered == "diamonds") {
		m_suit = str;
		Card::m_cardImg = Card::FindCardTexture(m_name, m_suit, m_renderer);
	}
	else {
		m_suit = "NO SUIT";
	}
}

std::string Card::getSuit() {
	return m_suit;
}

SDL_Texture* Card::getCardImg() {
	return m_cardImg;
}