#include "Enemy.h"

Enemy::Enemy(EnemyType type, Vector2f StartPosition) 
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);
	Texture texture;

	switch (type)
	{
	case Enemy_Chicken_1:
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Color::Blue);
		hitbox.setOutlineThickness(1);
		hitbox.setSize({ 50,50 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		texture = ResourceManager::getTexture("ThanGa.png");

		animations.push_back(new Animation(2, 50, 1, 0.7, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ThanGa.png"));
		animations.back()->makePingPong();
		animations.back()->PushToObject(animations.back(), this);

		texture = ResourceManager::getTexture("Cursor2.png");

		HitPoints = 1;

		ApplyPhysics();
		Velocity = { 50,(float) 0+rand()%20+10 };
		Acceleration = { 0,0 };

		reloadFrameIDMax = 150;
		break;
	default:
		break;
	}
}

void Enemy::takeTimeCurrent()
{
	Entity::takeTimeCurrent();

	reloadFrameID++;
	reloadFrameID = min(reloadFrameID, reloadFrameIDMax);

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

void Enemy::resetGun()
{
	reloadFrameID = 0;
	isFiring = false;
}