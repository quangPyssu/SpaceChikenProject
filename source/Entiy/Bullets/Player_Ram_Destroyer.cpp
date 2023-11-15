#include "../Bullet.h"

Player_Ram_Destroyer::Player_Ram_Destroyer(Vector2f StartPosition) : Bullet(StartPosition)
{
	hitbox.setFillColor(Colors::trans);
	hitbox.setOutlineColor(Colors::red);
	hitbox.setOutlineThickness(1);
	
	animations.push_back(new Animation(30, 8, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Dreadnought_Shield.png"));
	animations.back()->PushToObject(animations.back(), this);

	setHitBox(animations.back()->getSize()*0.8);

	playSound("MarioStar.ogg");
	setTimer(0, 650);

	isBulletDestructible = false;
	Damage = 2;

	Velocity = { 0, 0 };
	Acceleration = { 0,0 };

	type = BulletType_Player_Ram_Destroyer;
}

void Player_Ram_Destroyer::addDeathAnimation()
{
	Entity::addDeathAnimation();
}