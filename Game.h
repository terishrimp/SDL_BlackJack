#pragma once
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "SDL.h"
#include "SDL_image.h"

 enum class GameScene {
	START,
	GAME,
	END
};

class Game {
public:
	Game(Player player, Dealer dealer, Deck deck);
	void loop();
	void start();
private:
	void setBet(float m_value);
	void firstTurn(const bool splitHand = false);
	void turn(const bool splitHand = false);
	float getBet();
	void addCardToPlayerHand( User &player);
	bool checkValidInput(const char &playerInput, const char charPtr[], const size_t arraySize);
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
	float m_betValue { 0 };
	bool gameHasStarted = false;
	bool gameHasCompleted = false;
	GameScene m_cGameScene = GameScene::START;
};