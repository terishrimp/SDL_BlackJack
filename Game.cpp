#include "Game.h"


Game::Game(Player player, Dealer dealer, Deck deck, SDL_Renderer* renderer, SDL_Window* window)
	: m_player{ player }, m_dealer{ dealer }, m_deck{ deck } {
	Game::m_renderer = renderer;
	Game::m_window = window;
	Game::m_gameBg = IMG_LoadTexture(m_renderer, m_gameBgString.c_str());
	Game::m_mousePointer = IMG_LoadTexture(m_renderer, m_mousePointerString.c_str());
	SDL_GetWindowSize(window, &m_windowWidth, &m_windowHeight);
}


void Game::addCardToPlayerHand(User& player) {
	player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
}

bool Game::checkValidInput(PlayerAction action, PlayerAction actionList[], const size_t arraySize) {
	bool isValid = false;

	//compare player input to all char's in char array
	// if none are valid, return false otherwise return true
	for (size_t i{ 0 }; i < arraySize; ++i) {
		if (action == actionList[i]) {
			isValid = true;
		}
	}
	return isValid;
}

void Game::displayAllHands() {
	m_player.displayHand();
	if (m_player.getIsSplit())
		m_player.displaySplitHand();

	m_dealer.displayHand();

}

void Game::createHands()
{
	addCardToPlayerHand(m_player);
	addCardToPlayerHand(m_player);

	addCardToPlayerHand(m_dealer);
	addCardToPlayerHand(m_dealer);
	m_dealer.getCards()[1].setIsFacingDown(true);
}

void Game::start() {
	//askForInitialBalance();
	//askForBetValue();
	m_deck.shuffleCardList();
	createHands();
}

void Game::startScreen() {

	TextTexture title(m_renderer, "BlackJack", m_largeFont);
	title.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * .5), static_cast<int>(m_windowHeight * 0.25) });
	SDL_RenderCopy(m_renderer, title.getTexture(), NULL, title.getRect());

	TextTexture startText(m_renderer, "Start Game", m_mediumFont);
	startText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .5) });

	TextTexture quitText(m_renderer, "Quit", m_mediumFont);
	quitText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * .5),
		static_cast<int>(m_windowHeight * .6) });




	if (SDL_PointInRect(&m_mousePoint, startText.getRect())) {
		startText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			m_cGameScene = GameScene::BALANCECHECK;
			return;
		}
	}
	else
		startText.setColor(white);

	if (SDL_PointInRect(&m_mousePoint, quitText.getRect())) {
		quitText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN)
			quit();
	}
	else
		quitText.setColor(white);

	SDL_RenderCopy(m_renderer, title.getTexture(), NULL, title.getRect());
	SDL_RenderCopy(m_renderer, startText.getTexture(), NULL, startText.getRect());
	SDL_RenderCopy(m_renderer, quitText.getTexture(), NULL, quitText.getRect());
}

