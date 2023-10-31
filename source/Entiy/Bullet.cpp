#include "Bullet.h"

Bullet::Bullet(BulletType type,Vector2f StartPosition) : type(type)
{
	setPosition(StartPosition);
	canFlicker = false;

	switch (type)
	{
	case Player_Bullet_Normal:
	{
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Colors::red);
		hitbox.setOutlineThickness(1);
		hitbox.setSize({ 5,20 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		animations.push_back(new Animation(10, 11, 1, 0.5, { 0,0 }, { 0.5,0.5 }, Vector2f(0, 0), "Bullet.png"));
		animations.back()->setRotationDivation(-90);
		animations.back()->PushToObject(animations.back(), this);

		playSound("(laser).ogg");

		isBulletDestructible = true;
		Damage = 20;

		Velocity = { 0, -400 };
		Acceleration = { 0,-25 };
		break;
	}

	case Enemy_Bullet_Normal:
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

	case Player_Laser_Destroyer:
	{
		//hitbox.setFillColor(Colors::red);
		//hitbox.setOutlineColor(Colors::red);
		//hitbox.setOutlineThickness(1);

		hitbox.setFillColor(Colors::trans);
		hitbox.setSize(Vector2f( 20,(double) SCALE*1000 ));
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y);

		animations.push_back(new Animation(10,4, 1,1, { 0,0 }, { 0,0.5 }, Vector2f(0,-30), "QuicklyBeam.png"));
		animations.back()->setScale({5.5,1});
		animations.back()->setRotationDivation(-90);
		animations.back()->PushToObject(animations.back(), this);

		playSound("laserSmall.ogg");
		setTimer(10, 30);

		isBulletDestructible = false;
		Damage = 1;

		Velocity = { 0, 0 };
		Acceleration = { 0,0 };
		break;
	}

	case Astroid:
	{
		hitbox.setFillColor(Colors::trans);
		hitbox.setOutlineColor(Colors::purple);
		hitbox.setSize({ 80,80 });
		hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);

		int astroidId = rand() % 3;
		std::string path = "Astroid_" + std::to_string(astroidId) + ".png";
		sprites.push_back(new SpriteOnly(path, Vector2f(0, 0)));
		sprites.back()->PushToObject(sprites.back(), this);
		sprites.back()->setOrigin({ 0.5, 0.5 });
		sprites.back()->setScale(1);

		isBulletDestructible = true;
		HitPoints = 75;
		Damage = 5;

		Velocity = { 100, 100 };
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