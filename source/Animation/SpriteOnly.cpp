#include "SpriteOnly.h"

SpriteOnly::SpriteOnly(const std::string& i_texture_location) 
{
	texture = ResourceManager::getTexture(i_texture_location);
	sprite.setTexture(texture);
	sprite.setPosition({ -300,-300 });
	isRootSet = true;
}

SpriteOnly::SpriteOnly(const std::string& i_texture_location, sf::Vector2f divation) : divation(divation)
{
	texture = ResourceManager::getTexture(i_texture_location);
	sprite.setPosition({-300,-300});
	sprite.setTexture(texture);
	isRootSet = false;
}

void SpriteOnly::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void SpriteOnly::takeTimeCurrent()
{
	if (!isRootSet)	setPosition(this->Parent->getPosition()+divation);	

	setRotation(this->Parent->getRotation() + rotationDivation);
	sprite.setRotation(getRotation());
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

void SpriteOnly::setTransparency(float transparency)
{
	sprite.setColor(sf::Color(255, 255, 255, transparency));
}

void SpriteOnly::setTextureRect(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}