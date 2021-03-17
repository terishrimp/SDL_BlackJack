#pragma once
#include "Deck.h"

Deck::Deck(SDL_Renderer* const renderer) : m_renderer{ renderer } {
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
	Card ace(false, 1, "Ace", "Spades", m_renderer);
	for (size_t i{ 0 }; i < 52; i++) {
		deckList.push_back(ace);
	}
	//Card ace(false, 1, "Ace", "Spades", m_renderer);
	//Card two(false, 2, "Two", "Spades", m_renderer);
	//Card three(false, 3, "Three", "Spades", m_renderer);
	//Card four(false, 4, "Four", "Spades", m_renderer);
	//Card five(false, 5, "Five", "Spades", m_renderer);
	//Card six(false, 6, "Six", "Spades", m_renderer);
	//Card seven(false, 7, "Seven", "Spades", m_renderer);
	//Card eight(false, 8, "Eight", "Spades", m_renderer);
	//Card nine(false, 9, "Nine", "Spades", m_renderer);
	//Card ten(false, 10, "Ten", "Spades", m_renderer);
	//Card jack(false, 10, "Jack", "Spades", m_renderer );
	//Card queen(false, 10, "Queen", "Spades", m_renderer);
	//Card king(false, 10, "King", "Spades", m_renderer);

	//for (size_t i{ 0 }; i < 4; ++i) {
	//	std::string suitType;
	//	switch (i) {
	//	case 0:
	//		suitType = "Spades";
	//		break;
	//	case 1:
	//		suitType = "Clubs";
	//		break;
	//	case 2:
	//		suitType = "Hearts";
	//		break;
	//	default:
	//		suitType = "Diamonds";
	//		break;
	//	}
	//	deckList.push_back(ace);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(two);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(three);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(four);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(five);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(six);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(seven);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(eight);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(nine);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(ten);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(jack);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(queen);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//	deckList.push_back(king);
	//	deckList[deckList.size() - 1].setSuit(suitType);
	//}

}