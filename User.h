#pragma once
#include <iostream>
#include <vector>
#include "Helper.h"
#include "Card.h"
#include "SDL.h"
#include "SDL_image.h"
class User {
protected:
	unsigned int m_Balance{ 0 };
	std::string m_name;
	std::vector <Card> m_handCards;
	bool m_isStanding{ false };
	SDL_Point m_origin;
	SDL_Renderer* m_renderer;
	const int cardXOffset = 30;
	const int cardYOffset = 30;
	const Uint8 cardColumnLength = 4;

public:	
	unsigned int getUserBalance();
	void setUserBalance(unsigned int m_value);

	User(std::string name, SDL_Point origin, SDL_Renderer *renderer);
	std::vector<Card>& getCards();
	virtual void clearHands();
	void addCardToHand(std::vector<Card> * const handToAddTo, const Card cardToAdd);
	void sortHand(std::vector <Card> *hand);
	int static checkHandValue(const std::vector <Card> &handToCheck);
	void displayHandValue(const std::vector <Card> &handToDisplayValue);
	void displayHand( std::vector <Card> &handToDisplay);
	void stand();

	bool getIsStanding();
	void setIsStanding(const bool m_value);

};