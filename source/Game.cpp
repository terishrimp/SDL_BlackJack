#include "Game.h"

Game::Game(Player player, Dealer dealer, Deck deck, SDL_Renderer* renderer, SDL_Window* window)
	: m_player{ player }, m_dealer{ dealer }, m_deck{ deck }, winText{ IMG_LoadTexture(renderer, "./Images/WinText.png") },
	loseText{ IMG_LoadTexture(renderer, "./Images/LoseText.png") } {
	Game::m_renderer = renderer;
	Game::m_window = window;
	Game::m_emptyGameBg = IMG_LoadTexture(m_renderer, m_emptyGameBgString.c_str());
	Game::m_gameBg = IMG_LoadTexture(m_renderer, m_gameBgString.c_str());
	Game::m_mousePointer = IMG_LoadTexture(m_renderer, m_mousePointerString.c_str());
	m_gameScene = GameScene::START;
	SDL_GetWindowSize(window, &m_windowWidth, &m_windowHeight);

}

void Game::addCardToPlayerHand(User& player) {
	player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
}

void Game::updateTable() {
	SDL_Texture* playerIcon = IMG_LoadTexture(m_renderer, "./Images/playerIcon.png");
	SDL_Rect playerIconRect = Helper::getOffsetRect(m_player.getOrigin().x - 60, m_player.getOrigin().y, playerIcon);
	SDL_Texture* dealerIcon = IMG_LoadTexture(m_renderer, "./Images/playerIcon2.png");
	SDL_Rect dealerIconRect = Helper::getOffsetRect(m_dealer.getOrigin().x + 150, m_dealer.getOrigin().y, dealerIcon);

	TextTexture dealerText(m_renderer, "DEALER", m_mediumFont);
	dealerText.setColor(lightBrown);
	dealerText.setPosition(SDL_Point{ dealerIconRect.x + 16, m_dealer.getOrigin().y - 10 });
	TextTexture dealerShadow = dealerText;
	dealerShadow.setColor(brown);
	dealerShadow.setPosition(SDL_Point{ dealerText.getPosition()->x - textShadowOffset, dealerText.getPosition()->y - textShadowOffset }, false);

	TextTexture playerText(m_renderer, "PLAYER", m_mediumFont);
	playerText.setColor(lightBrown);
	playerText.setPosition(SDL_Point{ playerIconRect.x + 16, m_player.getOrigin().y - 10 });
	TextTexture playerShadow = playerText;
	playerShadow.setColor(brown);
	playerShadow.setPosition(SDL_Point{ playerText.getPosition()->x - textShadowOffset, playerText.getPosition()->y - textShadowOffset }, false);

	SDL_Texture* deckImg = IMG_LoadTexture(m_renderer, "./Images/Cards/CardFaceDown.png");
	SDL_Rect deckImgRect = Helper::getOffsetRect(m_windowWidth * 0.5 - 10, m_windowHeight * .4, deckImg);

	SDL_Texture* arrow = IMG_LoadTexture(m_renderer, "./Images/Arrow_01.png");
	SDL_Rect arrowRect{ 0,0,0,0 };

	if (m_player.getIsPlayingRegularHand() && !m_player.getIsStanding()) {
		arrowRect = Helper::getOffsetRect(m_player.getOrigin().x - 15, m_player.getOrigin().y + 10, arrow);

	}
	else if (!m_player.getIsPlayingRegularHand() && !m_player.getIsStanding()) {
		arrowRect = Helper::getOffsetRect(m_player.getOrigin().x - 15, m_player.getOrigin().y + 10 + m_player.splitHandYOffset, arrow);

	}

	SDL_RenderCopy(m_renderer, dealerIcon, NULL, &dealerIconRect);
	SDL_RenderCopy(m_renderer, playerIcon, NULL, &playerIconRect);
	SDL_RenderCopy(m_renderer, deckImg, NULL, &deckImgRect);
	SDL_RenderCopy(m_renderer, dealerShadow.getTexture(), NULL, dealerShadow.getRect());
	SDL_RenderCopy(m_renderer, dealerText.getTexture(), NULL, dealerText.getRect());
	SDL_RenderCopy(m_renderer, playerShadow.getTexture(), NULL, playerShadow.getRect());
	SDL_RenderCopy(m_renderer, playerText.getTexture(), NULL, playerText.getRect());
	SDL_RenderCopy(m_renderer, arrow, NULL, &arrowRect);

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

void Game::startScreen() {




	TextTexture title(m_renderer, "BlackJack", m_largeFont);
	title.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * .5),
		static_cast<int>(m_windowHeight * 0.35) });
	title.setColor(brown);

	TextTexture titleHighlight(m_renderer, "BlackJack", m_largeFont);
	titleHighlight.setPosition(SDL_Point{ title.getPosition()->x + textShadowOffset / 2,
		title.getPosition()->y + textShadowOffset / 2 }, false);
	titleHighlight.setColor(SDL_Color{ 0,64,0,255 });
	titleHighlight.setColor(lightBrown);

	TextTexture titleShadow(m_renderer, "BlackJack", m_largeFont);
	titleShadow.setPosition(SDL_Point{ title.getPosition()->x - textShadowOffset,
		title.getPosition()->y - textShadowOffset }, false);
	titleShadow.setColor(SDL_Color{ 15,15,15,255 });

	TextTexture startText(m_renderer, "Start Game", m_mediumFont);
	startText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .5) });

	TextTexture quitText(m_renderer, "Quit", m_mediumFont);
	quitText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * .5),
		static_cast<int>(m_windowHeight * .6) });

	if (SDL_PointInRect(&m_mousePoint, startText.getRect())) {
		startText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(-1, drumHitSound, 0);
			m_player.setUserBalance(0);
			m_betValue = 0;
			m_gameScene = GameScene::BALANCECHECK;
			reset();
			return;
		}
	}
	else {
		startText.setColor(white);
	}

	if (SDL_PointInRect(&m_mousePoint, quitText.getRect())) {
		quitText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(-1, drumHitSound, 0);
			quit();
		}
	}
	else {
		quitText.setColor(white);
	}
	SDL_RenderCopy(m_renderer, titleShadow.getTexture(), NULL, titleShadow.getRect());
	SDL_RenderCopy(m_renderer, title.getTexture(), NULL, title.getRect());
	SDL_RenderCopy(m_renderer, titleHighlight.getTexture(), NULL, titleHighlight.getRect());
	SDL_RenderCopy(m_renderer, startText.getTexture(), NULL, startText.getRect());
	SDL_RenderCopy(m_renderer, quitText.getTexture(), NULL, quitText.getRect());
}