void Game::askForInitialBalance() {
	std::vector<TextTexture> textureList;

	TextTexture balanceQuestion(m_renderer, "What is your initial balance?", m_mediumFont);
	balanceQuestion.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .25) });


	TextTexture balanceAmount = TextTexture(m_renderer, std::to_string(m_player.getUserBalance()).c_str(), m_mediumFont);
	balanceAmount.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .4) });

	TextTexture done(m_renderer, "Done", m_mediumFont);
	done.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * 0.8) });

	TextTexture ten(m_renderer, "10", m_mediumFont);
	textureList.push_back(ten);
	TextTexture hundred(m_renderer, "100", m_mediumFont);
	textureList.push_back(hundred);
	TextTexture twoHundredFifty(m_renderer, "250", m_mediumFont);
	textureList.push_back(twoHundredFifty);
	TextTexture fiveHundred(m_renderer, "500", m_mediumFont);
	textureList.push_back(fiveHundred);

	for (size_t i{ 0 }; i < textureList.size(); i++) {
		textureList[i].setPosition(SDL_Point{ static_cast<int>(105 + i * 100), static_cast<int>(m_windowHeight * .6) });
		if (SDL_PointInRect(&m_mousePoint, textureList[i].getRect())) {
			textureList[i].setColor(grey);
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				if (ten == textureList[i])
				{
					m_player.setUserBalance(m_player.getUserBalance() + 10);
				}
				else if (hundred == textureList[i])
				{
					m_player.setUserBalance(m_player.getUserBalance() + 100);

				}
				else if (twoHundredFifty == textureList[i])
				{
					m_player.setUserBalance(m_player.getUserBalance() + 250);

				}
				else if (fiveHundred == textureList[i])
				{
					m_player.setUserBalance(m_player.getUserBalance() + 500);

				}
				balanceAmount = TextTexture(m_renderer, std::to_string(m_player.getUserBalance()).c_str(), m_mediumFont);
				balanceAmount.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
					static_cast<int>(m_windowHeight * .4) });
			}
		}
		else {
			textureList[i].setColor(white);
		}
	}
	if (SDL_PointInRect(&m_mousePoint, done.getRect())) {
		done.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if ((int)m_player.getUserBalance() > 0) {
				start();
				m_cGameScene = GameScene::BETCHECK;
				return;
			}
			else {
				balanceAmount.setColor(grey);
			}
		}
	}
	else {
		done.setColor(white);
	}

	textureList.push_back(done);
	textureList.push_back(balanceQuestion);
	textureList.push_back(balanceAmount);
	for (size_t i{ 0 }; i < textureList.size(); i++) {
		SDL_RenderCopy(m_renderer, textureList[i].getTexture(), NULL, textureList[i].getRect());
	}
}

void Game::askForBetValue() {

	std::vector<TextTexture> textureList;

	TextTexture betQuestion(m_renderer, "What is your bet amount?", m_mediumFont);
	betQuestion.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .25) });


	TextTexture betAmount = TextTexture(m_renderer, std::to_string(m_betValue).c_str(), m_mediumFont);
	betAmount.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .4) });

	TextTexture done(m_renderer, "Done", m_mediumFont);
	done.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * 0.8) });

	TextTexture ten(m_renderer, "10", m_mediumFont);
	textureList.push_back(ten);
	TextTexture hundred(m_renderer, "100", m_mediumFont);
	textureList.push_back(hundred);
	TextTexture twoHundredFifty(m_renderer, "250", m_mediumFont);
	textureList.push_back(twoHundredFifty);
	TextTexture fiveHundred(m_renderer, "500", m_mediumFont);
	textureList.push_back(fiveHundred);

	for (size_t i{ 0 }; i < textureList.size(); i++) {
		textureList[i].setPosition(SDL_Point{ static_cast<int>(105 + i * 100), static_cast<int>(m_windowHeight * .6) });
		if (SDL_PointInRect(&m_mousePoint, textureList[i].getRect())) {
			textureList[i].setColor(grey);
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				if (ten == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 10)) >= 0)
						m_betValue += 10;
					else
						betAmount.setColor(grey);

				}
				else if (hundred == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 100)) >= 0)
						m_betValue += 100;
					else
						betAmount.setColor(grey);
				}
				else if (twoHundredFifty == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 250)) >= 0)
						m_betValue += 250;
					else
						betAmount.setColor(grey);
				}
				else if (fiveHundred == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 500)) > 0)
						m_betValue += 500;
					else
						betAmount.setColor(grey);
				}
				betAmount = TextTexture(m_renderer, std::to_string(m_betValue).c_str(), m_mediumFont);
				betAmount.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
					static_cast<int>(m_windowHeight * .4) });
				SDL_RenderCopy(m_renderer, betAmount.getTexture(), NULL, betAmount.getRect());
			}
		}
		else {
			textureList[i].setColor(white);
		}
	}
	if (SDL_PointInRect(&m_mousePoint, done.getRect())) {
		done.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if (m_betValue > 0) {
				m_cGameScene = GameScene::GAMELOOP;
				return;
			}
			else {
				betAmount.setColor(grey);
			}
		}
	}
	else done.setColor(white);

	textureList.push_back(done);
	textureList.push_back(betQuestion);
	textureList.push_back(betAmount);
	for (size_t i{ 0 }; i < textureList.size(); i++) {
		SDL_RenderCopy(m_renderer, textureList[i].getTexture(), NULL, textureList[i].getRect());
	}
}


