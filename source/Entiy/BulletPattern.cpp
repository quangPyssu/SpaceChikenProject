#include "BulletPattern.h"

BulletPattern::BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity)
{
	this->bulletManager = &bulletManager;

	setVelocity(Velocity);
	setPosition(Position);

	switch (type)
	{
	case Normal_Circle_Spin_NonKill:
		Destructible = true;
		for (int i = 0; i < 360; i += 36)
		{
			bulletManager.addBullet(Constants::Enemy_Bullet_Normal, Position);
			Bullet* tmp = bulletManager.BulletList.back();
			entityList.push_back(tmp);
		}

		setUpPattern(Circle);

		ApplyPhysics();

		setVelocity({ 200,54 });

		angleVelocity = 0.1;
			
		setTimer(0,1000);			
		
		break;
	default:
		break;
	}

}

void BulletPattern::takeTimeCurrent()
{
	Pattern::takeTimeCurrent();	
}







