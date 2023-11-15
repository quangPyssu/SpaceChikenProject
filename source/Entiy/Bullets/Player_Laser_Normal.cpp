#include "../Bullet.h"

Player_Laser_Normal::Player_Laser_Normal(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);	
	//hitbox.setOutlineColor(red);
	//hitbox.setOutlineThickness(1);

	animations.push_back(new Animation(10, 4, 1, 1, { 0,0 }, { 0,0.5 }, Vector2f(0, -30), "QuicklyBeam.png"));
	animations.back()->setScale({ 5.5,0.75 });
	animations.back()->setRotationDivation(-90);
	animations.back()->PushToObject(animations.back(), this);

	Vector2f size = { animations.back()->getSize().y,animations.back()->getSize().x };
	hitbox.setSize(size*Vector2f(0.4,1));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y);

	playSound("laserSmall.ogg");
	setTimer(0, 30);

	isBulletDestructible = false;
	Damage = 1;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Player_Laser_Normal;
}

void Player_Laser_Normal::addDeathAnimation()
{
	Entity::addDeathAnimation();
}