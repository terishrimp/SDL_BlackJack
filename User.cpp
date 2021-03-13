#pragma once
#include "User.h"
#include <algorithm>
User::User(std::string name) {
	User::m_name = name;
}

void User::addCardToHand(std::vector<Card>* const handToAddTo, const Card cardToAdd) {
	handToAddTo->push_back(cardToAdd);
	sortHand(handToAddTo);
}

std::vector <Card>& User::getCards() {
	return m_handCards;
}

void User::clearHands() {
	m_handCards.clear();
}


float User::getUserBalance() {
	return m_Balance;
}

void User::setUserBalance(float m_value) {
	m_Balance = m_value;
}
int User::checkHandValue(const std::vector <Card> &handToCheck) {
	int sum{ 0 };
	if (handToCheck.size() < 1) {
		return 0;
	}
	else {
		for (Card card : handToCheck) {
			if (card.getValue() == 1 && sum < 11) {
				sum += 11;
			}
			else {
				sum += card.getValue();
			}
		}
		return sum;
	}
}

void User::displayHandValue(const std::vector <Card>& handToDisplayValue) {
	std::cout << "The value of " << m_name << "'s hand is: " << checkHandValue(handToDisplayValue) << std::endl;
}

void User::displayHand(std::vector <Card>& handToDisplay) {
	std::cout << m_name << "'s current cards: ";
	for (size_t i{ 0 }; i < handToDisplay.size(); i++) {
		if (handToDisplay[i].getIsFacingDown()) {
			std::cout << "??";
		}
		else {
			std::cout << handToDisplay[i].getName();
		}
		if (i != handToDisplay.size() - 1) {
			std::cout << " | ";
		}
	}
	std::cout << std::endl;
}

bool User::getIsStanding() {
	return m_isStanding;
}


void User::stand() {
	setIsStanding(true);
}




void User::setIsStanding(bool value) {
	m_isStanding = value;
}
void User::sortHand(std::vector <Card>* hand) {
	std::sort(hand->begin(), hand->end(), [](Card& a, Card& b) {return a.getValue() > b.getValue(); });
}