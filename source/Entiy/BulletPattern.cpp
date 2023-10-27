#include "BulletPattern.h"

BulletPattern::BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt)
{
	this->bulletManager = &bulletManager;

	setVelocity(Velocity);
	setPosition(Position);

	this->total = total;
	this->width = width;
	this->widthCnt = widthCnt;

	setVelocity({ (float)SCALE * Velocity.x,(float)SCALE * Velocity.y });
	Destructible = true;
	rotationType = Spin;	

	switch (type)
	{
	case Enemy_Normal_Circle:
	{	
		for (int i = 0; i < total; i++)
		{
			bulletManager.addBullet(Constants::Enemy_Bullet_Normal, Position);
			Bullet* tmp = bulletManager.BulletList.back();
			tmp->RotationDivation = 90;
			entityList.push_back(tmp);
		}

		setUpPattern(Circle);
		ApplyPhysics();
		angleVelocity = 0.1;
		setTimer(0, -1);
	}	
		break;

	case Enemy_Normal_Square:
	{
		for (int i = 0; i < total; i++)
		{
			bulletManager.addBullet(Constants::Enemy_Bullet_Normal, Position);
			Bullet* tmp = bulletManager.BulletList.back();
			tmp->RotationDivation = 90;
			entityList.push_back(tmp);
		}

		setUpPattern(Square);
		ApplyPhysics();		
		angleVelocity = 0.1;
		setTimer(0, -1);
	}
		break;

	default:
		break;
	}

}

BulletPattern::BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, 
	int total, float width, int widthCnt, RotationType rotationType) : BulletPattern(type, bulletManager, Position, Velocity, total, width, widthCnt)
{
	this->rotationType = rotationType;
}

void BulletPattern::takeTimeCurrent()
{
	Pattern::takeTimeCurrent();	
	//cout << entityList.size() << endl;
}







