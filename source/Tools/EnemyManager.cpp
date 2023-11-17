#include "EnemyManager.h"

std::vector<BulletPattern*> EnemyManager::BulletPatternList;

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer)
{
	warningZone = new WarningZone();
	PushToObject(warningZone, this);

	this->EnimesBullets = new BulletManager(player);
	this->EnimesBullets_Vulnerable = new BulletManager(player);

	PushToObject(EnimesBullets, this);
	PushToObject(EnimesBullets_Vulnerable, this);

	EnimesBullets->addTarget(player);
	EnimesBullets->addTarget(*EnimesBullets_Vulnerable);
	EnimesBullets_Vulnerable->addTarget(player);	

	PlayerBullets_Detroyer.addTarget(*EnimesBullets);
	PlayerBullets_Detroyer.addTarget(*EnimesBullets_Vulnerable);
	PlayerBullets_Standard.addTarget(*EnimesBullets_Vulnerable);
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemy.size(); i++) if (enemy[i] != nullptr) 
	{
		detachChild(*enemy[i]);
	}
	enemy.clear();

	for (int i = 0; i < BulletPatternList.size(); i++) if (BulletPatternList[i] != nullptr)
	{
		detachChild(*BulletPatternList[i]);
	}

	BulletPatternList.clear();
	BulletPattern_Aim_For_Player.clear();

	//_CrtDumpMemoryLeaks();
}

void EnemyManager::addEnemy(EnemyType type)
{
	enemy.push_back(EnemyFactory::createEnemy(type,Vector2f(rand() % 1000, 100)));
	enemy.back()->setBulletManager(EnimesBullets, EnimesBullets_Vulnerable);
	enemy.back()->setPlayer(player);
	enemy.back()->setWarningZone(warningZone);

	PlayerBullets_Standard->addTarget(*enemy.back());
	PlayerBullets_Detroyer->addTarget(*enemy.back());

	PushToObject(enemy.back(), this);
}

void EnemyManager::removeEnemy(Entity& target)
{
	for (unsigned int i = 0; i < enemy.size(); i++)
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
	for (int i = 0; i < enemy.size(); i++)	
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
		else if (enemy[i]->CurrentEnityState == EntityState::Alive && enemy[i]->isFiring)// Enemy Fire
		{
			switch (enemy[i]->type)
			{
				case EnemyType_Boss_Chicken_1:
				{
					while (!enemy[i]->Enemy_BulletPattern_queue.empty())
					{
						addBulletPattern(enemy[i]->Enemy_BulletPattern_queue.front().ff, BulletType::BulletType_Enemy_Egg);

						if (enemy[i]->Enemy_BulletPattern_queue.front().ss) BulletPattern_Aim_For_Player.push_back(enemy[i]->Enemy_BulletPattern_queue.front());
						
						enemy[i]->Enemy_BulletPattern_queue.pop();
					}
				}
			}

			enemy[i]->resetGun();
		}
	}	

	fireBulletPattern();

	for (int i = 0; i < BulletPatternList.size(); i++)
	{
		if (BulletPatternList[i]->CurrentEnityState == EntityState::Dead)
		{
			detachChild(*BulletPatternList[i]);
			BulletPatternList.erase(BulletPatternList.begin() + i);
			i--;
		}
	}

	//cout << "BulletPatternList.size() " << BulletPatternList.size() << endl;	
	//cout << this->Children.size() << endl;
}

void EnemyManager::addBulletPattern(BulletType type, PatternType patternType, RotationType rotationType, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,bool Physics,
	int total, float width, int widthCnt, int timerStart, int timerEnd, double thisScale)
{
	BulletManager* tmp = nullptr;

	switch (type)
	{
		case BulletType_Enemy_Egg: {	tmp = EnimesBullets; } break;
		case BulletType_Astroid: {	tmp = EnimesBullets_Vulnerable; } break;
		case BulletType_Enemy_Laser: {tmp = EnimesBullets;} break;

		default: {tmp = EnimesBullets;} break;
	}

	BulletPatternList.push_back(new BulletPattern(type, patternType, rotationType, *tmp, Position, Velocity, Acceleration, Physics, total, width, widthCnt, *warningZone, timerStart, timerEnd,thisScale));
	
	PushToObject(BulletPatternList.back(), this);
}

void EnemyManager::addBulletPattern(BulletPattern* bulletPattern, BulletType type)
{
	BulletPatternList.push_back(bulletPattern);

	PushToObject(BulletPatternList.back(), this);
}


void EnemyManager::fireBulletPattern()
{
	for (int i = 0; i < BulletPattern_Aim_For_Player.size(); i++)
	{
		if (!BulletPattern_Aim_For_Player[i].ff->getTimerStart())
		{
			BulletPattern*& tmp=BulletPattern_Aim_For_Player[i].ff;
			int diva = BulletPattern_Aim_For_Player[i].ss;

			tmp->setVelocity(tmp->velocityToB(150, player)+Vector2f(diva-randInt(diva*2),diva - randInt(diva * 2)));

			BulletPattern_Aim_For_Player.erase(BulletPattern_Aim_For_Player.begin() + i);
			i--;
		}
	}
}