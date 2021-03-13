#include "Game.h"

Game::Game(Player player, Dealer dealer, Deck deck, SDL_Renderer* renderer, SDL_Window* window)
	: m_player{ player }, m_dealer{ dealer }, m_deck{ deck }{
	Game::m_renderer = renderer;
	Game::m_window = window;
	Game::m_gameBg = IMG_LoadTexture(m_renderer, m_gameBgString.c_str());
	Game::m_mousePointer = IMG_LoadTexture(m_renderer, m_mousePointerString.c_str());
	SDL_GetWindowSize(window, &m_windowWidth, &m_windowHeight);
}

void Game::setBet(float m_value) {
	m_betValue = m_value;
};

float Game::getBet() {
	return m_betValue;
}


void Game::addCardToPlayerHand(User& player) {
	player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
}

bool Game::checkValidInput(const char& playerInput, const char charPtr[], const size_t arraySize) {
	bool isValid = false;

	//compare player input to all char's in char array
	// if none are valid, return false otherwise return true
	for (size_t i{ 0 }; i < arraySize; ++i) {
		if (playerInput == *(charPtr + i)) {
			isValid = true;
		}
	}
	return isValid ? true : false;
}



void Game::start() {
	//askForInitialBalance();
	//askForBetValue();
	m_deck.shuffleCardList();
	createHands();
	displayAllHands();
}

void Game::askForInitialBalance() {
	float l_playerBalance;
	//ask user for input
	std::cout << "What is the player's current balance: " << std::endl;
	std::cin >> l_playerBalance;

	//input error check
	while (!std::cin) {
		std::cin.clear(); // reset failbit
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error, input was not a number. Please try again." << std::endl;
		std::cout << "What is the player's current balance: " << std::endl;
		std::cin >> l_playerBalance;
	}

	//set player balance to input
	m_player.setUserBalance(l_playerBalance);
}

void Game::askForBetValue() {
	//ask user for input
	std::cout << "How much would you like to bet: " << std::endl;
	std::cin >> m_betValue;

	//input error check
	while (!std::cin || m_betValue <= 0 || m_betValue > m_player.getUserBalance()) {
		std::cin.clear(); // reset failbit
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error, input was not a number, or it was 0,\nor you don't have enough money. Please try again." << std::endl;
		std::cout << "How much would you like to bet: " << std::endl;
		std::cin >> m_betValue;
		std::cout << std::endl;
	}

	//subtract bet value from balance
	m_player.setUserBalance(m_player.getUserBalance() - m_betValue);

}

void Game::displayAllHands() {
	m_player.displayHand(m_player.getCards());
	m_player.displayHandValue(m_player.getCards());

	m_dealer.displayHand(m_dealer.getCards());

}

void Game::createHands()
{
	addCardToPlayerHand(m_player);
	addCardToPlayerHand(m_player);

	addCardToPlayerHand(m_dealer);
	addCardToPlayerHand(m_dealer);
	m_dealer.getCards()[1].setIsFacingDown(true);
}
void Game::reset() {
	turnCount = 0;
	gameHasCompleted = false;
	m_player.clearHands();
	m_dealer.clearHands();
	m_deck.createDeck();
	m_deck.shuffleCardList();
	m_player.setIsStanding(false);
	m_player.setIsSplit(false);
	std::cout << std::endl;

	askForBetValue();

	createHands();
	displayAllHands();

}

void Game::activateMove(const char playerInput, Player& player, const bool firstTurn, const bool forSplit) {
	if (firstTurn) {
		switch (playerInput) {
		case 's':
			//case for stand
			player.stand();
			break;
		case 'p':
			//case for split
			player.split();
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_betValue *= 2;
			break;
		case 'h':
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displayHand(player.getSplitCards());
				m_player.displayHandValue(player.getSplitCards());
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand(player.getCards());
				m_player.displayHandValue(player.getCards());
			}
			break;
		case 'd':
			//case for double down
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_betValue *= 2;
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displayHand(player.getSplitCards());
				m_player.displayHandValue(player.getSplitCards());
				player.stand();
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand(player.getCards());
				m_player.displayHandValue(player.getCards());
				player.stand();
			}
			break;
		case 'f':
			//case for surrender
			player.setUserBalance(player.getUserBalance() - (m_betValue / 2));
			player.stand();
		default:
			//error check
			std::cout << "Error, failed input that shouldn't have passed through" << std::endl;
			break;
		}
	}
	else {
		switch (playerInput) {
		case 's':
			//case for stand
			player.stand();
			break;
		case 'h':
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displayHand(m_player.getSplitCards());
				m_player.displayHandValue(m_player.getSplitCards());
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand(m_player.getCards());
				m_player.displayHandValue(m_player.getCards());
			}
			break;
		default:
			//error check
			std::cout << "Error, failed input that shouldn't have passed through" << std::endl;
			break;
		}
	}
}

