#include "EnemyPattern.h"

EnemyPattern::EnemyPattern(EnemyType enemyType, PatternType patternType, RotationType rotationType, EnemyManager& enemyManager,
	Vector2f Position, Vector2f Velocity, Vector2f Acceleration, int total, float width, int widthCnt)
{
	this->enemyManager = &enemyManager;
	this->type = patternType;
	this->rotationType = rotationType;

	Position = Vector2f(Position.x * SCALE, Position.y * SCALE);
	Velocity = Vector2f(Velocity.x * SCALE, Velocity.y * SCALE);
	Acceleration = Vector2f(Acceleration.x * SCALE, Acceleration.y * SCALE);
	width = width * SCALE;

	setVelocity(Velocity);
	setAcceleration(Acceleration);
	setPosition(Position);

	setVelocity(Velocity);
	setAcceleration(Acceleration);
	setPosition(Position);

	this->total = total;
	this->width = width;
	this->widthCnt = widthCnt;

	setVelocity({ (float)SCALE * Velocity.x,(float)SCALE * Velocity.y });
	Destructible = true;
	HitPoints = 99999;
	rotationType = Spin;

	for (int i = 0; i < total; i++)
	{
		enemyManager.addEnemy(enemyType);
		Enemy* tmp = enemyManager.enemy.back();
		entityList.push_back(tmp);
			
	}

	switch (patternType)
	{
		case Circle:
		{
			if (rotationType == defaultRotation) this->rotationType = Spin;

			setUpPattern(Circle);
			ApplyPhysics();
			angleVelocity = 0.1;
			setTimer(0, -1);
		}
		break;

		case Square:
		{
			if (rotationType == defaultRotation) this->rotationType = tiltUp;

			setUpPattern(Square);
			ApplyPhysics();
			setTimer(0, -1);
		}
		break;

		case None:
		{
			if (rotationType == defaultRotation) this->rotationType = WithOwnVelocityTiltUp;

			setUpPattern(None);
			setTimer(0, -1);
		}

	default:
		break;
	}
}








