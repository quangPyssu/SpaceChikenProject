#pragma once

#include "State.h"
#include "../Button.h"
#include "../Animation/SpriteOnly.h"

class Credit: public State
{
public:
	Credit(State& parentState);
	~Credit();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;

private:

	Texture textureBack;
	Sprite backgroundSprite;
	Button* btnExit;
};

