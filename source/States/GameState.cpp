#include "GameState.h"

GameState::GameState()
{
	textureBack = ResourceManager::getTexture("VerticalSpace.png");
	backgroundSprite.setTexture(textureBack);


	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("VerticalSpace.png");
}

void GameState::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}	

void GameState::updateCurrent(Event& event, Vector2f& MousePos)
{
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
		isDead = true;
}

void GameState::takeTimeCurrent(Time& dt)
{
}