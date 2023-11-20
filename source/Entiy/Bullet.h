#pragma once
#include "Entity.h"

enum BulletType { BulletType_Enemy_Egg, BulletType_Astroid, BulletType_Enemy_Laser, BulletType_Enemy_Purple,
	
	BulletType_Player_Normal, BulletType_Player_Minigun,
	BulletType_Player_Laser_Normal, BulletType_Player_Laser_Destroyer,BulletType_Player_Ram_Destroyer,

	BulletType_Enemy_Ram_Destroyer
};

class Bullet : public Entity
{
	public:
	Bullet(Vector2f StartPosition);

	void takeTimeCurrent() override;

	BulletType type;

	void setDamage(int damage);

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
};

class Player_Bullet_Minigun : public Bullet
{
	public:
	Player_Bullet_Minigun(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Player_Laser_Normal : public Bullet
{
	public:
	Player_Laser_Normal(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Player_Laser_Destroyer : public Bullet
{
	public:
	Player_Laser_Destroyer(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Player_Ram_Destroyer : public Bullet
{
	public:
	Player_Ram_Destroyer(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Enemy_Bullet_Egg : public Bullet
{
	public:
	Enemy_Bullet_Egg(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Enemy_Laser_Flash : public Bullet
{
	public:
		Enemy_Laser_Flash(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Enemy_Bullet_Purple : public Bullet
{
	public:
	Enemy_Bullet_Purple(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Enemy_Ram_Destroyer : public Bullet
{
	public:
	Enemy_Ram_Destroyer(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;
};

class Astroid : public Bullet
{
	public:
	Astroid(sf::Vector2f StartPosition);

	//void takeTimeCurrent() override;

	void addDeathAnimation() override;
};