void Game::activateMove(const PlayerAction action, Player& player, const bool forSplit) {
	if (turnCount == 0) {
		switch (action) {
		case PlayerAction::STAND:
			//case for stand
			if (forSplit) {
				player.setIsStandingOnSplit(true);
				m_player.setIsPlayingRegularHand(true);
				turnCount = 0;
			}
			else {
				player.setIsStanding(true);
				if (player.getIsSplit()) {
					m_player.setIsPlayingRegularHand(false);
				}
				turnCount++;
			}
			break;
		case PlayerAction::SPLIT:
			//case for split
			player.split();
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_player.setIsPlayingRegularHand(false);
			break;
		case PlayerAction::HIT:
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
			}
			turnCount++;
			break;
		case PlayerAction::DOUBLEDOWN:
			//case for double down
			player.setUserBalance(player.getUserBalance() - m_betValue);
			m_betValue *= 2;
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
				player.stand();
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
				player.stand();
			}
			turnCount++;
			break;
		case PlayerAction::SURRENDER:
			//case for surrender
			player.setIsSurrendered(true);
			if (forSplit) {
				player.setIsStandingOnSplit(true);
				m_player.setIsPlayingRegularHand(true);
				turnCount = 0;
			}
			else {
				player.setIsStanding(true);
				if (player.getIsSplit()) {
					m_player.setIsPlayingRegularHand(false);
				}
				turnCount++;
			}
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
				if (m_player.getIsSplit()) {
					m_player.setIsPlayingRegularHand(false);
				}
			}
			turnCount++;
			break;
		case PlayerAction::HIT:
			//case for hit
			if (forSplit) {
				player.addCardToHand(&player.getSplitCards(), m_deck.takeCardFromFront());
				m_player.displaySplitHand();
				if (User::checkHandValue(m_player.getSplitCards()) > 21) {
					turnCount = 0;
					m_player.setIsPlayingRegularHand(true);
				}
				else { turnCount++; }
			}
			else {
				player.addCardToHand(&player.getCards(), m_deck.takeCardFromFront());
				m_player.displayHand();
				turnCount++;
			}

			break;
		default:
			//error check
			std::cout << "Error, failed input that shouldn't have passed through" << std::endl;
			break;
		}
	}

}

