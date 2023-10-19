#include "../SceneNode.h"
#include "../Animation/Animation.h"
#include "../Animation/SpriteOnly.h"

#pragma once

class Player : public SceneNode
{
	public:
	Player();
	~Player();

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(Event& event, Vector2f& MousePos) override;
	void takeTimeCurrent() override;

	private:
		vector <Animation*> animations;
		vector <Vector2f> animationPos;

		vector <SpriteOnly*> sprites;
		vector <Vector2f> spritePos;

		Texture texturePlayer;

		RectangleShape hitbox;
};

