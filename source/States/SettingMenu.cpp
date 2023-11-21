#include "SettingMenu.h"
#include "../States/GameState.h"

SettingMenu::SettingMenu(State& parentState) 
{
	this->parentState = &parentState;

	btnExit = new Button(sf::Vector2f(WINDOW_SIZE.x/4*3, WINDOW_SIZE.y/4*3), sf::Vector2f(100, 50)*SCALE, "Quit");
	btnExit->PushToObject(btnExit, this);

	background.setTexture(ResourceManager::getTexture("Blue_Background.png"));
	background.setScale(getScale::getScaleMax((Vector2f) background.getTexture()->getSize(), WINDOW_SIZE));

	sliderMaster = new Slider(sf::Vector2f(WINDOW_SIZE.x / 5 , 100 * SCALE), sf::Vector2f(100, 30) * SCALE, Color::Green, grey, "Master Volume:", Constants::masterVolume, 100);
	sliderMaster->PushToObject(sliderMaster, this);

	sliderMusic = new Slider(sf::Vector2f(WINDOW_SIZE.x / 5 , 140 * SCALE), sf::Vector2f(100, 30) * SCALE, Color::Green, grey, "Music Volume:", Constants::musicVolume, 100);
	sliderMusic->PushToObject(sliderMusic, this);

	sliderSound = new Slider(sf::Vector2f(WINDOW_SIZE.x / 5 , 180 * SCALE), sf::Vector2f(100, 30) * SCALE, Color::Green, grey, "Sfx Volume:", Constants::soundVolume, 100);
	sliderSound->PushToObject(sliderSound, this);

	CurrentState = States::None;
}	

SettingMenu::~SettingMenu()
{

}

void SettingMenu::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	parentState->draw(target, states);
	target.draw(background, states);
}	

void SettingMenu::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (btnExit->isLeftClicked(event, MousePos) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		CurrentState = States::KillMe;
		parentState->CurrentState = States::None;
	}

	State* tmp = this;
	while (tmp)
	{
		if (tmp->music)	tmp->setMusicVolume();
		tmp = tmp->parentState;
	}
}
