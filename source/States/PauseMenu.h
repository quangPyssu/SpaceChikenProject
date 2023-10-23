#pragma once

#include "State.h"
#include "../Button.h"
#include "../Animation/SpriteOnly.h"

class PauseMenu : public State
{
public:
	PauseMenu(State& parentState);
	~PauseMenu();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:

	Button* btnPlay;
	Button* btnExit;

	RectangleShape* invisibleWall;
};

