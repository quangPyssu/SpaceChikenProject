#pragma once

#include "Bullet.h"
#include "../Tools/EnemyManager.h"
#include "../Tools/Pattern.h"

enum EnemyPatternType
{
	Chicken_Circle,Chicken_Square
};

class EnemyPattern : public Pattern
{
	public:
	EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt);
	EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt,RotationType roationType);

	void takeTimeCurrent() override;
	private:

	EnemyManager* enemyManager;
};
