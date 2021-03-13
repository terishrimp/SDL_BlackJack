#pragma once
#include "User.h"

class Dealer : public User {
	std::string m_name = "House";
public:
	Dealer();
	Dealer(std::string name);
};