void Game::askForInitialBalance() {
	std::vector<TextTexture> textureList;

	TextTexture balanceQuestionText(m_renderer, "What is your Initial Balance?", m_mediumFont);
	balanceQuestionText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .35) });
	balanceQuestionText.setColor(lightBrown);

	TextTexture balanceQuestionShadow = balanceQuestionText;
	balanceQuestionShadow.setPosition(SDL_Point{ balanceQuestionText.getPosition()->x - textShadowOffset,
		balanceQuestionText.getPosition()->y - textShadowOffset }, false);
	balanceQuestionShadow.setColor(brown);

	TextTexture balanceAmountText = TextTexture(m_renderer, std::to_string(m_player.getUserBalance()), m_largeFont);
	balanceAmountText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .5) });

	TextTexture doneText(m_renderer, "Done", m_mediumFont);
	doneText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.4),
		static_cast<int>(m_windowHeight * .8) });

	TextTexture resetText(m_renderer, "Reset", m_mediumFont);
	resetText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.6), static_cast<int>(m_windowHeight * .8) });

	TextTexture ten(m_renderer, "10", m_mediumFont);
	textureList.push_back(ten);
	TextTexture hundred(m_renderer, "100", m_mediumFont);
	textureList.push_back(hundred);
	TextTexture twoHundredFifty(m_renderer, "250", m_mediumFont);
	textureList.push_back(twoHundredFifty);
	TextTexture fiveHundred(m_renderer, "500", m_mediumFont);
	textureList.push_back(fiveHundred);

	for (size_t i{ 0 }; i < textureList.size(); i++) {
		textureList[i].setPosition(SDL_Point{ static_cast<int>(142 + i * 75), static_cast<int>(m_windowHeight * .7) });
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
				balanceAmountText = TextTexture(m_renderer, std::to_string(m_player.getUserBalance()), m_largeFont);
				balanceAmountText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
					static_cast<int>(m_windowHeight * .5) });
				Mix_PlayChannel(-1, drawCardSound, 0);
			}
		}
		else {
			textureList[i].setColor(white);
		}
	}
	if (SDL_PointInRect(&m_mousePoint, doneText.getRect())) {
		doneText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if ((int)m_player.getUserBalance() > 0) {
				m_gameScene = GameScene::BETCHECK;
				Mix_PlayChannel(-1, drumHitSound, 0);
				return;
			}
			else {
				Mix_PlayChannel(-1, errorSound, 0);
				balanceAmountText.setColor(grey);
			}
		}
	}
	else {
		doneText.setColor(white);
	}
	if (SDL_PointInRect(&m_mousePoint, resetText.getRect())) {
		resetText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if (m_player.getUserBalance() > 0) {
				Mix_PlayChannel(-1, drumHitSound, 0);
				m_player.setUserBalance(0);
			}
			else
				Mix_PlayChannel(-1, errorSound, 0);
		}
	}
	else resetText.setColor(white);

	textureList.push_back(doneText);
	textureList.push_back(resetText);
	textureList.push_back(balanceQuestionShadow);
	textureList.push_back(balanceQuestionText);
	textureList.push_back(balanceAmountText);
	for (size_t i{ 0 }; i < textureList.size(); i++) {
		SDL_RenderCopy(m_renderer, textureList[i].getTexture(), NULL, textureList[i].getRect());
	}
}

