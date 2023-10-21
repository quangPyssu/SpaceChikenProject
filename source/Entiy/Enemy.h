#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	public:
	Enemy(EnemyType type, Vector2f StartPosition);

	//void takeTimeCurrent() override;

};