bool Game::askForReplay() {
	char replayInput{ ' ' };
	// ask user for input
	std::cout << "Your current balance is: " << m_player.getUserBalance() << std::endl;
	std::cout << "Would you like to play again? Press 'q' to quit or anything else to continue." << std::endl;
	std::cin >> replayInput;

	if (replayInput != 'q') {
		gameHasCompleted = false;
		return true;
	}

	else {
		gameHasCompleted = true;
		return false;
	}
}
void Game::firstTurn(const bool splitHand) {
	//check to see if split can occur

	if (m_player.getCards().size() > 1 && m_player.getCards()[0].getName() == m_player.getCards()[1].getName()) {
		//cards are the same, provide option for split
		std::cout << "Would you like to Hit(H), Stand(S), Split(P), or DoubleDown(D): " << std::endl;
		std::cin >> playerInput;
		std::cout << std::endl;
		while (!checkValidInput(std::tolower(playerInput), "hspd", 5)) {
			std::cout << "Error. Input does not match any of the possible actions. Please try again." << std::endl;
			std::cout << "Would you like to Hit(H), Stand(S), Split(P), or DoubleDown(D): " << std::endl;
			std::cin >> playerInput;
			std::cout << std::endl;
		}
		activateMove(playerInput, m_player, true);
	}
	else if (m_dealer.getCards()[0].getName() == "Ace") {
		//dealer has an Ace revealed, provide option for surrender
		std::cout << "Would you like to Hit(H), Stand(S), Surrender(F), or DoubleDown(D): " << std::endl;
		std::cin >> playerInput;
		std::cout << std::endl;
		while (!checkValidInput(std::tolower(playerInput), "hsfd", 5)) {
			std::cout << "Error. Input does not match any of the possible actions. Please try again." << std::endl;
			std::cout << "Would you like to Hit(H), Stand(S), Surrender(F), or DoubleDown(D): " << std::endl;
			std::cin >> playerInput;
			std::cout << std::endl;
		}
		activateMove(playerInput, m_player, true);
	}
	else if (m_dealer.getCards()[0].getName() == "Ace" && m_player.getCards()[0].getName() == m_player.getCards()[1].getName()) {
		//dealer has an Ace revealed and player can split, provide option for surrender and split
		std::cout << "Would you like to Hit(H), Stand(S), Surrender(F), Split(P), or DoubleDown(D): " << std::endl;
		std::cin >> playerInput;
		std::cout << std::endl;
		while (!checkValidInput(std::tolower(playerInput), "hsfpd", 5)) {
			std::cout << "Error. Input does not match any of the possible actions. Please try again." << std::endl;
			std::cout << "Would you like to Hit(H), Stand(S), Surrender(F), Split(P), or DoubleDown(D): " << std::endl;
			std::cin >> playerInput;
			std::cout << std::endl;
		}
		activateMove(playerInput, m_player, true);
	}
	else {
		//provide options for hit, stand, and doubledown only
		std::cout << "Would you like to Hit(H), Stand(S), or DoubleDown(D): " << std::endl;
		std::cin >> playerInput;
		std::cout << std::endl;

		//input error check
		while (!checkValidInput(std::tolower(playerInput), "hsd", 4)) {
			std::cout << "Error. Input does not match any of the possible actions. Please try again." << std::endl;
			std::cout << "Would you like to Hit(H), Stand(S), or DoubleDown(D): " << std::endl;
			std::cin >> playerInput;
			std::cout << std::endl;
		}

		if (!splitHand) {
			activateMove(playerInput, m_player, true);
		}
		else {
			activateMove(playerInput, m_player, true, true);
		}
	}
}

