#pragma once
#include "../SceneNode.h"

class SpriteOnly :  public SceneNode
{
	public:
	SpriteOnly(const std::string& i_texture_location);

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setRotation(float angle);
	void setScale(float x);
	void setOrigin(Vector2f Origin);
	void setPosition(Vector2f Position);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
};

