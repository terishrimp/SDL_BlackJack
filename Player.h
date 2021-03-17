#pragma once
#include <iostream>
#include <vector>
#include "User.h"

enum class PlayerAction {
	HIT,
	STAND,
	SPLIT,
	DOUBLEDOWN,
	SURRENDER,
	NONE
};

enum class PlayerHand {
	NORMAL,
	SPLIT
};

class Player : public User{
private:

	std::vector <Card> m_splitHandCards;
	int splitHandYOffset = 100;
	bool m_isSplit{ false };
	bool m_isSurrendered{ false };
	bool m_isStandingOnSplit{ false };
	bool m_isPlayingRegularHand = true;
public:
	Player(std::string name, SDL_Point origin, SDL_Renderer *renderer);
	void clearHands() override;
	std::vector<Card>& getSplitCards();
	void displaySplitHand();
	void split();

	bool getIsSplit();
	void setIsSplit(bool value);

	bool getIsSurrendered();
	void setIsSurrendered(bool value);

	bool getIsStandingOnSplit();
	void setIsStandingOnSplit(bool value);

	bool getIsPlayingRegularHand();
	void setIsPlayingRegularHand(bool value);

}; 