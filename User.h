#pragma once
#include <iostream>
#include <vector>
#include "Card.h"

class User {
protected:
	float m_Balance{ 0 };
	std::string m_name;
	std::vector <Card> m_handCards;
	bool m_isStanding{ false };

public:	
	float getUserBalance();
	void setUserBalance(float m_value);

	User(std::string name);
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