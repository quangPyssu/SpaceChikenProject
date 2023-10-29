#include "BulletPattern.h"

BulletPattern::BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, int total, float width, int widthCnt)
{
	this->bulletManager = &bulletManager;

	Position = Vector2f(Position.x * SCALE, Position.y * SCALE);
	Velocity = Vector2f(Velocity.x * SCALE, Velocity.y * SCALE);
	Acceleration = Vector2f(Acceleration.x * SCALE, Acceleration.y * SCALE);
	width = width * SCALE;

	setVelocity(Velocity);
	setAcceleration(Acceleration);
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
			bulletManager.addBullet(Enemy_Bullet_Normal, Position);
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
			bulletManager.addBullet(Enemy_Bullet_Normal, Position);
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

	case Enemy_Normal_Shower:
	{
		if (width <= 0) width = 200;

		for (int i = 0; i < total; i++)
		{
			int x = (rand() % (int)(width*2)) - width;
			int y = (rand() % (int)(width*2)) - width;
			bulletManager.addBullet(Enemy_Bullet_Normal, Position+Vector2f(x,y));
			Bullet* tmp = bulletManager.BulletList.back();
			tmp->RotationDivation = 100;

			entityList.push_back(tmp);
		}

		setRotation(270);
		rotationType = WithOwnVelocity;

		setUpPattern(Shower);
		setTimer(0, -1);
	}
			break;	
	
	case Enemy_Normal_Firework:
	{
		for (int i = 0; i < total; i++)
		{
			bulletManager.addBullet(Enemy_Bullet_Normal, Position);
			Bullet* tmp = bulletManager.BulletList.back();
			tmp->RotationDivation = 90;
			//tmp->ApplyPhysics();
			entityList.push_back(tmp);
		}

		setRotation(270);
		rotationType = WithOwnVelocity;
		setUpPattern(Firework);
		setTimer(0, -1);
	}
			break;

	default:
		break;
	}

}

BulletPattern::BulletPattern(BulletPatternType type, BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,
	int total, float width, int widthCnt, RotationType rotationType) : BulletPattern(type, bulletManager, Position, Velocity, Acceleration, total, width, widthCnt)
{
	this->rotationType = rotationType;
}







