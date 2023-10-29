#pragma once
#include "Entity.h"

enum EnemyType { Enemy_Chicken_1, Fast, Tank, Boss };

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
		EnemyType type;

		void addDeathAnimation() override;

		friend class EnemyManager;
};

