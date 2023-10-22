#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	public:
	Enemy(EnemyType type, Vector2f StartPosition);

	void takeTimeCurrent() override;
	bool isFiring = false;

	void resetGun();

private:
	
		short unsigned int reloadFrameID = 0;
		short unsigned int reloadFrameIDMax = 50;
};

