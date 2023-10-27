#pragma once

#include "Bullet.h"
#include "../Tools/BulletManager.h"
#include "../Tools/Pattern.h"

enum BulletPatternType
{
	Enemy_Normal_Circle,
	Enemy_Normal_Square,
};

class BulletPattern :  public Pattern
{
	public:
	BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt);
	BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt, RotationType rotationType);

	void takeTimeCurrent() override;
	private:

	BulletManager* bulletManager = nullptr;
};
