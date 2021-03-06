#pragma once
#include <iostream>
#include <cstdlib>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Game.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "Helper.h"



int main(int argv, char** argc) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << "Unable to init SDL: " << SDL_GetError();
		return -1;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("BlackJack", 100, 100, 512, 444, SDL_WINDOW_SHOWN);
	Helper::CheckError(win);

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	Helper::CheckError(ren);

	Player player("player", SDL_Point{ 100,100 }, ren);
	Dealer dealer("house", SDL_Point{ 296,100 }, ren);
	Deck deck(ren);
	Game game(player, dealer, deck, ren, win);
	game.loop();
	return 0;
}