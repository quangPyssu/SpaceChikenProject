#include "PauseMenu.h"
#include "../States/GameState.h"

PauseMenu::PauseMenu(State& parentState) 
{
	this->parentState = &parentState;

	btnPlay = new Button(sf::Vector2f(200, 100), sf::Vector2f(300, 100), "Resume");
	btnPlay->PushToObject(btnPlay, this);

	btnSetting = new Button(sf::Vector2f(200, 225), sf::Vector2f(250, 100), "Setting");
	btnSetting->PushToObject(btnSetting, this);

	btnExit = new Button(sf::Vector2f(200, 350), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	invisibleWall = new RectangleShape(WINDOW_SIZE);
	invisibleWall->setPosition(0, 0);
	invisibleWall->setFillColor(Color(91,91,91,50));
}	

PauseMenu::~PauseMenu()
{
	delete invisibleWall;
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
			parentState->parentState->CurrentState = States::KillMe;
			parentState->parentState->parentState->CurrentState = States::None;
		}
		else
			if (btnSetting->isLeftClicked(event, MousePos))
			{
				CurrentState = States::Setting;
			}
}
