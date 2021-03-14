#pragma once
#include "Card.h"

Card::Card(bool isFaceDown, int m_value, std::string name, std::string suit, SDL_Renderer * renderer) {
	Card::isFaceDown = isFaceDown;
	Card::m_value = m_value;
	Card::m_name = name;
	Card::m_suit = suit;
	Card::m_renderer = renderer;
	Card::m_cardImg = CardDictionary::GetCardImage(m_name, m_suit, renderer);
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
}

void Card::setSuit(const std::string& str) {
	std::string lowered;
	for (size_t i{ 0 }; i < str.length(); ++i) {
		lowered += std::tolower(str[i]);
	}
	if (lowered == "spades" || lowered == "clubs"
		|| lowered == "hearts" || lowered == "diamonds") {
		m_suit = str;
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
