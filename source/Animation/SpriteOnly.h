#pragma once
#include "../SceneNode.h"

class SpriteOnly :  public SceneNode
{
	public:
	SpriteOnly(const std::string& i_texture_location);
	SpriteOnly(const std::string& i_texture_location,sf::Vector2f divation);

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void takeTimeCurrent() override;

	void setRotationDivation(float angle) { rotationDivation = angle; }
	void setScale(float x);
	void setOrigin(Vector2f Origin);
	void setPosition(Vector2f Position);
	void setFlickerColor(sf::Color color) { sprite.setColor(color); }

	void setTextureRect(sf::IntRect rect);

	void setTransparency(float transparency);

	Vector2f getSize() const { return Vector2f(texture.getSize().x, texture.getSize().y); }

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f divation;
		float rotationDivation = 0;

		bool isRootSet = true;
};

