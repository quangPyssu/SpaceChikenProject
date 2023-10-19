#include "GameState.h"

GameState::GameState() 
{
	textureBack = ResourceManager::getTexture("Blue_Blank_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	Player* player = new Player();
	player->PushToObject(player,this);
}

GameState::~GameState()
{
	ResourceManager::unloadTexture("Blue_Blank_Background.png");
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

void GameState::takeTimeCurrent()
{
}