void Game::reset() {

	m_cGameScene = GameScene::BETCHECK;
	turnCount = 0;
	m_betValue = 0;
	m_player.clearHands();
	m_dealer.clearHands();
	m_deck.createDeck();
	m_deck.shuffleCardList();
	m_player.setIsStanding(false);
	m_player.setIsPlayingRegularHand(true);
	m_player.setIsStandingOnSplit(false);
	m_player.setIsSplit(false);
	createHands();


}

void Game::activateMove(PlayerAction action, Player& player, const bool forSplit) {
	if (turnCount == 0) {
		switch (action) {
		case PlayerAction::STAND:
			//case for stand
			if (forSplit) {
				player.setIsStandingOnSplit(true);
				m_player.setIsPlayingRegularHand(true);
			}
			else {
				player.setIsStanding(true);
				if (player.getIsSplit()) {
					m_player.setIsPlayingRegularHand(false);
				}
			}
			break;
		case PlayerAction::SPLIT:
			//case for split
			player.split();
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_betValue *= 2;
			m_player.setIsPlayingRegularHand(false);
			break;
		case PlayerAction::HIT:
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
				m_player.displayHandValue(player.getSplitCards());
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
				m_player.displayHandValue(player.getCards());
			}
			break;
		case PlayerAction::DOUBLEDOWN:
			//case for double down
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_betValue *= 2;
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
				m_player.displayHandValue(player.getSplitCards());
				player.stand();
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
				m_player.displayHandValue(player.getCards());
				player.stand();
			}
			break;
		case PlayerAction::SURRENDER:
			//case for surrender
			player.setIsSurrendered(true);
			player.stand();
			break;
		default:
			//error check
			std::cout << "Error, failed input that shouldn't have passed through" << std::endl;
			break;
		}
	}
	else if (turnCount > 0) {
		switch (action) {
		case PlayerAction::STAND:
			//case for stand
			if (forSplit) {
				player.setIsStandingOnSplit(true);
				m_player.setIsPlayingRegularHand(true);
			}
			else {
				player.setIsStanding(true);
				if (player.getIsSplit()) {
					m_player.setIsPlayingRegularHand(false);
				}
			}
			break;
		case PlayerAction::HIT:
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
				m_player.displayHandValue(m_player.getSplitCards());
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
				m_player.displayHandValue(m_player.getCards());
			}
			break;
		default:
			//error check
			std::cout << "Error, failed input that shouldn't have passed through" << std::endl;
			break;
		}
	}
	turnCount++;
}

void  Game::askForReplay(unsigned int updatedBalance) {

	TextTexture balanceText(m_renderer, "Your current balance is:", m_smallFont);
	balanceText.setPosition(SDL_Point{ 75, static_cast<int> (m_windowHeight * .5 - balanceText.getRect()->h * 0.5) }, false);
	SDL_RenderCopy(m_renderer, balanceText.getTexture(), NULL, balanceText.getRect());

	TextTexture balanceAmount(m_renderer, std::to_string(updatedBalance), m_smallFont);
	balanceAmount.setPosition(SDL_Point{ balanceText.getPosition()->x + balanceText.getRect()->w + 40, static_cast<int> (m_windowHeight * .5 - balanceAmount.getRect()->h * 0.5) }, false);
	SDL_RenderCopy(m_renderer, balanceAmount.getTexture(), NULL, balanceAmount.getRect());

	TextTexture replayText(m_renderer, "Play again?", m_smallFont);
	replayText.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * .5), static_cast<int> (m_windowHeight * 0.65) });
	SDL_RenderCopy(m_renderer, replayText.getTexture(), NULL, replayText.getRect());

	TextTexture yes(m_renderer, "yes", m_smallFont);
	yes.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * .5 - 60), static_cast<int> (m_windowHeight * 0.7) });


	TextTexture no(m_renderer, "no", m_smallFont);
	no.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * .5 + 60), static_cast<int> (m_windowHeight * 0.7) });



	if (SDL_PointInRect(&m_mousePoint, yes.getRect())) {
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			m_player.setUserBalance(updatedBalance);
			reset();
			return;
		}
		yes.setColor(grey);
	}

	if (SDL_PointInRect(&m_mousePoint, no.getRect())) {
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			quit();
		}
		no.setColor(grey);
	}
	SDL_RenderCopy(m_renderer, yes.getTexture(), NULL, yes.getRect());
	SDL_RenderCopy(m_renderer, no.getTexture(), NULL, no.getRect());

}

