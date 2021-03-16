#pragma once
#include "Helper.h"
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "TextTexture.h"
#include "SDL.h"
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
	void start();
	void quit();
private:
	const SDL_Color white = SDL_Color{ 255,255,255,255 };
	const SDL_Color grey = SDL_Color{ 128,128,128,255 };
	void startScreen();
	void addCardToPlayerHand(User& player);
	bool checkValidInput(PlayerAction action, PlayerAction actionList[], const size_t arraySize);
	void activateMove(PlayerAction action, Player& player, const bool forSplit = false);
	void askForReplay(unsigned int balance);
	void reset();
	void askForInitialBalance();
	void askForBetValue();
	void displayAllHands();
	void createHands();
	void payout(const std::vector <Card> hand, std::string handName, bool replay = true);
	void displayTurnOptions(const bool splitHand = false);
	unsigned int turnCount{ 0 };
	Player m_player;
	Dealer m_dealer;
	Deck m_deck;
	int m_windowWidth;
	int m_windowHeight;
	unsigned int m_betValue{ 0 };
	bool gameHasStarted = false;
	bool gameHasCompleted = false;
	GameScene m_cGameScene = GameScene::START;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_event{ NULL };
	SDL_Point m_mousePoint{ NULL };
	SDL_Texture* m_gameBg;
	SDL_Texture* m_mousePointer;
	TTF_Font* m_smallFont = TTF_OpenFont("./Fonts/slkscre.ttf", 10);
	TTF_Font* m_mediumFont = TTF_OpenFont("./Fonts/slkscre.ttf", 16);
	TTF_Font* m_largeFont = TTF_OpenFont("./Fonts/slkscre.ttf", 24);
	const std::string m_mousePointerString = "./Images/Pointer.png";
	const std::string m_gameBgString = "./Images/Board.png";
};