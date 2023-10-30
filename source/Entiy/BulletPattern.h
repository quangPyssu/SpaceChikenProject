#pragma once

#include "Bullet.h"
#include "../Tools/BulletManager.h"
#include "../Tools/Pattern.h"
#include "../Animation/WarningZone.h"

enum BulletPatternType
{
	Enemy_Normal_Circle,
	Enemy_Normal_Square,
	Enemy_Normal_Shower,
	Enemy_Normal_Firework,
};

class BulletPattern :  public Pattern
{
	public:
	BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
		int total, float width, int widthCnt,WarningZone& warningZong,int timerStart,int timerEnd);
	BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, 
		int total, float width, int widthCnt, WarningZone& warningZong, int timerStart, int timerEnd, RotationType rotationType);

	private:

	BulletManager* bulletManager = nullptr;
	WarningZone* warningZone = nullptr;
};
