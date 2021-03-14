#pragma once
#include <iostream>
#include <vector>
#include "User.h"

class Player : public User{
private:

	std::vector <Card> m_splitHandCards;
	bool m_isSplit{ false };
public:
	Player(std::string name, SDL_Point *origin, SDL_Renderer *renderer);
	void clearHands() override;
	std::vector<Card>& getSplitCards();
	void split();
	bool getIsSplit();
	void setIsSplit(bool value);


}; 