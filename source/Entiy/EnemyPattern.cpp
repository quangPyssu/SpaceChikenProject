#include "EnemyPattern.h"

EnemyPattern::EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration, int total, float width, int widthCnt)
{
	this->enemyManager = &enemyManager;

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
	rotationType = Spin;

	switch (type)
	{
	case Chicken_Circle:
	{
		for (int i = 0; i < total; i++)
		{
			enemyManager.addEnemy(Enemy_Chicken_1);
			Enemy* tmp = enemyManager.enemy.back();
			entityList.push_back(tmp);
		}

		setUpPattern(Circle);
		ApplyPhysics();
		angleVelocity = 0.1;
		setTimer(0, -1);
	}
	break;

	case Chicken_Square:
	{
		for (int i = 0; i < total; i++)
		{
			enemyManager.addEnemy(Enemy_Chicken_1);
			Enemy* tmp = enemyManager.enemy.back();
			entityList.push_back(tmp);
		}

		rotationType = tiltUp;
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

EnemyPattern::EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,
	int total, float width, int widthCnt, RotationType roationType) : EnemyPattern(type, enemyManager, Position, Velocity, Acceleration, total, width, widthCnt)
{
	this->rotationType = roationType;
}







