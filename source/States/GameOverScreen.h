#pragma once

#include "State.h"

class GameOverScreen : public State
{
public:
	GameOverScreen(State& parentState);
	~GameOverScreen();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:

	Texture textureBack;

	Sprite backgroundSprite;

	Button* btnPlay;
	Button* btnExit;
};

