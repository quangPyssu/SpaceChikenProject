#include "EnemyManager.h"

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer
	, BulletManager& EnimesBullets, BulletManager& EnimesBullets_Vulnerable, WarningZone& warningZone)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer)
	, EnimesBullets(&EnimesBullets) , EnimesBullets_Vulnerable(&EnimesBullets_Vulnerable), warningZone(&warningZone)
{

	EnimesBullets.addTarget(player);
	EnimesBullets.addTarget(EnimesBullets_Vulnerable);
	EnimesBullets_Vulnerable.addTarget(player);	
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemy.size(); i++) if (enemy[i] != nullptr) 
	{
		detachChild(*enemy[i]);
	}
	enemy.clear();
}

void EnemyManager::addEnemy(EnemyType type)
{
	enemy.push_back(new Enemy(type, Vector2f(rand() % 1000, 100)));

	PlayerBullets_Standard->addTarget(*enemy.back());
	PlayerBullets_Detroyer->addTarget(*enemy.back());

	PushToObject(enemy.back(), this);
}

void EnemyManager::removeEnemy(Entity& target)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i] == &target)
		{
			detachChild(*enemy[i]);
			enemy.erase(enemy.begin() + i);
			return;
		}
	}
}

void EnemyManager::takeTimeCurrent()
{
	for (int i = 0; i < enemy.size(); i++)	// Enemy Fire
	{
		if (enemy[i]->CurrentEnityState == EntityState::Dead)
		{
			// Detach the child
			detachChild(*enemy[i]);

			PlayerBullets_Standard->removeTarget(*enemy[i]);
			PlayerBullets_Detroyer->removeTarget(*enemy[i]);

			// Erase it from the enemy vector
			enemy.erase(enemy.begin() + i);
			i--;
		}
		else if (enemy[i]->CurrentEnityState == EntityState::Alive && enemy[i]->isFiring)
		{
			switch (enemy[i]->type)
			{
				case Enemy_Chicken_1:
				{
					EnimesBullets->addBullet(BulletType::Enemy_Bullet_Normal, enemy[i]->getPosition());
				}
				break;

				case Boss_Chicken_1:
				{
					
				}
			}

			enemy[i]->resetGun();
		}
	}	


	// Clean up the dead bullet pattern
	for (int i = 0; i < BulletPatternList.size(); i++)
	{
		if (BulletPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*BulletPatternList[i]);
			BulletPatternList.erase(BulletPatternList.begin() + i);
			i--;
		}
	}
}


void EnemyManager::addBulletPattern(BulletType type, PatternType patternType, RotationType rotationType, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,bool Physics,
	int total, float width, int widthCnt, int timerStart, int timerEnd)
{
	BulletManager* tmp = nullptr;

	switch (type)
	{
		case Enemy_Bullet_Normal: {	tmp = EnimesBullets; } break;
		case Astroid: {	tmp = EnimesBullets_Vulnerable; } break;

		default: {tmp = EnimesBullets;} break;
	}

	BulletPatternList.push_back(new BulletPattern(type, patternType, rotationType, *tmp, Position, Velocity, Acceleration, Physics, total, width, widthCnt, *warningZone, timerStart, timerEnd));
	
	PushToObject(BulletPatternList.back(), this);
}
