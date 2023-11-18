#pragma once

#include "State.h"
#include "../Button.h"
#include "../Animation/SpriteOnly.h"

class PostGameMenu: public State
{
public:
	PostGameMenu(State& parentState);
	~PostGameMenu();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:

	Texture textureBack;

	Sprite backgroundSprite;

	Button* btnPlay;
	Button* btnExit;
};

