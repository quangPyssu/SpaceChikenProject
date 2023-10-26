#include "EnemyManager.h"

EnemyManager::EnemyManager(Player& player, BulletManager& PlayerBullets_Standard, BulletManager& PlayerBullets_Detroyer, BulletManager& EnimesBullets)
	: player(&player), PlayerBullets_Standard(&PlayerBullets_Standard), PlayerBullets_Detroyer(&PlayerBullets_Detroyer), EnimesBullets(&EnimesBullets)
{
	for (int i = 0; i < 0; i++) addEnemy(Enemy_Chicken_1);

	{	//Target setting
		for (int i = 0; i < enemy.size(); i++)
		{
			PlayerBullets_Standard.addTarget(*enemy[i]);
			PlayerBullets_Detroyer.addTarget(*enemy[i]);
		}

		EnimesBullets.addTarget(player);
	}


	BulletPatternList.push_back(new BulletPattern(Normal_Circle_Spin_NonKill, EnimesBullets, Vector2f(500, 500), Vector2f(0, 0)));
	PushToObject(BulletPatternList.back(), this);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::addEnemy(EnemyType type)
{
	enemy.push_back(new Enemy(type, Vector2f(rand() % 1000, 100)));
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
			EnimesBullets->addBullet(Enemy_Bullet_Normal, enemy[i]->getPosition());
			enemy[i]->resetGun();
		}
	}

	if (BulletPatternList.size() && BulletPatternList.back()->CurrentEnityState == Dead)
	{
		detachChild(*BulletPatternList.back());
		BulletPatternList.pop_back();
	}
}