void Game::askForBetValue() {
	std::vector<TextTexture> textureList;

	TextTexture betQuestionText(m_renderer, "How much will you bet?", m_mediumFont);
	betQuestionText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .35) });
	betQuestionText.setColor(lightBrown);
	TextTexture betQuestionShadow = betQuestionText;
	betQuestionShadow.setPosition(SDL_Point{ betQuestionText.getPosition()->x - textShadowOffset,
		betQuestionText.getPosition()->y - textShadowOffset }, false);
	betQuestionShadow.setColor(brown);

	TextTexture betAmountText = TextTexture(m_renderer, std::to_string(m_betValue).c_str(), m_largeFont);
	betAmountText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .45) });

	TextTexture balanceAmountText(m_renderer, "Balance after bet: " + std::to_string(m_player.getUserBalance() - m_betValue), m_smallFont);
	balanceAmountText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
		static_cast<int>(m_windowHeight * .6) });

	TextTexture doneText(m_renderer, "Done", m_mediumFont);
	doneText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.4),
		static_cast<int>(m_windowHeight * 0.8) });

	TextTexture resetText(m_renderer, "Reset", m_mediumFont);
	resetText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.6), static_cast<int>(m_windowHeight * .8) });

	TextTexture ten(m_renderer, "10", m_mediumFont);
	textureList.push_back(ten);
	TextTexture hundred(m_renderer, "100", m_mediumFont);
	textureList.push_back(hundred);
	TextTexture twoHundredFifty(m_renderer, "250", m_mediumFont);
	textureList.push_back(twoHundredFifty);
	TextTexture fiveHundred(m_renderer, "500", m_mediumFont);
	textureList.push_back(fiveHundred);

	for (size_t i{ 0 }; i < textureList.size(); i++) {
		textureList[i].setPosition(SDL_Point{ static_cast<int>(142 + i * 75),
			static_cast<int>(m_windowHeight * .7) });
		if (SDL_PointInRect(&m_mousePoint, textureList[i].getRect())) {
			textureList[i].setColor(grey);
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				if (ten == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 10)) >= 0)
						m_betValue += 10;
					else
						betAmountText.setColor(grey);
				}
				else if (hundred == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 100)) >= 0)
						m_betValue += 100;
					else
						betAmountText.setColor(grey);
				}
				else if (twoHundredFifty == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 250)) >= 0)
						m_betValue += 250;
					else
						betAmountText.setColor(grey);
				}
				else if (fiveHundred == textureList[i])
				{
					if ((int)(m_player.getUserBalance() - (m_betValue + 500)) >= 0)
						m_betValue += 500;
					else
						betAmountText.setColor(grey);
				}
				betAmountText = TextTexture(m_renderer, std::to_string(m_betValue).c_str(), m_largeFont);
				betAmountText.setPosition(SDL_Point{ static_cast<int>(m_windowWidth * 0.5),
					static_cast<int>(m_windowHeight * .45) });
				Mix_PlayChannel(-1, drawCardSound, 0);
			}
		}
		else {
			textureList[i].setColor(white);
		}
	}
	if (SDL_PointInRect(&m_mousePoint, doneText.getRect())) {
		doneText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if (m_betValue > 0) {
				m_player.setUserBalance(m_player.getUserBalance() - m_betValue);
				m_gameScene = GameScene::GAMELOOP;
				gameHasStarted = false;
				Mix_PlayChannel(-1, shuffleSound, 0);
				reset();
				return;
			}
			else {
				Mix_PlayChannel(-1, errorSound, 0);
				betAmountText.setColor(grey);
			}
		}

	}
	else doneText.setColor(white);

	if (SDL_PointInRect(&m_mousePoint, resetText.getRect())) {
		resetText.setColor(grey);
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			if (m_betValue > 0) {
				Mix_PlayChannel(-1, drumHitSound, 0);
				m_betValue = 0;
			}
			else
				Mix_PlayChannel(-1, errorSound, 0);
		}
	}
	else resetText.setColor(white);

	textureList.push_back(balanceAmountText);
	textureList.push_back(resetText);
	textureList.push_back(doneText);
	textureList.push_back(betQuestionShadow);
	textureList.push_back(betQuestionText);
	textureList.push_back(betAmountText);
	for (size_t i{ 0 }; i < textureList.size(); i++) {
		SDL_RenderCopy(m_renderer, textureList[i].getTexture(), NULL, textureList[i].getRect());
	}
}

