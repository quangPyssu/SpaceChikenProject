
#include "Player.h"

Player::Player()
{
	hitbox.setOutlineThickness(1);
	isFiring = false;
	isSpecialing = false;
	isInvincibleWhenFlicker = true;
	totalTime = 50;

	texturePlayer = ResourceManager::getTexture("Battlecruiser_Base.png");	

	hitbox.setSize(sf::Vector2f(texturePlayer.getSize().x/3, texturePlayer.getSize().y/2));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);

	{
		/*animations.push_back(new Animation(10, 10, 6, 1, { 0,0 }, { 0,0.5 }, Vector2f( 0, texturePlayer.getSize().y / 4 ), "FireJet.png"));
		animations.back()->setRotationDivation(90);
		animations.back()->PushToObject(animations.back(), this);*/

		animations.push_back(new Animation(20, 8, 1, 1, { 0,0 }, { 0.5,0.55 }, Vector2f(0, 0), "Battlecruiser_Engine.png"));
		animations.back()->setScale({ 1,1.7 });
		animations.back()->PushToObject(animations.back(), this);
	}

	{
		sprites.push_back(new SpriteOnly("Battlecruiser_Base.png",Vector2f(0,0)));
		sprites.back()->PushToObject(sprites.back(), this);
		sprites.back()->setOrigin({ 0.5, 0.5 });
	}

	HitPoints = HitPointsMax = 10;

	sf::Mouse::setPosition(Vector2i(WINDOW_SIZE.x/2,WINDOW_SIZE.y*2/3));
	setPosition(WINDOW_SIZE);
	hitbox.setPosition(getPosition());
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
	PlayerCurPos = MousePos;
}

void Player::takeTimeCurrent()
{	
	Entity::takeTimeCurrent();

	reloadFrameID++;
	reloadFrameID=min(reloadFrameID,reloadFrameIDMax);

	specialFrameID++;
	specialFrameID=min(specialFrameID, specialFrameIDMax);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (reloadFrameID == reloadFrameIDMax)
		{
			reloadFrameID = 0;
			isFiring = true;
		}
		else
		{
			isFiring = false;
		}
	} 

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (hasSpeacial && specialFrameID == specialFrameIDMax)
		{
			specialFrameID = 0;
			isSpecialing = true;
			hasSpeacial--;
		}
		else isSpecialing = false;

	}
}

void Player::resetGun()
{
	reloadFrameID = 0;
	isFiring = false;
}

void Player::resetSpecial()
{
	specialFrameID = 0;
	isSpecialing = false;
}

void Player::addDeathAnimation()
{
	Entity::addDeathAnimation();
	animations.push_back(new Animation(6, 18, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Battlecruiser_Destruction.png", 95));
	PushToObject(animations.back(), this);

	playSound("PlayerExplode.ogg");
}

void Player::atHalfHealth()
{
	animations.push_back(new Animation(10, 8, 1, 1, { 0,0 }, { 0.5,0 }, Vector2f(0, 0), "Explosion.png",150));
	animations.back()->PushToObject(animations.back(), this);

	playSound("PlayerExplode.ogg");
}

void Player::atQuarterHealth()
{
	animations.push_back(new Animation(10, 8, 1, 1, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 150));
	animations.back()->PushToObject(animations.back(), this);
	playSound("PlayerExplode.ogg");
}