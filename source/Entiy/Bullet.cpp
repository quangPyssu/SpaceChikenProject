#include "Bullet.h"

Bullet::Bullet(Vector2f StartPosition)
{
	setPosition(StartPosition);
	canFlicker = false;
	type = BulletType::BulletType_Player_Normal;
}

void Bullet::takeTimeCurrent()
{
	Entity::takeTimeCurrent();
}

void Bullet::setDamage(int damage)
{
	Damage = damage;
}

Bullet* BulletFactory::createBullet(BulletType type, Vector2f StartPosition)
{
	switch (type)
	{
	case BulletType::BulletType_Player_Normal:
		return new Player_Bullet_Normal(StartPosition);
		break;
	case BulletType::BulletType_Player_Laser_Normal:
		return new Player_Laser_Normal(StartPosition);
		break;
	case BulletType::BulletType_Player_Minigun:
		return new Player_Bullet_Minigun(StartPosition);
		break;
	case BulletType::BulletType_Player_Laser_Destroyer:
		return new Player_Laser_Destroyer(StartPosition);
		break;
	case BulletType::BulletType_Player_Ram_Destroyer:
		return new Player_Ram_Destroyer(StartPosition);
		break;
	case BulletType::BulletType_Enemy_Egg:
		return new Enemy_Bullet_Egg(StartPosition);
		break;
	case BulletType::BulletType_Enemy_Laser:
		return new Enemy_Laser_Flash(StartPosition);
		break;
	case BulletType::BulletType_Enemy_Laser_Destroyer:
		return new Enemy_Laser_Destroyer(StartPosition);
		break;
	case BulletType::BulletType_Enemy_Purple:
		return new Enemy_Bullet_Purple(StartPosition);
		break;
	case BulletType::BulletType_Enemy_Ram_Destroyer:
		return new Enemy_Ram_Destroyer(StartPosition);
		break;
	case BulletType::BulletType_Astroid:
		return new Astroid(StartPosition);
		break;
	default:
		return new Player_Bullet_Normal(StartPosition);
		break;
	}
}