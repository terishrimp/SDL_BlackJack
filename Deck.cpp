#pragma once
#include "Deck.h"

Deck::Deck() {
	createDeck();
}


Card Deck::takeCardFromFront() {
	Card takenCard = getCardAtIndex(0);
	removeCard(0);
	return takenCard;
}

void Deck::shuffleCardList() {
	srand((unsigned int)time(nullptr));
	std::random_shuffle(deckList.begin(), deckList.end());
}

std::vector<Card> Deck::getDeckList() {
	return deckList;
}



Card Deck::getCardAtIndex(const int index) {
	return deckList[index];
}
void Deck::removeCard(const int index) {
	deckList.erase(deckList.begin() + index);
}


void Deck::createDeck() {
	deckList.clear();

	Card ace(false, 1, "Ace", "Spades");
	Card two(false, 2, "Two", "Spades");
	Card three(false, 3, "Three", "Spades");
	Card four(false, 4, "Four", "Spades");
	Card five(false, 5, "Five", "Spades");
	Card six(false, 6, "Six", "Spades");
	Card seven(false, 7, "Seven", "Spades");
	Card eight(false, 8, "Eight", "Spades");
	Card nine(false, 9, "Nine", "Spades");
	Card ten(false, 10, "Ten", "Spades");
	Card jack(false, 10, "Jack", "Spades");
	Card queen(false, 10, "Queen", "Spades");
	Card king(false, 10, "King", "Spades");

	for (size_t i{ 0 }; i < 4; ++i) {
		std::string suitType;
		switch (i) {
		case 0:
			suitType = "Spades";
			break;
		case 1:
			suitType = "Clubs";
			break;
		case 2:
			suitType = "Hearts";
			break;
		default:
			suitType = "Diamonds";
			break;
		}
		deckList.push_back(ace);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(two);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(three);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(four);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(five);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(six);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(seven);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(eight);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(nine);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(ten);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(jack);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(queen);
		deckList[deckList.size() - 1].setSuit(suitType);
		deckList.push_back(king);
		deckList[deckList.size() - 1].setSuit(suitType);
	}

}