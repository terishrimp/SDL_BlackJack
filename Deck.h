#pragma once
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "SDL.h"
class Deck {
private:
	void removeCard(const int index);
	std::vector <Card> deckList;
	SDL_Renderer* const m_renderer;
public:
	Deck(SDL_Renderer* renderer);
	void createDeck();
	Card takeCardFromFront();
	std::vector<Card> getDeckList();
	Card getCardAtIndex(const int index);
	void shuffleCardList();

};