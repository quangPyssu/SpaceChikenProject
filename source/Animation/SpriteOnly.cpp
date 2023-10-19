#include "SpriteOnly.h"

SpriteOnly::SpriteOnly(const std::string& i_texture_location)
{
	texture = ResourceManager::getTexture(i_texture_location);
	sprite.setTexture(texture);
}

void SpriteOnly::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void SpriteOnly::setRotation(float angle)
{
	sprite.setRotation(angle);
}

void SpriteOnly::setScale(float x)
{
	sprite.setScale(x, x);
}

void SpriteOnly::setOrigin(Vector2f Origin)
{
	sprite.setOrigin(Vector2f(Origin.x * texture.getSize().x, Origin.y * texture.getSize().y));
}

void SpriteOnly::setPosition(Vector2f Position)
{
	sprite.setPosition(Position);
}