void Game::displayTurnOptions(const bool splitHand) {
	PlayerAction action = PlayerAction::NONE;
	std::vector<TextTexture> textureList;
	if (turnCount > 0)
	{
		//ask user for input (only hit or stand)
		TextTexture hit(m_renderer, "hit", m_mediumFont);
		hit.setPosition(SDL_Point{ 100, static_cast<int> (m_windowHeight * 0.85) });
		textureList.push_back(hit);

		TextTexture stand(m_renderer, "stand", m_mediumFont);
		stand.setPosition(SDL_Point{ 200, static_cast<int> (m_windowHeight * 0.85) });
		textureList.push_back(stand);

		for (size_t i{ 0 }; i < textureList.size(); i++) {
			if (SDL_PointInRect(&m_mousePoint, textureList[i].getRect()))
			{
				if (m_event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (hit == textureList[i])
						action = PlayerAction::HIT;

					else if (stand == textureList[i])
						action = PlayerAction::STAND;

					if (!splitHand)
						activateMove(action, m_player, false);
					else
						activateMove(action, m_player, true);

				}
				textureList[i].setColor(grey);
			}
			else
			{
				textureList[i].setColor(white);
			}
		}
	}

	else if (turnCount == 0) {

		TextTexture hit(m_renderer, "hit", m_smallFont);
		hit.setPosition(SDL_Point{ 85, static_cast<int> (m_windowHeight * 0.8) });
		textureList.push_back(hit);

		TextTexture stand(m_renderer, "stand", m_smallFont);
		stand.setPosition(SDL_Point{ 254, static_cast<int> (m_windowHeight * 0.8) });
		textureList.push_back(stand);

		TextTexture doubleDown(m_renderer, "doubled", m_smallFont);
		doubleDown.setPosition(SDL_Point{ 420, static_cast<int>(m_windowHeight * 0.8) });
		textureList.push_back(doubleDown);


		if (m_player.getCards().size() > 1 && m_player.getCards()[0].getName() == m_player.getCards()[1].getName()) {
			//cards are the same, provide option for split

			TextTexture split(m_renderer, "split", m_smallFont);
			split.setPosition(SDL_Point{ 171, static_cast<int>(m_windowHeight * 0.9) });
			textureList.push_back(split);


			if (SDL_PointInRect(&m_mousePoint, split.getRect())) {
				if (m_event.type == SDL_MOUSEBUTTONDOWN) {
					action = PlayerAction::SPLIT;

					if (!splitHand)
						activateMove(action, m_player, false);
					else
						activateMove(action, m_player, true);

				}
				split.setColor(grey);
			}
			else split.setColor(white);
		}

		if (m_dealer.getCards()[0].getName() == "Ace") {

			TextTexture surrender(m_renderer, "surrender", m_smallFont);
			surrender.setPosition(SDL_Point{ 337, static_cast<int>(m_windowHeight * 0.9) });
			textureList.push_back(surrender);

			if (SDL_PointInRect(&m_mousePoint, surrender.getRect())) {
				if (m_event.type == SDL_MOUSEBUTTONDOWN) {
					action = PlayerAction::SURRENDER;

					if (!splitHand)
						activateMove(action, m_player, false);
					else
						activateMove(action, m_player, true);
				}
				surrender.setColor(grey);
			}
			else surrender.setColor(white);
		}

		for (size_t i{ 0 }; i < textureList.size(); i++) {
			if (SDL_PointInRect(&m_mousePoint, textureList[i].getRect())) {
				if (m_event.type == SDL_MOUSEBUTTONDOWN) {
					if (hit == textureList[i])
						action = PlayerAction::HIT;

					else if (stand == textureList[i])
						action = PlayerAction::STAND;

					else if (doubleDown == textureList[i])
						action = PlayerAction::DOUBLEDOWN;

					if (!splitHand)
						activateMove(action, m_player, false);
					else
						activateMove(action, m_player, true);

				}
				textureList[i].setColor(grey);
			}
			else {
				textureList[i].setColor(white);
			}
		}


	}
	for (TextTexture text : textureList) {
		SDL_RenderCopy(m_renderer, text.getTexture(), NULL, text.getRect());
	}
}


