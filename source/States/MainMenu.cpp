#include "MainMenu.h"

MainMenu::MainMenu()
{
	textureBack = ResourceManager::getTexture("Space_Sea.png");
	backgroundSprite.setTexture(textureBack);

	backgroundSprite.setScale(getScale::getScaleMax(sf::Vector2f(backgroundSprite.getTextureRect().width, backgroundSprite.getTextureRect().height), Constants::WINDOW_SIZE));

	btn_Quit = new Button(sf::Vector2f(200, 600), sf::Vector2f(200, 100), "Quit"); 
	btn_Quit->PushToObject(btn_Quit,this);

	btn_NewGame = new Button(sf::Vector2f(200, 100), sf::Vector2f(400, 100), "New Game");
	btn_NewGame->PushToObject(btn_NewGame, this);
}

MainMenu::~MainMenu()
{
}

void MainMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}	

void MainMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btn_Quit->isLeftClicked(event,MousePos)) isDead = true; else
		if (btn_NewGame->isLeftClicked(event, MousePos))
		{
			CurrentState = States::NewGame;
		}
}

void MainMenu::takeTimeCurrent(Time& dt)
{
}