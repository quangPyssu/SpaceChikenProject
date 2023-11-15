#include "GameOverScreen.h"
#include "../States/GameState.h"

GameOverScreen::GameOverScreen(State& parentState) 
{
	this->parentState = &parentState;

	textureBack=ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(Vector2f(textureBack.getSize()),WINDOW_SIZE));

	btnPlay = new Button(sf::Vector2f(WINDOW_SIZE.x/5, WINDOW_SIZE.y /3 + 250), sf::Vector2f(600, 100), "Restart Level");
	btnPlay->PushToObject(btnPlay, this);

	btnExit = new Button(sf::Vector2f(WINDOW_SIZE.x/5+650, WINDOW_SIZE.y / 3+250), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	SubTitle* TitleGameOver = new SubTitle({ 0,WINDOW_SIZE.y / 3 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.3,0.5 }, 40, white, "GAME OVER", "neuro",-1);
	SubTitleList.push_back(TitleGameOver);
	PushToObject(SubTitleList.back(), this);


	CurrentState = States::None;
}	

GameOverScreen::~GameOverScreen()
{
	ResourceManager::unloadTexture("Blue_Background.png");

}

void GameOverScreen::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}

void GameOverScreen::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnPlay->isLeftClicked(event, MousePos))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::KillMe;
		parentState->parentState->CurrentState = States::NewGame;
	}
	else
		if (btnExit->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			CurrentState = States::KillMe;
			parentState->CurrentState = States::KillMe;
			parentState->parentState->CurrentState = States::KillMe;
			parentState->parentState->parentState->CurrentState = States::None;
		}
}
