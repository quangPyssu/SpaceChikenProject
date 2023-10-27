#include "EnemyPattern.h"

EnemyPattern::EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, int total, float width, int widthCnt)
{
	this->enemyManager = &enemyManager;

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

EnemyPattern::EnemyPattern(EnemyPatternType type, EnemyManager& enemyManager, Vector2f Position, Vector2f Velocity, 
	int total, float width, int widthCnt, RotationType roationType) : EnemyPattern(type, enemyManager, Position, Velocity, total, width, widthCnt)
{
	this->rotationType = roationType;
}

void EnemyPattern::takeTimeCurrent()
{
	Pattern::takeTimeCurrent();	
}







