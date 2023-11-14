#include "../Bullet.h"

Player_Laser_Normal::Player_Laser_Normal(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setSize(Vector2f(20, (double)SCALE * 1000));
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y);

	animations.push_back(new Animation(10, 4, 1, 1, { 0,0 }, { 0,0.5 }, Vector2f(0, -30), "QuicklyBeam.png"));
	animations.back()->setScale({ 5.5,1 });
	animations.back()->setRotationDivation(-90);
	animations.back()->PushToObject(animations.back(), this);

	playSound("laserSmall.ogg");
	setTimer(0, 25);

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