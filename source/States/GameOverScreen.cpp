#include "GameOverScreen.h"
#include "../States/GameState.h"

GameOverScreen::GameOverScreen(State& parentState) 
{
	this->parentState = &parentState;

	textureBack=ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(Vector2f(textureBack.getSize()),WINDOW_SIZE));

	btnPlay = new Button(sf::Vector2f(200, 600), sf::Vector2f(600, 100), "Restart Level");
	btnPlay->PushToObject(btnPlay, this);

	btnExit = new Button(sf::Vector2f(200, 100), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	invisibleWall = new RectangleShape(WINDOW_SIZE);
	invisibleWall->setPosition(0, 0);
	invisibleWall->setFillColor(Color(91,91,91,50));
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
			parentState->parentState->CurrentState = States::None;
		}
}
