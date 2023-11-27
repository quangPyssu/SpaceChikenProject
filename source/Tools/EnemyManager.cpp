#include "EnemyManager.h"

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer)
{
	warningZone = new WarningZone();
	PushToObject(warningZone, this);

	this->EnimesBullets = new BulletManager(player);
	this->EnimesBullets_Vulnerable = new BulletManager(player);
	dummy = new SubTitle({ 0,0 }, Vector2f(-300, -300), trans, { 0.2,0.4 }, 0, trans, "", "neuro", -1);
	PushToObject(dummy, this);

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
	detachChild(*dummy);
	dummy = nullptr;
	for (int i = 0; i < BulletPatternList.size(); i++) detachChild(*BulletPatternList[i]);

	
	enemy.clear();
	BulletPatternList.clear();
	BulletPattern_Aim_For_Player.clear();
}

void EnemyManager::addEnemy(EnemyType type)
{
	enemy.push_back(EnemyFactory::createEnemy(type,Vector2f(rand() % 1000, 100)));
	enemy.back()->setBulletManager(EnimesBullets, EnimesBullets_Vulnerable);
	enemy.back()->setPlayer(player);
	enemy.back()->setWarningZone(warningZone);

	PlayerBullets_Standard->addTarget(*enemy.back());
	PlayerBullets_Detroyer->addTarget(*enemy.back());

	PushToObject(enemy.back(), dummy);
}

void EnemyManager::addEnemy(EnemyType type, Vector2f Position, Vector2f Velocity, Vector2f Acceleration,int timerEnd)
{
	addEnemy(type);
	enemy.back()->setPosition(Position*SCALE);
	enemy.back()->setVelocity(Velocity*SCALE);
	enemy.back()->setAcceleration(Acceleration*SCALE);
	enemy.back()->setTimer(0, timerEnd);
}

void EnemyManager::takeTimeCurrent()
{
	for (int i = 0; i < enemy.size(); i++)	
	{
		if (enemy[i]->CurrentEnityState == EntityState::Dead)
		{
			// Detach the child
			dummy->detachChild(*enemy[i]);

			PlayerBullets_Standard->removeTarget(*enemy[i]);
			PlayerBullets_Detroyer->removeTarget(*enemy[i]);

			// Erase it from the enemy vector
			enemy.erase(enemy.begin() + i);
			i--;
		}
		else if (enemy[i]->CurrentEnityState == EntityState::Alive)
		{
			if (player->CurrentEnityState == Alive && enemy[i]->CollitionDetection(*player))
			{
				player->takeDamage(enemy[i]->Damage);
			}

			if (enemy[i]->isFiring)// Enemy Fire
			{
				while (!enemy[i]->Enemy_BulletPattern_queue.empty())
				{
					addBulletPattern(enemy[i]->Enemy_BulletPattern_queue.front().ff);

					if (enemy[i]->Enemy_BulletPattern_queue.front().ss) BulletPattern_Aim_For_Player.push_back(enemy[i]->Enemy_BulletPattern_queue.front());

					enemy[i]->Enemy_BulletPattern_queue.pop();
				}

				if (enemy[i]->spawnRequest) // Enemy Spawn event
				{
					addEnemy(enemy[i]->SpawnType, enemy[i]->getPosition() * (1 / SCALE) + Vector2f(0, 100), enemy[i]->spawnVelocity, Vector2f(0, 0), -1);
					enemy.back()->setHitPoints(enemy.back()->getHitPoint() / 2 + 10);
					enemy[i]->spawnRequest = false;

					switch (enemy[i]->SpawnType)
					{
					case EnemyType_SemiVortex: { enemy.back()->gotoPosition(Vector2f(25, 560) * SCALE, 50); } break;
					case EnemyType_SprialVortex: { enemy.back()->gotoPosition(Vector2f(775, 560) * SCALE, 50); } break;
					case EnemyType_BlackHole: { enemy.back()->gotoPosition(Vector2f(400, 80) * SCALE, 50); } break;
					}
				}

				switch (enemy[i]->type)	// Enemy spawn with cooldown
				{
				case EnemyType_Henterprise:
				{
					for (int j = 0; j < 2; j++)
					{
						addEnemy(EnemyType_Chicken_1, Vector2f(200 + j * 100, 1), Vector2f(0, 40), Vector2f(-8, -1), 1000);
						addEnemy(EnemyType_Chicken_1, Vector2f(600 - j * 100, 1), Vector2f(0, 40), Vector2f(8, -1), 1000);
					}
				} break;
				}

				enemy[i]->resetGun();
			}
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

void EnemyManager::addBulletPattern(BulletPattern* bulletPattern)
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

			tmp->setVelocity(tmp->velocityToB(100*SCALE, player)+Vector2f(diva-randInt(diva*2),diva - randInt(diva * 2)));

			BulletPattern_Aim_For_Player.erase(BulletPattern_Aim_For_Player.begin() + i);
			i--;
		}
	}
}