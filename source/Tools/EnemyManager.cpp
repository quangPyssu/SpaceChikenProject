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

	for (int i = 0; i < BulletPatternList.size(); i++) if (BulletPatternList[i] != nullptr)
	{
		detachChild(*BulletPatternList[i]);
	}

	BulletPatternList.clear();
	BulletPattern_Aim_For_Player.clear();
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
					switch (enemy[i]->attackType)
					{
						case 0: // 3 Circle
						{
							for (int j = 0; j < 3; j++)
							{
								addBulletPattern(BulletType::Enemy_Bullet_Normal, PatternType::Circle, RotationType::Spin, enemy[i]->getPosition(),
									{0,0}, {0,0}, false, 10, 70, 0, j * 100, -1, 1);
								BulletPattern_Aim_For_Player.push_back({BulletPatternList.back(), 10});
							}
						}
						break;

						case 1: // 2 Square
						{	
							for (int j = 0; j < 2; j++)
							{
								addBulletPattern(BulletType::Enemy_Bullet_Normal, PatternType::Square, RotationType::defaultRotation, enemy[i]->getPosition(),
									Vector2f(0,0), {0,0}, false, 9, 80, 3, j * 100, -1, 1);
								BulletPattern_Aim_For_Player.push_back({ BulletPatternList.back(), 10 });
							}
						}
						break;

						case 2: //4 Direction Circle
						{
							for (int j=0;j<2;j++)
								for (int k=0;k<2;k++)
									addBulletPattern(BulletType::Enemy_Bullet_Normal, PatternType::Circle, RotationType::Spin, enemy[i]->getPosition(),
											enemy[i]->velocityToB(150, player)*Vector2f(j?1:-1, k ? 1 : -1), {0,0}, true, 6, 80, 4, 0, 2000, 1);

							//spawn 4 go in 4 direction
						}	

						case 3: // barrage
						{
							for (int j = 0; j < 10; j++)
							{
								addBulletPattern(BulletType::Enemy_Bullet_Normal, PatternType::Circle, RotationType::WithVelocity, enemy[i]->getPosition(),
									{ 0,0 }, { 0,0 }, false, 1, 0, 1, j * 15, -1, 1);
								BulletPattern_Aim_For_Player.push_back({ BulletPatternList.back(), 10 });
							}
						}


						break;						
					}

					EnimesBullets->addBullet(BulletType::Enemy_Bullet_Normal, enemy[i]->getPosition());
				}
			}

			enemy[i]->resetGun();
		}
	}	

	fireBulletPattern();


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
	int total, float width, int widthCnt, int timerStart, int timerEnd, double thisScale)
{
	BulletManager* tmp = nullptr;

	switch (type)
	{
		case Enemy_Bullet_Normal: {	tmp = EnimesBullets; } break;
		case Astroid: {	tmp = EnimesBullets_Vulnerable; } break;

		default: {tmp = EnimesBullets;} break;
	}

	BulletPatternList.push_back(new BulletPattern(type, patternType, rotationType, *tmp, Position, Velocity, Acceleration, Physics, total, width, widthCnt, *warningZone, timerStart, timerEnd,thisScale));
	
	PushToObject(BulletPatternList.back(), this);
}


void EnemyManager::fireBulletPattern()
{
	for (int i = 0; i < BulletPattern_Aim_For_Player.size(); i++)
	{
		if (!BulletPattern_Aim_For_Player[i].ff->getTimerStart())
		{
			auto tmp=BulletPattern_Aim_For_Player[i].ff;
			int diva = BulletPattern_Aim_For_Player[i].ss;

			tmp->setVelocity(tmp->velocityToB(150, player)+Vector2f(diva-randInt(diva*2),
				diva - randInt(diva * 2)));

			BulletPattern_Aim_For_Player.erase(BulletPattern_Aim_For_Player.begin() + i);
			i--;
		}
	}
}