void Game::reset() {
	if (gameHasStarted && m_player.getUserBalance() >= 10) {
		m_gameScene = GameScene::BETCHECK;
		gameHasStarted = false;
	}
	else if (gameHasStarted && m_player.getUserBalance() < 10) {
		m_gameScene = GameScene::START;
		gameHasStarted = false;
	}
	turnCount = 0;
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

void  Game::askForReplay(const int updatedBalance) {
	TextTexture endText(m_renderer, "Your current balance is: " + std::to_string(updatedBalance), m_smallFont);
	endText.setPosition(SDL_Point{ 100, static_cast<int> (m_windowHeight * 0.725) }, false);

	TextTexture replayText(m_renderer, "Play again?", m_smallFont);
	replayText.setPosition(SDL_Point{ 384 , static_cast<int> (m_windowHeight * 0.7) });

	TextTexture yes(m_renderer, "yes", m_smallFont);
	yes.setPosition(SDL_Point{ replayText.getRect()->x + replayText.getRect()->w / 2 - 40, static_cast<int> (m_windowHeight * 0.75) });

	TextTexture no(m_renderer, "no", m_smallFont);
	no.setPosition(SDL_Point{ replayText.getRect()->x + replayText.getRect()->w / 2 + 40, static_cast<int> (m_windowHeight * 0.75) });

	if (updatedBalance > 10) {

		if (SDL_PointInRect(&m_mousePoint, yes.getRect())) {
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				m_player.setUserBalance(updatedBalance);
				m_gameScene = GameScene::BETCHECK;
				m_betValue = 0;
				Mix_PlayChannel(-1, drumHitSound, 0);
				return;
			}
			yes.setColor(grey);
		}

		if (SDL_PointInRect(&m_mousePoint, no.getRect())) {
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				Mix_PlayChannel(-1, drumHitSound, 0);
				quit();
			}
			no.setColor(grey);
		}
	}
	else {

		endText.setText("Your balance is below minimum bet.");
		endText.setPosition(SDL_Point{ 50, static_cast<int> (m_windowHeight * 0.7 - endText.getRect()->h/2) }, false);

		TextTexture endText2(m_renderer, "Game Over.", m_smallFont);
		endText2.setPosition(SDL_Point{ 50, static_cast<int>(m_windowHeight * 0.725 + endText2.getRect()->h/2) }, false);
		SDL_RenderCopy(m_renderer, endText2.getTexture(), NULL, endText2.getRect());

		if (SDL_PointInRect(&m_mousePoint, yes.getRect())) {
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				m_player.setUserBalance(updatedBalance);
				m_gameScene = GameScene::START;
				Mix_PlayChannel(-1, drumHitSound, 0);
				return;
			}
			yes.setColor(grey);
		}

		if (SDL_PointInRect(&m_mousePoint, no.getRect())) {
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				Mix_PlayChannel(-1, drumHitSound, 0);
				quit();
			}
			no.setColor(grey);
		}
	}
	SDL_RenderCopy(m_renderer, endText.getTexture(), NULL, endText.getRect());
	SDL_RenderCopy(m_renderer, replayText.getTexture(), NULL, replayText.getRect());

	SDL_RenderCopy(m_renderer, yes.getTexture(), NULL, yes.getRect());
	SDL_RenderCopy(m_renderer, no.getTexture(), NULL, no.getRect());
}

