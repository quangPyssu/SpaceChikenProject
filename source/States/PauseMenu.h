#pragma once

#include "State.h"

class PauseMenu : public State
{
public:
	PauseMenu(State& parentState);
	~PauseMenu();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:

	Button* btnPlay;
	Button* btnSetting;
	Button* btnExit;

	RectangleShape* invisibleWall;
};

