#pragma once
#include "Entity.h"

class Bullet : public Entity
{
	public:
	Bullet(BulletType type, sf::Vector2f StartPosition);

	void takeTimeCurrent() override;

	BulletType type;
	bool Destructible = false;
};