void Game::updateMoveOptions(const bool splitHand) {
	PlayerAction action = PlayerAction::NONE;
	std::vector<TextTexture> textureList;

	//ask user for input (only hit or stand)
	TextTexture hit(m_renderer, "Hit", m_smallFont);
	hit.setPosition(SDL_Point{ 85, static_cast<int> (m_windowHeight * 0.8) });
	textureList.push_back(hit);

	TextTexture stand(m_renderer, "Stand", m_smallFont);
	stand.setPosition(SDL_Point{ 254, static_cast<int> (m_windowHeight * 0.8) });
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

				Mix_PlayChannel(-1, playCardSound, 0);

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


	if (turnCount == 0) {

		TextTexture doubleDown(m_renderer, "DoubleDown", m_smallFont);
		doubleDown.setPosition(SDL_Point{ 420, static_cast<int>(m_windowHeight * 0.8) });
		textureList.push_back(doubleDown);


		if (SDL_PointInRect(&m_mousePoint, doubleDown.getRect())) {
			if (m_event.type == SDL_MOUSEBUTTONDOWN) {
				action = PlayerAction::DOUBLEDOWN;
				Mix_PlayChannel(-1, playCardSound, 0);
				if (!splitHand)
					activateMove(action, m_player, false);
				else
					activateMove(action, m_player, true);
			}
			doubleDown.setColor(grey);
		}
		else {
			doubleDown.setColor(white);
		}

		if (m_player.getCards().size() > 1 && m_player.getCards()[0].getName() == m_player.getCards()[1].getName()) {
			//cards are the same, provide option for split

			TextTexture split(m_renderer, "Split", m_smallFont);
			split.setPosition(SDL_Point{ 171, static_cast<int>(m_windowHeight * 0.9) });
			textureList.push_back(split);

			if (SDL_PointInRect(&m_mousePoint, split.getRect())) {
				if (m_event.type == SDL_MOUSEBUTTONDOWN) {
					action = PlayerAction::SPLIT;

					Mix_PlayChannel(-1, playCardSound, 0);

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
			TextTexture surrender(m_renderer, "Surrender", m_smallFont);
			surrender.setPosition(SDL_Point{ 337, static_cast<int>(m_windowHeight * 0.9) });
			textureList.push_back(surrender);

			if (SDL_PointInRect(&m_mousePoint, surrender.getRect())) {
				if (m_event.type == SDL_MOUSEBUTTONDOWN) {

					action = PlayerAction::SURRENDER;

					Mix_PlayChannel(-1, playCardSound, 0);

					if (!splitHand)
						activateMove(action, m_player, false);
					else
						activateMove(action, m_player, true);

				}
				surrender.setColor(grey);
			}
			else surrender.setColor(white);
		}


	}
	for (TextTexture text : textureList) {
		SDL_RenderCopy(m_renderer, text.getTexture(), NULL, text.getRect());
	}
}

void Game::payout(bool isSplit) {
	int textYOffset{ 40 };
	int regularHandPay{ 0 };
	int splitHandPay{ 0 };
	SDL_Point splitHandTextPos{ m_player.getOrigin().x, m_player.getOrigin().y - textYOffset / 2 + m_player.splitHandYOffset };
	SDL_Point originalHandTextPos{ m_player.getOrigin().x, m_player.getOrigin().y - textYOffset };
	SDL_Point dealerSplitHandTextPos{ m_dealer.getOrigin().x, m_dealer.getOrigin().y - (int)round(textYOffset * 1.5) };
	SDL_Point dealerOriginalHandTextPos{ m_dealer.getOrigin().x, m_dealer.getOrigin().y - textYOffset };
	TextTexture withOriginal(m_renderer, " against original hand", m_smallFont);
	TextTexture withSplit(m_renderer, " against split hand", m_smallFont);
	TextTexture tieText(m_renderer, "TIE against Dealer", m_smallFont);

	tieText.setPosition(SDL_Point{  }, false);

	if (m_player.getIsSurrendered()) {
		SDL_Rect loseRect = Helper::getOffsetRect(originalHandTextPos, loseText);
		SDL_Rect winRect = Helper::getOffsetRect(dealerOriginalHandTextPos, winText);

		withOriginal.setPosition(SDL_Point{ winRect.x + winRect.w, winRect.y }, false);

		SDL_RenderCopy(m_renderer, withOriginal.getTexture(), NULL, withOriginal.getRect());
		SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
		SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

		regularHandPay = +(int)round(m_betValue * 0.5);
	}
	else if (User::checkHandValue(m_player.getCards()) > 21)
	{
		SDL_Rect loseRect = Helper::getOffsetRect(originalHandTextPos, loseText);
		SDL_Rect winRect = Helper::getOffsetRect(dealerOriginalHandTextPos, winText);

		withOriginal.setPosition(SDL_Point{ winRect.x + winRect.w, winRect.y }, false);
		SDL_RenderCopy(m_renderer, withOriginal.getTexture(), NULL, withOriginal.getRect());
		SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
		SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);
		regularHandPay = 0;
	}
	else if (User::checkHandValue(m_player.getCards()) > 17 && User::checkHandValue(m_player.getCards()) <= 21
		&& User::checkHandValue(m_player.getCards()) == User::checkHandValue(m_dealer.getCards()))
	{
		//return bet to player balance
		tieText.setPosition(originalHandTextPos, false);
		SDL_RenderCopy(m_renderer, tieText.getTexture(), NULL, tieText.getRect());

		regularHandPay = m_betValue;
	}
	else if (User::checkHandValue(m_player.getCards()) <= 21
		&& User::checkHandValue(m_dealer.getCards()) > 21)
	{
		SDL_Rect winRect = Helper::getOffsetRect(originalHandTextPos, winText);
		SDL_Rect loseRect = Helper::getOffsetRect(dealerOriginalHandTextPos, loseText);

		TextTexture withOriginal(m_renderer, " against original hand", m_smallFont);
		withOriginal.setPosition(SDL_Point{ loseRect.x + loseRect.w, loseRect.y }, false);
		SDL_RenderCopy(m_renderer, withOriginal.getTexture(), NULL, withOriginal.getRect());
		SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
		SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

		regularHandPay = m_betValue * 2;

	}
	else if (User::checkHandValue(m_player.getCards()) <= 21
		&& User::checkHandValue(m_player.getCards()) > User::checkHandValue(m_dealer.getCards()))
	{
		SDL_Rect winRect = Helper::getOffsetRect(originalHandTextPos, winText);
		SDL_Rect loseRect = Helper::getOffsetRect(dealerOriginalHandTextPos, loseText);

		withOriginal.setPosition(SDL_Point{ loseRect.x + loseRect.w, loseRect.y }, false);
		SDL_RenderCopy(m_renderer, withOriginal.getTexture(), NULL, withOriginal.getRect());
		SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
		SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

		regularHandPay = m_betValue * 2;
	}
	else if (User::checkHandValue(m_player.getCards()) < User::checkHandValue(m_dealer.getCards())
		&& User::checkHandValue(m_player.getCards()) <= 21 && User::checkHandValue(m_dealer.getCards()) <= 21)
	{
		SDL_Rect loseRect = Helper::getOffsetRect(originalHandTextPos, loseText);
		SDL_Rect winRect = Helper::getOffsetRect(dealerOriginalHandTextPos, winText);

		withOriginal.setPosition(SDL_Point{ winRect.x + winRect.w, winRect.y }, false);
		SDL_RenderCopy(m_renderer, withOriginal.getTexture(), NULL, withOriginal.getRect());
		SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
		SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

		regularHandPay = 0;

	}
	if (isSplit) {
		if (User::checkHandValue(m_player.getSplitCards()) > 21)
		{
			SDL_Rect loseRect = Helper::getOffsetRect(splitHandTextPos, loseText);
			SDL_Rect winRect = Helper::getOffsetRect(dealerSplitHandTextPos, winText);

			withSplit.setPosition(SDL_Point{ winRect.x + winRect.w, winRect.y }, false);
			SDL_RenderCopy(m_renderer, withSplit.getTexture(), NULL, withSplit.getRect());
			SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
			SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

			splitHandPay = 0;
		}
		else if (User::checkHandValue(m_player.getSplitCards()) > 17 && User::checkHandValue(m_player.getSplitCards()) <= 21
			&& User::checkHandValue(m_player.getSplitCards()) == User::checkHandValue(m_dealer.getCards()))
		{
			//return bet to player balance
			tieText.setPosition(splitHandTextPos, false);
			SDL_RenderCopy(m_renderer, tieText.getTexture(), NULL, tieText.getRect());

			splitHandPay = m_betValue;
		}
		else if (User::checkHandValue(m_player.getSplitCards()) <= 21
			&& User::checkHandValue(m_dealer.getCards()) > 21)
		{
			SDL_Rect winRect = Helper::getOffsetRect(splitHandTextPos, winText);
			SDL_Rect loseRect = Helper::getOffsetRect(dealerSplitHandTextPos, loseText);

			withSplit.setPosition(SDL_Point{ loseRect.x + loseRect.w, loseRect.y }, false);
			SDL_RenderCopy(m_renderer, withSplit.getTexture(), NULL, withSplit.getRect());
			SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
			SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

			splitHandPay = m_betValue * 2;

		}
		else if (User::checkHandValue(m_player.getSplitCards()) <= 21
			&& User::checkHandValue(m_player.getSplitCards()) > User::checkHandValue(m_dealer.getCards()))
		{
			SDL_Rect winRect = Helper::getOffsetRect(splitHandTextPos, winText);
			SDL_Rect loseRect = Helper::getOffsetRect(dealerSplitHandTextPos, loseText);

			withSplit.setPosition(SDL_Point{ loseRect.x + loseRect.w, loseRect.y }, false);
			SDL_RenderCopy(m_renderer, withSplit.getTexture(), NULL, withSplit.getRect());
			SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
			SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

			splitHandPay = m_betValue * 2;
		}
		else if (User::checkHandValue(m_player.getSplitCards()) < User::checkHandValue(m_dealer.getCards())
			&& User::checkHandValue(m_player.getSplitCards()) <= 21 && User::checkHandValue(m_dealer.getCards()) <= 21)
		{
			SDL_Rect loseRect = Helper::getOffsetRect(splitHandTextPos, loseText);
			SDL_Rect winRect = Helper::getOffsetRect(dealerSplitHandTextPos, winText);

			withSplit.setPosition(SDL_Point{ winRect.x + winRect.w, winRect.y }, false);
			SDL_RenderCopy(m_renderer, withSplit.getTexture(), NULL, withSplit.getRect());
			SDL_RenderCopy(m_renderer, winText, NULL, &winRect);
			SDL_RenderCopy(m_renderer, loseText, NULL, &loseRect);

			splitHandPay = 0;
		}
	}

	askForReplay(m_player.getUserBalance() + regularHandPay + splitHandPay);
}

void Game::loop() {
	SDL_ShowCursor(SDL_DISABLE);

	while (m_event.type != SDL_QUIT) {
		SDL_WaitEvent(&m_event);
		SDL_RenderClear(m_renderer);

		SDL_GetMouseState(&m_mousePoint.x, &m_mousePoint.y);
		SDL_Rect mousePointerRect = Helper::getOffsetRect(m_mousePoint.x - 12, m_mousePoint.y, m_mousePointer);


		if (m_gameScene == GameScene::START) {
			SDL_RenderCopy(m_renderer, m_emptyGameBg, NULL, NULL);
			reset();
			startScreen();
		}
		else if (m_gameScene == GameScene::BALANCECHECK) {
			SDL_RenderCopy(m_renderer, m_emptyGameBg, NULL, NULL);
			askForInitialBalance();
		}
		else if (m_gameScene == GameScene::BETCHECK) {
			SDL_RenderCopy(m_renderer, m_emptyGameBg, NULL, NULL);
			askForBetValue();
		}
		else if (m_gameScene == GameScene::GAMELOOP) {
			SDL_RenderCopy(m_renderer, m_gameBg, NULL, NULL);
			TextTexture naturalPayoutText(m_renderer, m_smallFont);
			naturalPayoutText.setPosition(SDL_Point{ static_cast<int> (m_windowWidth * 0.5), static_cast<int> (m_windowHeight * .1) });


			if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) != 21 && !gameHasStarted) {
				naturalPayoutText.setText("You have a natural. You Win!");
				m_dealer.revealHand();
				updateTable();
				askForReplay(m_player.getUserBalance() + (int)(round(m_betValue * 1.5f)));
				SDL_RenderCopy(m_renderer, naturalPayoutText.getTexture(), NULL, naturalPayoutText.getRect());
			}
			//dealer natural
			else if (User::checkHandValue(m_player.getCards()) != 21 && User::checkHandValue(m_dealer.getCards()) == 21 && !gameHasStarted) {
				naturalPayoutText.setText("The dealer has a natural. You Lose.");
				m_dealer.revealHand();
				updateTable();
				askForReplay(m_player.getUserBalance());
				SDL_RenderCopy(m_renderer, naturalPayoutText.getTexture(), NULL, naturalPayoutText.getRect());
			}
			//tie
			else if (User::checkHandValue(m_player.getCards()) == 21 && User::checkHandValue(m_dealer.getCards()) == 21 && !gameHasStarted) {
				naturalPayoutText.setText("The game is a tie and will now reset.");
				m_dealer.revealHand();
				updateTable();
				askForReplay(m_player.getUserBalance() + m_betValue);
				SDL_RenderCopy(m_renderer, naturalPayoutText.getTexture(), NULL, naturalPayoutText.getRect());
			}
			else if (!m_player.getIsStanding() && User::checkHandValue(m_player.getCards()) <= 21
				&& m_player.getIsPlayingRegularHand())
			{
				gameHasStarted = true;
				updateMoveOptions();
				updateTable();
			}
			else if (!m_player.getIsStandingOnSplit() && m_player.getIsSplit() && User::checkHandValue(m_player.getSplitCards()) <= 21
				&& !m_player.getIsPlayingRegularHand())
			{
				updateMoveOptions(true);
				updateTable();
			}

			//dealer hits till above 16
			while (m_player.getIsStanding() && User::checkHandValue(m_dealer.getCards()) <= 17)
				m_dealer.addCardToHand(&m_dealer.getCards(), m_deck.takeCardFromFront());

			if (!m_player.getIsSplit()) {
				if (m_player.getIsStanding() || User::checkHandValue(m_player.getCards()) > 21) {
					m_dealer.revealHand();
					updateTable();
					//payout only for normal hand
					payout();
				}
			}


			else if (m_player.getIsSplit()) {
				if ((m_player.getIsStanding() || User::checkHandValue(m_player.getCards()) > 21)
					&& (m_player.getIsStandingOnSplit() || User::checkHandValue(m_player.getSplitCards()) > 21)) {
					m_dealer.revealHand();
					updateTable();
					//payout for both hands.
					payout(true);
				}

			}
		}
		SDL_RenderCopy(m_renderer, m_mousePointer, NULL, &mousePointerRect);
		SDL_RenderPresent(m_renderer);
	}
}

void Game::quit() {
	std::cout << "Everything's A-OK!" << std::endl;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	Mix_Quit();
	TTF_Quit();
	atexit(SDL_Quit);
}