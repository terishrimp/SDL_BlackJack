#pragma once
#include "Player.h"

Player::Player(std::string name) : User(name) {}

std::vector <Card>& Player::getSplitCards() {
	return m_splitHandCards;
}
void Player::clearHands() {
	m_handCards.clear();
	m_splitHandCards.clear();
}


bool Player::getIsSplit() {
	return m_isSplit;
}

void Player::split() {
	m_isSplit = true;
	addCardToHand(&m_splitHandCards, m_handCards[m_handCards.size() - 1]);
	m_handCards.pop_back();
	std::cout << "We will first play this hand: " << std::endl;
	displayHand(m_handCards);
	displayHandValue(m_handCards);
	std::cout << std::endl;

}

void Player::setIsSplit(bool value) {
	m_isSplit = value;
}
