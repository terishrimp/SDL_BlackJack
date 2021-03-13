#pragma once
#include <iostream>
#include <vector>
#include "User.h"

class Player : public User{
private:

	std::vector <Card> m_splitHandCards;
	bool m_isSplit{ false };
public:
	Player(std::string name);
	void clearHands() override;
	std::vector<Card>& getSplitCards();
	void split();
	bool getIsSplit();
	void setIsSplit(bool value);


}; 