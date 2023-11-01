#include "BulletPattern.h"

BulletPattern::BulletPattern(BulletType bulletType, PatternType patternType, RotationType rotationType, 
	BulletManager& bulletManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,
	int total, float width, int widthCnt, WarningZone& warningZong, int timerStart, int timerEnd)
{
	this->bulletManager = &bulletManager;
	this->warningZone = &warningZong;
	this->type = patternType;
	this->rotationType = rotationType;

	Position = Vector2f(Position.x * SCALE, Position.y * SCALE);
	Velocity = Vector2f(Velocity.x * SCALE, Velocity.y * SCALE);
	Acceleration = Vector2f(Acceleration.x * SCALE, Acceleration.y * SCALE);
	width = width * SCALE;

	setVelocity(Velocity);
	setAcceleration(Acceleration);
	setPosition(Position);	
	HitPoints = 9999;

	this->total = total;
	this->width = width;
	this->widthCnt = widthCnt;

	setVelocity({ (float)SCALE * Velocity.x,(float)SCALE * Velocity.y });
	Destructible = true;

	for (int i=0;i<total;i++)
	{
		bulletManager.addBullet(bulletType, Position);
		Bullet* tmp = bulletManager.BulletList.back();
		entityList.push_back(tmp);
	}

	switch (bulletType)
	{
		case Enemy_Bullet_Normal:
		{
			for (int i = 0; i < total; i++)
			{
				Entity* tmp = entityList[i];
				tmp->RotationDivation = 90;
			}

		}
			break;

		case Astroid:
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

			warningZone->addWarningZone(*shape, timerStart);
		}
			break;

		case Square:
		{
			if (rotationType == defaultRotation) this->rotationType = WithVelocity;
			setUpPattern(Square);

			RectangleShape* shape = new RectangleShape();
			shape->setSize(Vector2f(width, (width * (total / widthCnt) / width)));
			shape->setPosition(Position);
			shape->setFillColor(Colors::yellow);

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
			if (bulletType == Enemy_Bullet_Normal) setRotation(270);
		}
			break;
	}

	setTimer(timerStart, timerEnd);
}







