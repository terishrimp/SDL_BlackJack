#pragma once
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include "Card.h"

class Deck {
private:
	void removeCard(const int index);
	std::vector <Card> deckList;

public:
	Deck();
	void createDeck();
	Card takeCardFromFront();
	std::vector<Card> getDeckList();
	Card getCardAtIndex(const int index);
	void shuffleCardList();

};