#pragma once

#include "Bullet.h"
#include "../Tools/BulletManager.h"
#include "../Tools/Pattern.h"

enum BulletPatternType
{
	Normal_Circle_Spin_NonKill
};

class BulletPattern :  public Pattern
{
	public:
	BulletPattern(BulletPatternType type, BulletManager& bulletManager,Vector2f Position,Vector2f Velocity);

	void takeTimeCurrent() override;
	private:

	BulletManager* bulletManager = nullptr;
};
