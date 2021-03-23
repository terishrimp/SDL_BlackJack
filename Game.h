#pragma once
#include "Helper.h"
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "TextTexture.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>



enum class GameScene {
	START,
	BALANCECHECK,
	BETCHECK,
	GAMELOOP,
	END
};



class Game {
public:
	Game(Player player, Dealer dealer, Deck deck, SDL_Renderer* renderer, SDL_Window* window);
	void loop();

private:

	void quit();
	void startScreen();
	void askForInitialBalance();
	void askForBetValue();
	void addCardToPlayerHand(User& player);
	void activateMove(const PlayerAction action, Player& player, const bool forSplit = false);
	void askForReplay(const int balance);
	void reset();
	void updateTable();
	void createHands();
	void payout(bool isSplit = false);
	void updateMoveOptions(const bool splitHand = false);

	const SDL_Color white = SDL_Color{ 255,255,255,255 };
	const SDL_Color grey = SDL_Color{ 128,128,128,255 };
	const SDL_Color brown = SDL_Color{ 104,104,32, 255 };
	const SDL_Color lightBrown = SDL_Color{ 232, 232, 122, 255 };
	TTF_Font* const m_smallFont = TTF_OpenFont("./Fonts/alagard.ttf", 14);
	TTF_Font* const m_mediumFont = TTF_OpenFont("./Fonts/alagard.ttf", 16);
	TTF_Font* const m_largeFont = TTF_OpenFont("./Fonts/alagard.ttf", 26);
	const std::string m_mousePointerString = "./Images/Pointer.png";
	const std::string m_emptyGameBgString = "./Images/Board.png";
	const std::string m_gameBgString = "./Images/Board2.png";
	Mix_Chunk* playCardSound = Mix_LoadWAV("./Sounds/playcard.wav");
	Mix_Chunk* drawCardSound = Mix_LoadWAV("./Sounds/draw.wav");
	Mix_Chunk* shuffleSound = Mix_LoadWAV("./Sounds/shuffle.wav");
	Mix_Chunk* drumHitSound = Mix_LoadWAV("./Sounds/cuckoo.wav");
	Mix_Chunk* errorSound = Mix_LoadWAV("./Sounds/error.wav");
	const int textShadowOffset{ -2 };


	SDL_Texture* const winText; 
	SDL_Texture* const loseText;

	unsigned int turnCount{ 0 };
	unsigned int m_betValue{ 0 };
	bool gameHasStarted = false;
	GameScene m_gameScene;
	Player m_player;
	Dealer m_dealer;
	Deck m_deck;

	int m_windowWidth;
	int m_windowHeight;

	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_event{ NULL };
	SDL_Point m_mousePoint{ NULL };
	SDL_Texture* m_emptyGameBg;
	SDL_Texture* m_gameBg;
	SDL_Texture* m_mousePointer;
};