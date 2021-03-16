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

class Player : public User{
private:

	std::vector <Card> m_splitHandCards;
	bool m_isSplit{ false };
	bool m_canSurrender{ false };
	bool m_canSplit{ false };
public:
	Player(std::string name, SDL_Point origin, SDL_Renderer *renderer);
	void clearHands() override;
	std::vector<Card>& getSplitCards();
	void split();
	bool getIsSplit();
	void setIsSplit(bool value);
	bool getCanSurrender();
	void setCanSurrender(bool value);
	bool getCanSplit();
	void setCanSplit(bool value);


}; 