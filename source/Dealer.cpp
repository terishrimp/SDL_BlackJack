#pragma once
#include "Dealer.h"

Dealer::Dealer(std::string name, SDL_Point origin, SDL_Renderer* renderer) : User(name, origin, renderer) {}

void Dealer::revealHand() {
	for (size_t i{ 0 }; i < m_handCards.size(); ++i) 
		m_handCards[i].setIsFacingDown(false);
}
