#include "Enemy.h"

Enemy::Enemy(EnemyType type, Vector2f StartPosition) 
{
	this->type = type;

	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);
	Texture texture;

	switch (type)
	{
	case Enemy_Chicken_1:
	{
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Color::Blue);
		hitbox.setOutlineThickness(1);
		hitbox.setSize({ 50,50 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		animations.push_back(new Animation(2, 50, 1, 0.35, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ChickenBody.png"));
		animations.back()->makePingPong();
		animations.back()->PushToObject(animations.back(), this);

		animations.push_back(new Animation(20, 25, 1, 1, { 0,0 }, { 0.5,1 }, Vector2f(0, 0), "ChickenFace.png"));
		animations.back()->setCurrentFrame(rand() % 25);
		animations.back()->makePingPong();
		animations.back()->PushToObject(animations.back(), this);

		HitPoints = 60;

		ApplyPhysics();
		Velocity = { 50,(float)0 + rand() % 20 + 10 };
		Acceleration = { 0,0 };

		reloadFrameID = rand() % 300;
		reloadFrameIDMax = 350;

		attackTypeMax = 1;
	}
		break;
	case Boss_Chicken_1:
	{
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Color::Blue);
		hitbox.setOutlineThickness(1);
		hitbox.setSize({ 112,112 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		animations.push_back(new Animation(2, 50, 1, 0.75, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "ChickenBody.png"));
		animations.back()->makePingPong();
		animations.back()->PushToObject(animations.back(), this);

		sprites.push_back(new SpriteOnly("ChickenFace1.png", Vector2f(0, 0)));
		sprites.back()->setScale(1.5);
		sprites.back()->setOrigin({ 0.5,1.2 });
		sprites.back()->setPosition({ 0,0 });
		sprites.back()->PushToObject(sprites.back(), this);

		HitPoints = 2500;

		ApplyPhysics();
		Velocity = { 50,20 };
		Acceleration = { 0,-1 };

		reloadFrameID = rand() % 300;
		reloadFrameIDMax = 350;

		attackTypeMax = 4;
	}
	break;
	}
}

void Enemy::addDeathAnimation()
{
	Entity::addDeathAnimation();
	switch (type)
	{	
	case Enemy_Chicken_1:		
	{
		animations.push_back(new Animation(10, 8, 1, 1.2, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
		PushToObject(animations.back(), this);

		playSound("chicken1a(die).ogg");		
	}
	break;

	case Boss_Chicken_1:
	{
		animations.push_back(new Animation(10, 8, 1, 5, WINDOW_SIZE, { 0.5,0.5 }, Vector2f(0, 0), "Explosion.png", 70));
		PushToObject(animations.back(), this);

		playSound("chicken1a(die).ogg");
	}
		break;
	}
}

void Enemy::takeTimeCurrent()
{
	Entity::takeTimeCurrent();
	if (timerStart > 0) return;

	reloadFrameID++;
	reloadFrameID = min(reloadFrameID, reloadFrameIDMax);

	if (reloadFrameID == reloadFrameIDMax)
	{
		reloadFrameID = 0;
		isFiring = true;
		attackType = rand() % attackTypeMax;
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