#include "BulletPattern.h"

BulletPattern::BulletPattern(BulletType bulletType, PatternType patternType, RotationType rotationType, 
	BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, bool PhysicsEnable,
	int total, float width, int widthCnt, WarningZone& warningZong, int timerStart, int timerEnd, double thisScale)
{
	this->bulletManager = &bulletManager;
	this->warningZone = &warningZong;
	this->type = patternType;
	this->rotationType = rotationType;

	if (PhysicsEnable) ApplyPhysics();

	Position = Vector2f(Position.x * thisScale, Position.y * thisScale);
	Velocity = Vector2f(Velocity.x * thisScale, Velocity.y * thisScale);
	Acceleration = Vector2f(Acceleration.x * thisScale, Acceleration.y * thisScale);
	width = width * thisScale;

	setVelocity(Velocity);
	setAcceleration(Acceleration);
	setPosition(Position);	
	HitPoints = 9999;

	this->total = total;
	this->width = width;
	this->widthCnt = widthCnt;
	Destructible = true;

	for (int i=0;i<total;i++)
	{
		bulletManager.addBullet(bulletType, Position);
		Bullet* tmp = bulletManager.BulletList.back();
		entityList.push_back(tmp);
	}

	switch (bulletType)
	{
		case BulletType_Enemy_Egg:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->RotationDivation = 90;
				tmp->setBaseRotation(90);
			}

		}
			break;

		case BulletType_Astroid:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->RotationDivation = rand() % 360;
			}
		}
			break;
	}

	switch (patternType)
	{
		case Circle:
		{
			if (rotationType == defaultRotation) this->rotationType = Spin;
			setUpPattern(Circle);

			CircleShape* shape = new CircleShape();
			shape->setRadius(width/2);
			shape->setOrigin(width/2, width/2);
			shape->setPosition(Position);
			shape->setOutlineThickness(2);
			shape->setFillColor(trans);
			shape->setOutlineColor(Colors::yellow);
			angleVelocity = 0.2;

			warningZone->addWarningZone(*shape, timerStart);
		}
			break;

		case Square:
		{
			if (rotationType == defaultRotation) this->rotationType = WithVelocity;
			setUpPattern(Square);

			RectangleShape* shape = new RectangleShape();
			shape->setSize(Vector2f(width, width));
			shape->setPosition(Position);
			shape->setOutlineColor(Colors::yellow);
			shape->setOutlineThickness(2);
			shape->setFillColor(trans);			

			warningZone->addWarningZone(*shape, timerStart);
		}
			break;

		case Shower:
		{
			if (rotationType == defaultRotation) this->rotationType = WithOwnVelocity;
			setUpPattern(Shower);
		}
			break;

		case Firework:
		{
			if (rotationType == defaultRotation) this->rotationType = WithOwnVelocity;
			setUpPattern(Firework);

			CircleShape* shape = new CircleShape();
			width = 20;
			shape->setRadius(width);
			shape->setOrigin(width, width);
			shape->setPosition(Position);
			shape->setFillColor(Colors::yellow);

			warningZone->addWarningZone(*shape, timerStart);
			if (bulletType == BulletType_Enemy_Egg) setRotation(270);
		}
			break;
	}

	setTimer(timerStart, timerEnd);

	
}







