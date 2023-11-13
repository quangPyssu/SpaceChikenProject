#include "SettingMenu.h"
#include "../States/GameState.h"

SettingMenu::SettingMenu(State& parentState) 
{
	this->parentState = &parentState;

	btnExit = new Button(sf::Vector2f(WINDOW_SIZE.x/4*3, 600), sf::Vector2f(200, 100), "Quit");
	btnExit->PushToObject(btnExit, this);

	background.setTexture(ResourceManager::getTexture("Blue_Background.png"));
	background.setScale(getScale::getScaleMin((Vector2f) background.getTexture()->getSize(), WINDOW_SIZE));

	sliderMaster = new Slider(sf::Vector2f(WINDOW_SIZE.x / 4 , 100), sf::Vector2f(200, 50), Color::Green, grey, "Master Volume:", Constants::masterVolume, 100);
	sliderMaster->PushToObject(sliderMaster, this);

	sliderMusic = new Slider(sf::Vector2f(WINDOW_SIZE.x / 4 , 175), sf::Vector2f(200, 50), Color::Green, grey, "Music Volume:", Constants::musicVolume, 100);
	sliderMusic->PushToObject(sliderMusic, this);

	sliderSound = new Slider(sf::Vector2f(WINDOW_SIZE.x / 4 , 250), sf::Vector2f(200, 50), Color::Green, grey, "Sfx Volume:", Constants::soundVolume, 100);
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
