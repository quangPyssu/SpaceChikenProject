#include "Enemy.h"

Enemy::Enemy(Vector2f StartPosition) 
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);
	type = EnemyType_Chicken_1;
}

Enemy::~Enemy()
{
	while (!Enemy_BulletPattern_queue.empty())
	{
		delete Enemy_BulletPattern_queue.front().ff;
		Enemy_BulletPattern_queue.pop();
	}
}

void Enemy::takeTimeCurrent()
{
	Entity::takeTimeCurrent();
	if (timerStart > 0) return;	

	if (reloadFrameID >= reloadFrameIDMax)
	{
		reloadFrameID = 0;
		isFiring = true;
		attackType = rand() % attackTypeMax;
		attack();
	}
	else
	{
		reloadFrameID++;
		isFiring = false;
	}

	additionalBehavior();
}

void Enemy::setBulletManager(BulletManager*& EnimesBullets, BulletManager*& EnimesBullets_Vulnerable)
{
	this->EnimesBullets = EnimesBullets;
	this->EnimesBullets_Vulnerable = EnimesBullets_Vulnerable;
}

void Enemy::resetGun()
{
	reloadFrameID = 0;
	isFiring = false;
}

Enemy* EnemyFactory::createEnemy(EnemyType type, Vector2f StartPosition)
{
	switch (type)
	{	
	case EnemyType_Chicken_1:
		return new Enemy_Chicken_1(StartPosition);
		break;
	case EnemyType_Boss_Chicken_1:
		return new Boss_Chicken_1(StartPosition);
		break;
	case EnemyType_UFO:
		return new UFO(StartPosition);
		break;
	case EnemyType_SpaceShip:
		return new SpaceShip(StartPosition);
		break;
	case EnemyType_Henterprise:
		return new Henterprise(StartPosition);
		break;
	case EnemyType_BlackHole:
		return new Black_Hole(StartPosition);
		break;
	case EnemyType_SemiVortex:
		return new Semi_Vortex(StartPosition);
		break;
	case EnemyType_SprialVortex:
		return new Spiral_Vortex(StartPosition);
		break;
	case EnemyType_Boss_Chicken_2:
		return new Boss_Chicken_2(StartPosition);
		break;
	default:
		break;
	}
}