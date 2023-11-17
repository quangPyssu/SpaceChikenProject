
#include "Player.h"

Player::Player()
{
	hitbox.setOutlineThickness(1);
	isFiring = false;
	isSpecialing = false;
	isInvincibleWhenFlicker = true;
	totalTime = 50;

	texturePlayer = ResourceManager::getTexture("Battlecruiser_Base.png");	

	setHitBox(sf::Vector2f(texturePlayer.getSize().x/5*SCALE, texturePlayer.getSize().y/3*SCALE));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);

	Constants::PlayerHitboxSize = hitbox.getSize();

	{
		animations.push_back(new Animation(20, 8, 1, 1, { 0,0 }, { 0.5,0.6 }, Vector2f(0, 0), "Battlecruiser_Engine.png"));
		animations.back()->setScale({ 0.8,1.4 });
		animations.back()->PushToObject(animations.back(), this);
	}

	{
		sprites.push_back(new SpriteOnly("Battlecruiser_Base.png",Vector2f(0,0)));
		sprites.back()->PushToObject(sprites.back(), this);
		sprites.back()->setOrigin({ 0.5, 0.5 });
	}

	HitPoints = HitPointsMax = PlayerMaxHP;

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

	// mouse scroll to change weapon

	if (event.type == Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			CurrentWeapon++;
			CurrentWeapon %= 2;

		}
		else if (event.mouseWheelScroll.delta < 0)
		{
			CurrentWeapon--;
			CurrentWeapon += 2;
			CurrentWeapon %= 2;
		}
		reloadFrameIDMax = WeaponUnlocked[EquipedWeapon[CurrentWeapon]].ss;
		resetGun();
	}
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
		if (specialFrameID == specialFrameIDMax)
		{
			specialFrameID = 0;
			isSpecialing = true;
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