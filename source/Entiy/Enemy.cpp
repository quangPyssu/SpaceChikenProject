#include "Enemy.h"

Enemy::Enemy(Vector2f StartPosition) 
{
	setPosition(StartPosition);
	hitbox.setPosition(StartPosition);
	type = EnemyType_Chicken_1;
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
	default:
		break;
	}
}