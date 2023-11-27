#pragma once

#include "State.h"
#include "../Tools/Slider.h"

class SettingMenu : public State
{
public:
	SettingMenu(State& parentState);
	~SettingMenu();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:
	Button* btnExit;

	Sprite background;
	

	Slider* sliderMaster;
	Slider* sliderMusic;
	Slider* sliderSound;
};

