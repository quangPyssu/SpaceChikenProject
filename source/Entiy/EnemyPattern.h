#pragma once

#include "Bullet.h"
#include "../Tools/EnemyManager.h"
#include "../Tools/Pattern.h"
#include "../Entiy/Enemy.h"

class EnemyPattern : public Pattern
{
	public:
	EnemyPattern(EnemyType enemyType, PatternType patternType, RotationType rotationType, EnemyManager& enemyManager,
		Vector2f Position, Vector2f Velocity, Vector2f Acceleration, int total, float width, int widthCnt);

	private:

	EnemyManager* enemyManager;
};
