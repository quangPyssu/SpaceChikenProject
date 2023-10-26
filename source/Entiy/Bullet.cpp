#include "Bullet.h"

Bullet::Bullet(BulletType type,Vector2f StartPosition) : type(type)
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);

	switch (type)
	{
	case Constants::Player_Bullet_Normal:
	{
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Colors::red);
		hitbox.setOutlineThickness(1);
		hitbox.setSize({ 5,20 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		animations.push_back(new Animation(10, 11, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Bullet.png"));
		animations.back()->setRotation(-90);
		animations.back()->PushToObject(animations.back(), this);

		playSound("(laser).ogg");

		isBulletDestructible = true;
		Damage = 20;

		Velocity = { 0, -400 };
		Acceleration = { 0,-25 };
		break;
	}

	case Constants::Enemy_Bullet_Normal:
	{
		hitbox.setFillColor(Colors::purple);
		hitbox.setSize({ 5,20 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		sprites.push_back(new SpriteOnly("egg.png", Vector2f(0, 0)));
		sprites.back()->PushToObject(sprites.back(), this);
		sprites.back()->setOrigin({ 0.5, 0.5 });
		sprites.back()->setScale(0.5);

		isBulletDestructible = true;
		Damage = 1;

		Velocity = { 0, 100 };
		Acceleration = { 0,0 };
		break;
	}

	case Constants::Player_Laser_Destroyer:
	{
		//hitbox.setFillColor(Colors::red);
		//hitbox.setOutlineColor(Colors::red);
		//hitbox.setOutlineThickness(1);

		hitbox.setFillColor(Colors::trans);
		hitbox.setSize({ 20,1000 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y);

		animations.push_back(new Animation(10,4, 1,1, { 0,0 }, { 0,0.5 }, Vector2f(0,-30), "QuicklyBeam.png"));
		animations.back()->setScale({4.3,1});
		animations.back()->setRotation(-90);
		animations.back()->PushToObject(animations.back(), this);

		playSound("laserSmall.ogg");
		setTimer(10, 30);

		isBulletDestructible = false;
		Damage = 1;

		Velocity = { 0, 0 };
		Acceleration = { 0,0 };
		break;
	}

	default:
		break;

	}
}

void Bullet::takeTimeCurrent()
{
	Entity::takeTimeCurrent();

}





