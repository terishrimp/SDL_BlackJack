#pragma once
#include "Helper.h"
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

enum class GameScene {
	START,
	GAME,
	END
};

class Game {
public:
	Game(Player player, Dealer dealer, Deck deck, SDL_Renderer* renderer, SDL_Window* window);
	void loop();
	void start();
	void quit();
private:
	void displayStartScreen();
	void setBet(float m_value);
	void firstTurn(const bool splitHand = false);
	void turn(const bool splitHand = false);
	float getBet();
	void addCardToPlayerHand(User& player);
	bool checkValidInput(const char& playerInput, const char charPtr[], const size_t arraySize);
	void activateMove(const char playerInput, Player& player, const bool firstTurn = false, const bool forSplit = false);
	bool askForReplay();
	void reset();
	void askForInitialBalance();
	void askForBetValue();
	void displayAllHands();
	void createHands();
	void payout(const std::vector <Card> hand, std::string handName, bool replay = true);

	char playerInput{ ' ' };
	unsigned int turnCount{ 0 };
	Player m_player;
	Dealer m_dealer;
	Deck m_deck;
	int m_windowWidth;
	int m_windowHeight;
	float m_betValue{ 0 };
	bool gameHasStarted = false;
	bool gameHasCompleted = false;
	GameScene m_cGameScene = GameScene::START;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_cEvent{ NULL };
	SDL_Point m_mousePoint{ NULL };
	SDL_Texture* m_gameBg;
	SDL_Texture* m_mousePointer;
	TTF_Font* m_smallFont = TTF_OpenFont("./FOnts/8-bit-pusab.ttf", 6);
	TTF_Font* m_mediumFont = TTF_OpenFont("./FOnts/8-bit-pusab.ttf", 12);
	TTF_Font* m_largeFont = TTF_OpenFont("./FOnts/8-bit-pusab.ttf", 18);
	const std::string m_mousePointerString = "./Images/Pointer.png";
	const std::string m_gameBgString = "./Images/Board.png";
};