void Game::payout(const std::vector <Card> hand, std::string handName) {

	if (m_player.getIsSurrendered()) {
		TextTexture payout(m_renderer, "You have surrendered.", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		if (m_player.getUserBalance() - static_cast<int>(m_betValue * .5) > 10) {
			askForReplay(m_player.getUserBalance() - static_cast<int>(m_betValue * .5));
		}
		else { m_cGameScene = GameScene::START; }
	}
	else if (User::checkHandValue(hand) > 21)
	{
		TextTexture payout(m_renderer, "Your " + handName + " hand is over 21, you've lost.", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		if (m_player.getUserBalance() - m_betValue > 10) {
			askForReplay(m_player.getUserBalance() - m_betValue);
		}
		else { m_cGameScene = GameScene::START; }
	}
	else if (User::checkHandValue(hand) > 17 && User::checkHandValue(hand) <= 21
		&& User::checkHandValue(hand) == User::checkHandValue(m_dealer.getCards()))
	{
		//return bet to player balance
		TextTexture payout(m_renderer, "There is a tie between your " + handName + " hand and", m_smallFont);
		TextTexture payout2(m_renderer, handName + " hand and the dealer's.", m_smallFont);
		TextTexture payout3(m_renderer, "Your bet has returned to your balance.", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		payout2.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .15) });
		payout3.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .2) });
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		SDL_RenderCopy(m_renderer, payout2.getTexture(), NULL, payout2.getRect());
		SDL_RenderCopy(m_renderer, payout3.getTexture(), NULL, payout3.getRect());
		if (m_player.getUserBalance() > 10) {
			askForReplay(m_player.getUserBalance());
		}
		else { m_cGameScene = GameScene::START; }
	}
	else if (User::checkHandValue(hand) <= 21
		&& User::checkHandValue(m_dealer.getCards()) > 21)
	{
		TextTexture payout(m_renderer, "Dealer is over 21 and your " + handName, m_smallFont);
		TextTexture payout2(m_renderer, "hand is not. You Win!", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		payout2.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .15) });
		SDL_RenderCopy(m_renderer, payout2.getTexture(), NULL, payout2.getRect());
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		if (m_player.getUserBalance() + m_betValue > 10) {
			askForReplay(m_player.getUserBalance() + m_betValue);
		}
		else { m_cGameScene = GameScene::START; }
	}
	else if (User::checkHandValue(hand) <= 21
		&& User::checkHandValue(hand) > User::checkHandValue(m_dealer.getCards()))
	{
		TextTexture payout(m_renderer, "Your " + handName + " hand has a higher ", m_smallFont);
		TextTexture payout2(m_renderer, "value than the dealer's. You Win!", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		payout2.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .15) });
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		SDL_RenderCopy(m_renderer, payout2.getTexture(), NULL, payout2.getRect());
		if (m_player.getUserBalance() + m_betValue > 10) {
			askForReplay(m_player.getUserBalance() + m_betValue);
		}
		else { m_cGameScene = GameScene::START; }
	}
	else if (User::checkHandValue(hand) < User::checkHandValue(m_dealer.getCards())
		&& User::checkHandValue(hand) <= 21 && User::checkHandValue(m_dealer.getCards()) <= 21)
	{
		TextTexture payout(m_renderer, "The dealer has a higher hand value than your", m_smallFont);
		TextTexture payout2(m_renderer, handName + " hand. You Lose.", m_smallFont);
		payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
		payout2.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .15) });
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		SDL_RenderCopy(m_renderer, payout2.getTexture(), NULL, payout2.getRect());
		if (m_player.getUserBalance() - m_betValue > 10) {
			askForReplay(m_player.getUserBalance() - m_betValue);
		}
		else { m_cGameScene = GameScene::START; }
	}
	else
	{
		TextTexture payout(m_renderer, "Unknown payout reached", m_smallFont);
		std::cout << "Unknown Payout reached" << std::endl;
		m_dealer.displayHandValue(m_dealer.getCards());
		m_player.displayHandValue(hand);
		SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
		askForReplay(m_player.getUserBalance());
	}

}
void Game::loop() {
	SDL_ShowCursor(SDL_DISABLE);

	while (m_event.type != SDL_QUIT) {
		SDL_WaitEvent(&m_event);
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_gameBg, NULL, NULL);
		SDL_GetMouseState(&m_mousePoint.x, &m_mousePoint.y);
		SDL_Rect mousePointerRect = Helper::getOffsetRect(m_mousePoint.x - 12, m_mousePoint.y, m_mousePointer);


		if (m_cGameScene == GameScene::START) {
			m_betValue = 0;
			m_player.setUserBalance(0);
			startScreen();
		}
		else if (m_cGameScene == GameScene::BALANCECHECK)
			askForInitialBalance();
		else if (m_cGameScene == GameScene::BETCHECK)
			askForBetValue();
		else if (m_cGameScene == GameScene::GAMELOOP) {

			if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) != 21 && !gameHasStarted) {
				TextTexture payout(m_renderer, "You have a natural. You Win!", m_smallFont);
				payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
				SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
				askForReplay(m_player.getUserBalance() + (int)(round(m_betValue * 2.5f)));
			}
			//dealer natural 
			else if (User::checkHandValue(m_player.getCards()) != 21 && User::checkHandValue(m_dealer.getCards()) == 21 && !gameHasStarted) {
				TextTexture payout(m_renderer, "The dealer has a natural. You Lose.", m_smallFont);
				payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
				SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
				askForReplay(m_player.getUserBalance() - m_betValue);
			}
			//tie
			else if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) == 21 && !gameHasStarted) {
				TextTexture payout(m_renderer, "The game is a tie and will now reset.", m_smallFont);
				payout.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });
				SDL_RenderCopy(m_renderer, payout.getTexture(), NULL, payout.getRect());
				askForReplay(m_player.getUserBalance() + m_betValue);
			}
			else if (!m_player.getIsStanding() && User::checkHandValue(m_player.getCards()) <= 21 
				&& m_player.getIsPlayingRegularHand()) 
{
				gameHasStarted = true;
				displayTurnOptions();
				displayAllHands();

			}
			else if (!m_player.getIsStandingOnSplit() && m_player.getIsSplit() && User::checkHandValue(m_player.getSplitCards()) <= 21 
				&& !m_player.getIsPlayingRegularHand()) 
			{
				displayTurnOptions(true);
				displayAllHands();
			}

			//dealer hits till above 16
			while (m_player.getIsStanding() && User::checkHandValue(m_dealer.getCards()) <= 17) {
				m_dealer.addCardToHand(&m_dealer.getCards(), m_deck.takeCardFromFront());
			}



			if (!m_player.getIsSplit()) {
				if (m_player.getIsStanding() || User::checkHandValue(m_player.getCards()) > 21) {
					for (size_t i{ 0 }; i < m_dealer.getCards().size(); ++i) {
						m_dealer.getCards()[i].setIsFacingDown(false);
						displayAllHands();
					}
					payout(m_player.getCards(), "original");
				}
			}
			else if (m_player.getIsSplit()) {
				if ((m_player.getIsStanding() || User::checkHandValue(m_player.getCards()) > 21) 
					&& (m_player.getIsStandingOnSplit() || User::checkHandValue(m_player.getSplitCards()) > 21)) {
					for (size_t i{ 0 }; i < m_dealer.getCards().size(); ++i) {
						m_dealer.getCards()[i].setIsFacingDown(false);
						displayAllHands();
					}
					//payout for both hands.
				}
			}

		}
		SDL_RenderCopy(m_renderer, m_mousePointer, NULL, &mousePointerRect);
		SDL_RenderPresent(m_renderer);
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



void Game::quit() {
	std::cout << "Everything's A-OK!" << std::endl;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	atexit(SDL_Quit);
}
