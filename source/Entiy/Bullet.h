#pragma once
#include "Entity.h"

enum BulletType { Player_Bullet_Normal, Enemy_Bullet_Normal, Player_Bullet_Destroyer, Player_Laser_Destroyer
	, Enemy_Astroid
};

class Bullet : public Entity
{
	public:
	Bullet(BulletType type,sf::Vector2f StartPosition);

	void takeTimeCurrent() override;

	BulletType type;

	bool isBulletDestructible = true;
};
