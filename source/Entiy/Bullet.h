#pragma once
#include "Entity.h"

enum BulletType { BulletType_Enemy_Egg, BulletType_Astroid, BulletType_Player_Normal, BulletType_Player_Laser_Destroyer};

class Bullet : public Entity
{
	public:
	Bullet(Vector2f StartPosition);

	void takeTimeCurrent() override;

	BulletType type;

	bool isBulletDestructible = true;
};

class BulletFactory
{
	public:
		static Bullet* createBullet(BulletType type, Vector2f StartPosition);
};


class Player_Bullet_Normal : public Bullet
{
	public:
	Player_Bullet_Normal(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;

	void addDeathAnimation() override;
};

class Player_Laser_Destroyer : public Bullet
{
	public:
	Player_Laser_Destroyer(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;

	void addDeathAnimation() override;
};

class Enemy_Bullet_Egg : public Bullet
{
	public:
	Enemy_Bullet_Egg(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;

	void addDeathAnimation() override;
};

class Astroid : public Bullet
{
	public:
	Astroid(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;

	void addDeathAnimation() override;
};