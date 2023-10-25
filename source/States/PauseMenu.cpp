#include "PauseMenu.h"
#include "../States/GameState.h"

PauseMenu::PauseMenu(State& parentState) 
{
	this->parentState = &parentState;

	btnPlay = new Button(sf::Vector2f(200, 600), sf::Vector2f(300, 100), "Resume");
	btnPlay->PushToObject(btnPlay, this);

	btnExit = new Button(sf::Vector2f(200, 100), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	invisibleWall = new RectangleShape(WINDOW_SIZE);
	invisibleWall->setPosition(0, 0);
	invisibleWall->setFillColor(Color(91,91,91,50));
}	

PauseMenu::~PauseMenu()
{
	ResourceManager::unloadTexture("Blue_Background.png");
}

void PauseMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	parentState->draw(target, states);
	target.draw(*invisibleWall);
}

void PauseMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnPlay->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::None;
	}
	else
		if (btnExit->isLeftClicked(event, MousePos))
		{
			CurrentState = States::KillMe;
			parentState->CurrentState = States::KillMe;
			parentState->parentState->CurrentState = States::None;
		}
}