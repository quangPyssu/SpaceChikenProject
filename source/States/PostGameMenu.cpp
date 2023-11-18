#include "PostGameMenu.h"
#include "../States/GameState.h"

PostGameMenu::PostGameMenu(State& parentState) 
{
	this->parentState = &parentState;

	textureBack=ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(Vector2f(textureBack.getSize()),WINDOW_SIZE));

	btnPlay = new Button(sf::Vector2f(WINDOW_SIZE.x/5, WINDOW_SIZE.y /3 + 250), sf::Vector2f(600, 100), "Next Level");
	btnPlay->PushToObject(btnPlay, this);

	btnExit = new Button(sf::Vector2f(WINDOW_SIZE.x/5+650, WINDOW_SIZE.y / 3+250), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	SubTitle* TitleGameOver = new SubTitle({ 0,WINDOW_SIZE.y / 3 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.3,0.5 }, 40, white, "LEVEL CLEAR", "neuro",-1);
	SubTitleList.push_back(TitleGameOver);
	PushToObject(SubTitleList.back(), this);


	CurrentState = States::None;
}	

PostGameMenu::~PostGameMenu()
{

}

void PostGameMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}

void PostGameMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnPlay->isLeftClicked(event, MousePos))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::KillMe;
		parentState->parentState->CurrentState = States::KillMe;
		parentState->parentState->parentState->CurrentState = States::Load;


		switch (Constants::CurrentLevel)
		{
			case 0:
			{
				Constants::SpecialUnlocked[0].first = true;
				break;
			}

			case 1:
			{
				Constants::WeaponUnlocked[1].first = true;
				break;
			}

			case 2:
			{
				Constants::WeaponUnlocked[2].first = true;
				Constants::SpecialUnlocked[2].first = true;
				break;
			}

			case 3:
			{
				Constants::SpecialUnlocked[1].first = true;
				break;
			}

			default:
				break;
		}

		Constants::CurrentLevel++;
		if (Constants::CurrentLevel > 4) Constants::CurrentLevel = 0;

		CurrentData::writeData();
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
