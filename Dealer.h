#pragma once
#include "User.h"

class Dealer : public User {
public:
	Dealer(std::string name, SDL_Point *m_origin, SDL_Renderer *renderer);
};