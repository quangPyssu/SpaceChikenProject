#pragma once

#include "Bullet.h"
#include "../Tools/BulletManager.h"
#include "../Tools/Pattern.h"
#include "../Animation/WarningZone.h"

class BulletPattern :  public Pattern
{
	public:
	BulletPattern(BulletType bulletType, PatternType patternType, RotationType rotationType,
		BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, bool PhysicsEnable,
		int total, float width, int widthCnt,WarningZone& warningZong,int timerStart,int timerEnd,double thisScale);
	~BulletPattern();


	private:

	BulletManager* bulletManager = nullptr;
	WarningZone* warningZone = nullptr;
};