void Game::turn(const bool splitHand) {
	//ask user for input
	std::cout << "Would you like to Hit(H) or Stand(S): " << std::endl;
	std::cin >> playerInput;
	std::cout << std::endl;

	//input error check
	while (!checkValidInput(std::tolower(playerInput), "hs", 3)) {
		std::cout << "Error. Input does not match any of the possible actions. Please try again." << std::endl;
		std::cout << "Would you like to Hit(H) or Stand(S): " << std::endl;
		std::cin >> playerInput;
		std::cout << std::endl;
	}

	if (!splitHand)
		activateMove(playerInput, m_player);
	else
		activateMove(playerInput, m_player, false, true);
}

void Game::payout(const std::vector <Card> hand, std::string handName, bool replay) {
	if (User::checkHandValue(hand) > 21) {
		std::cout << "Your " << handName << " hand is over 21, you've lost." << std::endl;
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	else if (User::checkHandValue(hand) > 17 && User::checkHandValue(hand) <= 21
		&& User::checkHandValue(hand) == User::checkHandValue(m_dealer.getCards())) {
		//return bet to player balance
		std::cout << "There is a tie between your " << handName << " hand and the dealer's. Your bet has returned to your balance." << std::endl;
		m_player.setUserBalance(m_player.getUserBalance() + m_betValue);
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	else if (User::checkHandValue(hand) <= 21
		&& User::checkHandValue(m_dealer.getCards()) > 21) {
		std::cout << "Dealer is over your 21 and your " << handName << " hand is not. You Win!" << std::endl;
		m_player.setUserBalance(m_player.getUserBalance() + m_betValue * 2);
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	else if (User::checkHandValue(hand) <= 21
		&& User::checkHandValue(hand) > User::checkHandValue(m_dealer.getCards())) {
		std::cout << "Because of your " << handName << " hand, you've won!" << std::endl;
		m_player.setUserBalance(m_player.getUserBalance() + m_betValue * 2);
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	else if (User::checkHandValue(hand) < User::checkHandValue(m_dealer.getCards())
		&& User::checkHandValue(hand) <= 21 && User::checkHandValue(m_dealer.getCards()) <= 21) {
		std::cout << "The dealer has a higher hand value than your " << handName << " hand, you've lost." << std::endl;
		m_dealer.setUserBalance(m_dealer.getUserBalance() + m_betValue * 2);
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	else {
		std::cout << "Unkown Payout reached" << std::endl;
		m_dealer.displayHandValue(m_dealer.getCards());
		m_player.displayHandValue(hand);
		if (replay) {
			if (askForReplay()) reset();
		}
	}
	std::cout << std::endl;
}
void Game::loop() {
	while (m_cEvent.type != SDL_QUIT) {
		while (SDL_PollEvent(&m_cEvent)) {
			SDL_GetMouseState(&m_mousePoint.x, &m_mousePoint.y);
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, m_gameBg, NULL, NULL);
			if (m_cGameScene == GameScene::START) {
				displayStartScreen();
			}
			else if (m_cGameScene == GameScene::GAME) {
				//actual game loop
			}

			SDL_RenderPresent(m_renderer);

		}
	}
	////ask user for input until they stand or lose
	//while (!gameHasCompleted) {
	//	//player natural
	//	if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) != 21) {
	//		std::cout << "\nYou have a natural, you win!" << std::endl;
	//		m_player.setUserBalance(m_player.getUserBalance() + m_betValue * 2.5f);
	//		if (askForReplay()) {
	//			reset();
	//			continue;
	//		}
	//	}
	//	//dealer natural
	//	else if (User::checkHandValue(m_player.getCards()) != 21 && User::checkHandValue(m_dealer.getCards()) == 21) {
	//		std::cout << "\nThe dealer has a natural, you lose." << std::endl;
	//		m_dealer.setUserBalance(m_dealer.getUserBalance() + m_betValue);
	//		if (askForReplay()) {
	//			reset();
	//			continue;
	//		}
	//	}
	//	//tie
	//	else if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) == 21) {
	//		std::cout << "\nThe game is a tie, game will reset." << std::endl;
	//		if (askForReplay()) {
	//			reset();
	//			continue;
	//		}
	//	}
	//	//play game
	//	else {
	//		//play regular hand
	//		while (!m_player.getIsStanding() && User::checkHandValue(m_player.getCards()) <= 21) {

	//			if (turnCount <= 0) {
	//				firstTurn();
	//			}
	//			else {
	//				turn();
	//			}
	//			turnCount++;
	//		}

	//		//check for split
	//		turnCount = 0;
	//		if (m_player.getIsSplit()) {
	//			//play split hand
	//			m_player.setIsStanding(false);
	//			//display hand
	//			std::cout << "\nWe will now look at this hand: " << std::endl;
	//			m_player.displayHand(m_player.getSplitCards());
	//			m_player.displayHandValue(m_player.getSplitCards());
	//			std::cout << std::endl;
	//			while (!m_player.getIsStanding() && User::checkHandValue(m_player.getSplitCards()) <= 21) {

	//				if (turnCount <= 0) {
	//					firstTurn(true);
	//				}
	//				else {
	//					turn(true);
	//				}
	//				turnCount++;
	//			}
	//		}

	//		//dealer will hit until their hand sum is above 17
	//		while (User::checkHandValue(m_dealer.getCards()) <= 17) {
	//			m_dealer.addCardToHand(&m_dealer.getCards(), m_deck.takeCardFromFront());
	//		}

	//		//reveal all cards
	//		for (size_t i{ 0 }; i < m_dealer.getCards().size(); ++i) {
	//			m_dealer.getCards()[i].setIsFacingDown(false);
	//		}

	//		//display their hand
	//		m_dealer.displayHand(m_dealer.getCards());
	//		m_dealer.displayHandValue(m_dealer.getCards());
	//	}
	//	std::cout << std::endl;

	//	//activate payouts
	//	if (m_player.getIsSplit()) {
	//		payout(m_player.getSplitCards(), "split", false);
	//	}
	//	payout(m_player.getCards(), "original");

	//	//end game if player has no more money
	//	if (m_player.getUserBalance() <= 0) {
	//		std::cout << "Your balance has run out. Game Over." << std::endl;
	//		break;
	//	}
	//}
}

void Game::displayStartScreen() {
	SDL_Texture* titleText = Helper::TTFtoTexture(m_renderer, m_largeFont, "BlackJack", Helper::colorWhite);
	SDL_Rect titleRect = Helper::TextRect(m_largeFont, "BlackJack");
	titleRect.x = m_windowWidth / 2 - titleRect.w / 2;
	titleRect.y = m_windowHeight * 0.25;
	SDL_RenderCopy(m_renderer, titleText, NULL, &titleRect);

	SDL_Texture* startGameText = Helper::TTFtoTexture(m_renderer, m_mediumFont, "Start Game", Helper::colorWhite);
	SDL_Texture* startGameTextSelected = Helper::TTFtoTexture(m_renderer, m_mediumFont, "Start Game", Helper::colorGrey);
	SDL_Rect startGameRect = Helper::TextRect(m_mediumFont, "Start Game");
	startGameRect.x = m_windowWidth / 2 - startGameRect.w / 2;
	startGameRect.y = m_windowHeight / 2 - startGameRect.h / 2;

	SDL_Texture* quitText = Helper::TTFtoTexture(m_renderer, m_mediumFont, "Quit", Helper::colorWhite);
	SDL_Texture* quitTextSelected = Helper::TTFtoTexture(m_renderer, m_mediumFont, "Quit", Helper::colorGrey);
	SDL_Rect quitRect = Helper::TextRect(m_mediumFont, "Quit");
	quitRect.x = m_windowWidth / 2 - quitRect.w / 2;
	quitRect.y = m_windowHeight * .75 - quitRect.h / 2;

	if (SDL_PointInRect(&m_mousePoint, &startGameRect)) {
		SDL_RenderCopy(m_renderer, startGameTextSelected, NULL, &startGameRect);
		if (m_cEvent.type == SDL_MOUSEBUTTONDOWN)
			m_cGameScene = GameScene::GAME;
	}
	else
		SDL_RenderCopy(m_renderer, startGameText, NULL, &startGameRect);

	if (SDL_PointInRect(&m_mousePoint, &quitRect)) {
		SDL_RenderCopy(m_renderer, quitTextSelected, NULL, &quitRect);
		if (m_cEvent.type == SDL_MOUSEBUTTONDOWN)
			SDL_Quit();
	}
	else
		SDL_RenderCopy(m_renderer, quitText, NULL, &quitRect);
}


void Game::quit() {
	std::cout << "Everything's A-OK!" << std::endl;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	atexit(SDL_Quit);
}
