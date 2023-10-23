#include "Player.h"

Player::Player()
{
	hitbox.setOutlineThickness(1);
	isFiring = false;

	texturePlayer = ResourceManager::getTexture("Battlecruiser_Base.png");	

	hitbox.setSize(sf::Vector2f(texturePlayer.getSize().x/3, texturePlayer.getSize().y/2));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);

	{
		animations.push_back(new Animation(10, 10, 6, 1, { 0,0 }, { 0,0.5 }, Vector2f( 0, texturePlayer.getSize().y / 4 ), "FireJet.png"));
		animations.back()->setRotation(90);
		animations.back()->PushToObject(animations.back(), this);
	}

	{
		sprites.push_back(new SpriteOnly("Battlecruiser_Base.png",Vector2f(0,0)));
		sprites.back()->PushToObject(sprites.back(), this);
		sprites.back()->setOrigin({ 0.5, 0.5 });
	}

	HitPoints = 2;
}

Player::~Player()
{
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::drawCurrent(target, states);
	target.draw(hitbox);
}

void Player::updateCurrent(Event& event, Vector2f& MousePos)
{
	setPosition(MousePos);
	hitbox.setPosition(MousePos);	
}

void Player::takeTimeCurrent()
{	
	Entity::takeTimeCurrent();

	reloadFrameID++;
	reloadFrameID=min(reloadFrameID,reloadFrameIDMax);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (reloadFrameID == reloadFrameIDMax)
		{
			reloadFrameID = 0;
			isFiring = true;
			ResourceManager::MakeSound("(laser).ogg");
		}
		else
		{
			isFiring = false;
		}
	}
}

void Player::resetGun()
{
	reloadFrameID = 0;
	isFiring = false;
}

