#pragma once
#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Deck.h"
#include "Dealer.h"
#include "Player.h"

template <typename T>
int CheckError(const T toCheck);
SDL_Rect GetOffsetRect(const int x, const int y, SDL_Texture* tex);
SDL_Rect GetOffsetRect(const int x, const int y, const int w, const int h);



int main(int argv, char** argc) {
	GameScene m_cGameScene = GameScene::START;
	SDL_Event currentEvent{ NULL };

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Unable to init SDL: " << SDL_GetError();
		return -1;
	}

	SDL_Window* win = SDL_CreateWindow("BlackJack", 100, 100, 512, 444, SDL_WINDOW_SHOWN);
	CheckError(win);

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	CheckError(ren);

	SDL_Texture* titleScreenUnselected = IMG_LoadTexture(ren, "./Images/Title.png");
	CheckError(titleScreenUnselected);

	SDL_Texture* titleScreenStartSelected = IMG_LoadTexture(ren, "./Images/StartSelected.png");
	CheckError(titleScreenStartSelected);

	SDL_Texture* gameScreenBackground = IMG_LoadTexture(ren, "./Images/GameplayBackground.png");
	CheckError(gameScreenBackground);

	SDL_Rect startButtonRect = GetOffsetRect(199, 194, 173, 45);
	SDL_Point mousePoint;

	//game loop
	while (currentEvent.type != SDL_QUIT) {
		while (SDL_PollEvent(&currentEvent)) {
			SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
			SDL_RenderClear(ren);
			if (m_cGameScene == GameScene::START) {
				if (SDL_PointInRect(&mousePoint, &startButtonRect)) {
					SDL_RenderCopy(ren, titleScreenStartSelected, NULL, NULL);
					if (currentEvent.type == SDL_MOUSEBUTTONDOWN) {
						m_cGameScene = GameScene::GAME;
					}
				}
				else
				{
					SDL_RenderCopy(ren, titleScreenUnselected, NULL, NULL);
				}
			}
			else if (m_cGameScene == GameScene::GAME) {
				SDL_RenderCopy(ren, gameScreenBackground, NULL, NULL);
				//actual game loop
			}
			else if (m_cGameScene == GameScene::END) {
				//game over
			}

			SDL_RenderPresent(ren);

		}
	}

	SDL_DestroyTexture(titleScreenUnselected);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	atexit(SDL_Quit);

	return 0;
}

template <typename T>
int CheckError(const T toCheck) {
	if (!toCheck) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	return -1;
}

SDL_Rect GetOffsetRect(const int x, const int y, SDL_Texture* tex) {
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &tempRect.w, &tempRect.h);

	return tempRect;
}
SDL_Rect GetOffsetRect(const int x, const int y, const int w, const int h) {
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;

	return tempRect;
}

