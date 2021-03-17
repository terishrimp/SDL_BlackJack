#pragma once
#include "Player.h"

Player::Player(std::string name, SDL_Point origin, SDL_Renderer *renderer) : User(name, origin, renderer) {}

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
}

void Player::displaySplitHand() {

		for (size_t i{ 0 }; i < m_splitHandCards.size(); i++) {
			SDL_Rect cardRect = Helper::getOffsetRect(m_origin.x + cardXOffset * (i % cardColumnLength)
				, m_origin.y + splitHandYOffset + cardYOffset * floor(i / cardColumnLength),
				m_splitHandCards[i].getCardImg());
			SDL_RenderCopy(m_renderer, m_splitHandCards[i].getCardImg(), NULL, &cardRect);
		}
}

void Player::setIsSplit(bool value) {
	m_isSplit = value;
}

bool Player::getCanSurrender() {
	return m_canSurrender;
}
void Player::setCanSurrender(bool value) {
	m_canSurrender = value;
}
bool Player::getCanSplit() {
	return m_canSplit;
}
void Player::setCanSplit(bool value) {
	m_canSplit = value;
}
