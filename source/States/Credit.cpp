#include "Credit.h"
#include "../States/GameState.h"

Credit::Credit(State& parentState) 
{
	this->parentState = &parentState;

	textureBack=ResourceManager::getTexture("Blue_Background.png");
	backgroundSprite.setTexture(textureBack);
	backgroundSprite.setScale(getScale::getScaleMax(Vector2f(textureBack.getSize()),WINDOW_SIZE));

	btnExit = new Button(sf::Vector2f(WINDOW_SIZE.x/5+650, WINDOW_SIZE.y / 3+250), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	SubTitle* TitleGameOver = new SubTitle({ 0,WINDOW_SIZE.y / 3 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.3,0.5 }, 40, white, "ThanK for Playng", "neuro",-1);
	SubTitleList.push_back(TitleGameOver);
	PushToObject(SubTitleList.back(), this);

	SubTitle* Cred = new SubTitle({ 0,WINDOW_SIZE.y / 6 }, Vector2f(WINDOW_SIZE.x, 200), trans, { 0.3,0.5 }, 20, white, "Made by NGUYEN VUONG QUANG", "neuro", -1);
	SubTitleList.push_back(Cred);
	PushToObject(SubTitleList.back(), this);


	CurrentState = States::None;
}	

Credit::~Credit()
{

}

void Credit::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite);
}

void Credit::updateCurrent(Event& event, Vector2f& MousePos)
{		
	if (btnExit->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
			CurrentState = States::KillMe;
			parentState->CurrentState = States::KillMe;
			parentState->parentState->CurrentState = States::KillMe;
			parentState->parentState->parentState->CurrentState = States::None;
	}
}
